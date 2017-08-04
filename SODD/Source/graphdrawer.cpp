#include "../Include/graphdrawer.h"
#include "../Include/Line.h"
#include "../Include/Circle.h"

using Geometry::Line;
using Geometry::Circle;

namespace GraphDrawer {
	Node::Node(float radius):Node(radius, "") {
	}

	Node::Node(float radius, string text) {
		_radius = radius;
		_text = text;
	}

	Node::~Node() {

	}

	inline float Node::getRadius() const {
		return _radius;
	}

	inline string Node::getText() const {
		return _text;
	}

	Graph::Graph(const vector<Node> &nodes, const ConnectivityMatrix &connectivityMatrix):_connectivityMatrix(connectivityMatrix) {
		//TODO : Assert nodes.size() == connectivityMatrix.getNodeCounts(), or throw exception otherwise.
		_nodes = nodes;
		_edges = _connectivityMatrix.toAdjacencyList();
	}

	Graph::~Graph(){

	}

	const vector<Node> & Graph::getNodes() const {
		return _nodes;
	}

	const vector<list<int> > & Graph::getEdges() const {
		return _edges;
	}

	const ConnectivityMatrix & Graph::getConnectivityMatrix() const {
		return _connectivityMatrix;
	}

	GraphDrawer::GraphDrawer(Renderer &rendererToDrawTo)
		:_renderer(rendererToDrawTo){
	}

	GraphDrawer::~GraphDrawer() {

	}

	void GraphDrawer::drawGraph(const Graph &graph) {
		vector<Geometry::Point2D> nodesPositions = calculateNodesPositions(graph);
		actuallyDrawGraph(graph, nodesPositions);
	}

	vector<Geometry::Point2D> GraphDrawer::calculateNodesPositions(const Graph &graph) const {
		vector<Geometry::Point2D> positions = vector<Geometry::Point2D>();
		const vector<Node> nodes = graph.getNodes();
		positions.reserve(nodes.size());

		//TODO: replace following code with the algorithm to draw the graph
		//This is just for testing
		for (vector<Node>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
			positions.push_back(Geometry::Point2D(rand() % 600, rand() % 600));
		}
		positions[0] = Geometry::Point2D(50,50);
		positions[1] = Geometry::Point2D(200, 100);
		positions[2] = Geometry::Point2D(100, 200);
		positions[3] = Geometry::Point2D(450, 450);
		

		return positions;
	}

	void GraphDrawer::actuallyDrawGraph(const Graph &graph, const vector<Geometry::Point2D> &nodePositions) {
		drawNodes(graph, nodePositions);
		drawEdges(graph, nodePositions);
	}

	void GraphDrawer::drawNodes(const Graph &graph, const vector<Geometry::Point2D> &positions) {
		const vector<Node> nodes = graph.getNodes();
		int n = nodes.size();

		for (int i = 0; i < n; ++i) {
			drawNode(nodes[i], positions[i]);
		}
	}

	void GraphDrawer::drawNode(const Node &node, Geometry::Point2D position) {
		_renderer.drawCircle(position, node.getRadius());
		_renderer.drawTextCenteredInBoundingCircle(node.getText(), Circle(position, node.getRadius()), 5);
	}

	void GraphDrawer::drawEdges(const Graph &graph, const vector<Geometry::Point2D> &positions) {
		const vector<Node> nodes = graph.getNodes();
		const vector<list<int> > edges = graph.getEdges();
		const ConnectivityMatrix connectivityMatrix = graph.getConnectivityMatrix();
		int n = nodes.size();
		vector<bool> alreadyChecked = vector<bool>(n, false);
		

		for (int currentNode = 0; currentNode < n; ++currentNode) {
			const list<int> currentAdjacencyList = edges[currentNode];
			for (list<int>::const_iterator it = currentAdjacencyList.begin(); it != currentAdjacencyList.end(); it++) {
				int otherNode = *it;

				if (!alreadyChecked[otherNode]) {
					list<ConnectionDrawingAlgorithm*> connectionDrawingAlgorithms = connectivityMatrix.getConnectionAlgorithmsBetweenNodes(currentNode, otherNode);
					drawConnectivity(nodes[currentNode], positions[currentNode], nodes[otherNode], positions[otherNode], connectionDrawingAlgorithms);
				}
			}

			alreadyChecked[currentNode] = true;
		}
	}

	void GraphDrawer::drawConnectivity(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2, list<ConnectionDrawingAlgorithm*> &connectivities) {
		int numberOfArrows = connectivities.size();
		float minimumRadius = min(node1.getRadius(), node2.getRadius());
		
		Geometry::Point2D diffPositions = positionNode2 - positionNode1;

		Vec2d auxVector = normalize(Vec2d(diffPositions.y, -diffPositions.x));
		Geometry::Point2D orthogonalVectorToVectorFromNode1ToNode2 = Geometry::Point2D(auxVector[0], auxVector[1]);
		
		Geometry::Line lineFromCircumferenceOfNodeWithMinimunRadiusToOtherNode = Line(	positionNode1 + orthogonalVectorToVectorFromNode1ToNode2*minimumRadius,
																						positionNode2 + orthogonalVectorToVectorFromNode1ToNode2*minimumRadius);
		
		float circlePartition = (minimumRadius * 2) / (numberOfArrows + 1);

		for (int i = 1; i < numberOfArrows+1; i++) {
			Geometry::Line ray = Geometry::Line(lineFromCircumferenceOfNodeWithMinimunRadiusToOtherNode.getPoint1() - orthogonalVectorToVectorFromNode1ToNode2 * (i * circlePartition),
												lineFromCircumferenceOfNodeWithMinimunRadiusToOtherNode.getPoint2() - orthogonalVectorToVectorFromNode1ToNode2 * (i * circlePartition));

			pair<Geometry::Point2D, Geometry::Point2D> collitionPoints = getCollitionPoints(node1, positionNode1, node2, positionNode2, ray);

			connectivities.front()->drawConnection(_renderer, collitionPoints.first, collitionPoints.second);
			delete connectivities.front();
			connectivities.pop_front();
		}
	}

	pair<Geometry::Point2D, Geometry::Point2D> GraphDrawer::getCollitionPoints(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2, const Line &ray) const {
		Geometry::Point2D collitionPointInNode2 = ray.firstCollitionPointAgainstCircle(Circle(positionNode2, node2.getRadius()));
		Geometry::Point2D collitionPointInNode1 = ray.reversed().firstCollitionPointAgainstCircle(Circle(positionNode1, node1.getRadius()));

		return pair<Geometry::Point2D, Geometry::Point2D>(collitionPointInNode1, collitionPointInNode2);
	}
}