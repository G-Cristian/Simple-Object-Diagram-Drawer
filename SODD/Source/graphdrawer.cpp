#include "../Include/BoundingRectangleGetters.h"
#include "../Include/Circle.h"
#include "../Include/graphdrawer.h"
#include "../Include/Line.h"

#include <iostream>
#include <random>

using Geometry::Line;
using Geometry::Circle;
using Geometry::Rectangle;
using namespace std;

namespace gd {
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

	void GraphDrawer::drawGraph(const Graph &graph, shared_ptr<AbstractBoundingRectangleGetter> boundingRectangleGetter) {
		//TODO: Recive an instance of a class used to calculate the width and height and use that instance in 'getGraphBoundingRectangle'.
		vector<Geometry::Point2D> nodesPositions = calculateNodesPositions(graph, boundingRectangleGetter);
		Geometry::Rectangle boundingRectangle = getMinimumBoundingRectangle(graph, nodesPositions);
		_renderer.resizeWindow(static_cast<int>(boundingRectangle.getWidth()),
								static_cast<int>(boundingRectangle.getHeight()));
		//offset positions so the graph is centered (top-left graph is on the top-left of image)
		offsetGraph(-Point2D(boundingRectangle.getLeft(), boundingRectangle.getTop()), nodesPositions);
		actuallyDrawGraph(graph, nodesPositions);
	}

	vector<Geometry::Point2D> GraphDrawer::calculateNodesPositions(const Graph &graph, const shared_ptr<AbstractBoundingRectangleGetter> &boundingRectangleGetter) const {
		//get bounding rectangle
		Geometry::Rectangle boundingRectangle = boundingRectangleGetter->getRectangle();
		//position nodes
		vector<Geometry::Point2D> positions = nodesPositionsInsideRectangle(graph, boundingRectangle);

		return positions;
	}

	vector<Geometry::Point2D> GraphDrawer::nodesPositionsInsideRectangle(const Graph &graph, const Geometry::Rectangle &rectangle)const {
		const vector<Node> &nodes = graph.getNodes();
		size_t nodesCount = nodes.size();
		vector<Geometry::Point2D> positions = randomPositionsInsideRectangle(graph, rectangle);
		
		const int M = 2500;
		vector<Geometry::Point2D> displacements;;

		for (int i = 0; i < M; ++i) {
			displacements = vector<Geometry::Point2D>(nodesCount, Geometry::Point2D(0, 0));
			calculateDisplacements(graph, positions,rectangle, displacements);
			moveVertices(displacements, rectangle, positions);
		}

		return positions;
	}

	vector<Geometry::Point2D> GraphDrawer::randomPositionsInsideRectangle(const Graph &graph, const Geometry::Rectangle &rectangle)const {
		const vector<Node> &nodes = graph.getNodes();
		size_t nodesCount = nodes.size();
		vector<Geometry::Point2D> positions = vector<Geometry::Point2D>();
		positions.reserve(nodesCount);

		int rectangleWidth = static_cast<int>(rectangle.getWidth());
		int rectangleHeight = static_cast<int>(rectangle.getHeight());

		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distributionForWidth(0, rectangleWidth);
		std::uniform_int_distribution<int> distributionForHeight(0, rectangleHeight);
		for (int i = 0; i < nodesCount; ++i) {
			int a = distributionForWidth(generator);
			int b = distributionForHeight(generator);
			positions.push_back(Geometry::Point2D(a, b));
		}

		return positions;
	}

	void GraphDrawer::calculateDisplacements(const Graph &graph, const vector<Geometry::Point2D> &positions, const Geometry::Rectangle &boundingRectangle, vector<Geometry::Point2D> &outDisplacements)const {
		addRepulsiveDisplacementsToDisplacements(graph, positions, boundingRectangle, outDisplacements);
		addAttractiveDisplacementsToDisplacements(graph, positions, boundingRectangle, outDisplacements);
	}

	void GraphDrawer::addRepulsiveDisplacementsToDisplacements(const Graph &graph, const vector<Geometry::Point2D> &positions, const Geometry::Rectangle &boundingRectangle, vector<Geometry::Point2D> &outDisplacements)const {
		const vector<Node> &nodes = graph.getNodes();
		size_t nodesCount = nodes.size();
		double k = sqrt(boundingRectangle.area() / nodesCount);

		for (int i = 0; i < nodesCount; ++i) {
			for (int j = i + 1; j < nodesCount; ++j) {
				Circle circleNode1 = Circle(positions[i], nodes[i].getRadius());
				Circle circleNode2 = Circle(positions[j], nodes[j].getRadius());
				double distance = circleNode1.distanceFromCenterToOtherCenter(circleNode2);
				if (distance != 0) {
					Geometry::Point2D distanceVector = positions[j] - positions[i];
					Geometry::Point2D realDisplacement = (distanceVector / distance) * (k*k / distance);
					outDisplacements[i] = outDisplacements[i] - realDisplacement;
					outDisplacements[j] = outDisplacements[j] + realDisplacement;
				}
			}
		}
	}

	void GraphDrawer::addAttractiveDisplacementsToDisplacements(const Graph &graph, const vector<Geometry::Point2D> &positions, const Geometry::Rectangle &boundingRectangle, vector<Geometry::Point2D> &outDisplacements)const {
		const vector<Node> &nodes = graph.getNodes();
		const vector<list<int> > &edges = graph.getEdges();
		size_t nodesCount = nodes.size();
		double k = sqrt(boundingRectangle.area() / nodesCount);

		for (int i = 0; i < nodesCount; ++i) {
			for (list<int>::const_iterator it = edges[i].begin(); it != edges[i].end(); it++) {
				Circle circleNode1 = Circle(positions[i], nodes[i].getRadius());
				Circle circleNode2 = Circle(positions[*it], nodes[*it].getRadius());
				double distance = circleNode1.distanceFromCircumferenceToOtherCircumference(circleNode2);
				if (distance > 0) {
					Geometry::Point2D distanceVector = circleNode1.distanceVectorFromCircumferenceToOtherCircumference(circleNode2);
					Geometry::Point2D realDisplacement = (distanceVector / distance) * (distance*distance / k);

					outDisplacements[i] = outDisplacements[i] + realDisplacement;
				}
			}
		}
	}
	//TODO: thow exception if displacements.size() != outPositions.size()
	void GraphDrawer::moveVertices(const vector<Geometry::Point2D> &displacements, const Geometry::Rectangle &boundingRectangle, vector<Geometry::Point2D> &outPositions) const {
		size_t n = displacements.size();
		for (int i = 0; i < n; ++i) {
			outPositions[i].x = min(boundingRectangle.getWidth(), max(0.0, outPositions[i].x + 0.1*displacements[i].x));
			outPositions[i].y = min(boundingRectangle.getHeight(), max(0.0, outPositions[i].y + 0.1*displacements[i].y));
		}
	}

	
	Geometry::Rectangle GraphDrawer::getMinimumBoundingRectangle(const Graph &graph, const vector<Geometry::Point2D> &positions) const{
		const vector<Node> &nodes = graph.getNodes();
		size_t n = nodes.size();
		double top = 999999;
		double left = 999999;
		double bottom = -999999;
		double right = -999999;
		double nodeRadius = 0;
		for (int i = 0; i < n; ++i) {
			nodeRadius = nodes[i].getRadius();
			left = min(positions[i].x - nodeRadius, left);
			top = min(positions[i].y - nodeRadius, top);
			right = max(positions[i].x + nodeRadius, right);
			bottom = max(positions[i].y + nodeRadius, bottom);
		}
		return Geometry::Rectangle(left, top, right - left, bottom - top);
	}
	
	void GraphDrawer::offsetGraph(const Point2D &offset, vector<Geometry::Point2D> &outPositions) const {
		size_t n = outPositions.size();

		for (int i = 0; i < n; ++i) {
			outPositions[i] = outPositions[i] + offset;
		}
	}

	void GraphDrawer::actuallyDrawGraph(const Graph &graph, const vector<Geometry::Point2D> &nodePositions) {
		drawNodes(graph, nodePositions);
		drawEdges(graph, nodePositions);
	}

	void GraphDrawer::drawNodes(const Graph &graph, const vector<Geometry::Point2D> &positions) {
		const vector<Node> &nodes = graph.getNodes();
		size_t n = nodes.size();

		for (int i = 0; i < n; ++i) {
			drawNode(nodes[i], positions[i]);
		}
	}

	void GraphDrawer::drawNode(const Node &node, Geometry::Point2D position) {
		_renderer.drawCircle(position, static_cast<int>(node.getRadius()));
		_renderer.drawTextCenteredInBoundingCircle(node.getText(), Circle(position, node.getRadius()), 5);
	}

	void GraphDrawer::drawEdges(const Graph &graph, const vector<Geometry::Point2D> &positions) {
		const vector<Node> &nodes = graph.getNodes();
		const vector<list<int> > &edges = graph.getEdges();
		const ConnectivityMatrix connectivityMatrix = graph.getConnectivityMatrix();
		size_t n = nodes.size();
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
		size_t numberOfArrows = connectivities.size();
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