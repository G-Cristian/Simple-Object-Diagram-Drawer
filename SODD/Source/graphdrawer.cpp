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

	Graph::Graph(const vector<Node> &nodes, const vector<list<int> > &edges, const matrix_b &adjacencyMatrix) {
		_nodes = nodes;
		_edges = edges;
		_adjacencyMatrix = adjacencyMatrix;
	}

	Graph::~Graph(){

	}

	const vector<Node> & Graph::getNodes() const {
		return _nodes;
	}

	const vector<list<int> > & Graph::getEdges() const {
		return _edges;
	}

	const matrix_b & Graph::getAdjacencyMatrix() const {
		return _adjacencyMatrix;
	}

	GraphDrawer::GraphDrawer(Renderer &rendererToDrawTo)
		:_renderer(rendererToDrawTo){
	}

	GraphDrawer::~GraphDrawer() {

	}

	void GraphDrawer::drawGraph(const Graph &graph) {
		vector<Geometry::Point2Di> nodesPositions = calculateNodesPositions(graph);
		actuallyDrawGraph(graph, nodesPositions);
	}

	vector<Geometry::Point2Di> GraphDrawer::calculateNodesPositions(const Graph &graph) const {
		vector<Geometry::Point2Di> positions = vector<Geometry::Point2Di>();
		const vector<Node> nodes = graph.getNodes();
		positions.reserve(nodes.size());

		//TODO: replace following code with the algorithm to draw the graph
		//This is just for testing
		for (vector<Node>::const_iterator it = nodes.begin(); it != nodes.end(); it++) {
			positions.push_back(Geometry::Point2Di(rand() % 600, rand() % 600));
		}
		positions[0] = Geometry::Point2Di(50,50);
		positions[1] = Geometry::Point2Di(200, 100);
		positions[2] = Geometry::Point2Di(100, 200);
		positions[3] = Geometry::Point2Di(250, 200);
		

		return positions;
	}

	void GraphDrawer::actuallyDrawGraph(const Graph &graph, const vector<Geometry::Point2Di> &nodePositions) {
		drawNodes(graph, nodePositions);
		drawEdges(graph, nodePositions);
	}

	void GraphDrawer::drawNodes(const Graph &graph, const vector<Geometry::Point2Di> &positions) {
		const vector<Node> nodes = graph.getNodes();
		int n = nodes.size();

		for (int i = 0; i < n; ++i) {
			drawNode(nodes[i], positions[i]);
		}
	}

	void GraphDrawer::drawEdges(const Graph &graph, const vector<Geometry::Point2Di> &positions) {
		const vector<Node> nodes = graph.getNodes();
		const vector<list<int> > edges = graph.getEdges();
		const matrix_b adjacencyMatrix = graph.getAdjacencyMatrix();
		int n = nodes.size();
		vector<bool> alreadyChecked = vector<bool>(n, false);
		

		for (int currentNode = 0; currentNode < n; ++currentNode) {
			const list<int> currentAdjacencyList = edges[currentNode];
			for (list<int>::const_iterator it = currentAdjacencyList.begin(); it != currentAdjacencyList.end(); it++) {
				int otherNode = *it;

				if (!alreadyChecked[otherNode]) {
					if (adjacencyMatrix[currentNode][otherNode]) {
						if (adjacencyMatrix[otherNode][currentNode]) {
							connectNodesWithDoubleArrow(nodes[currentNode], positions[currentNode], nodes[otherNode], positions[otherNode]);
						}
						else {
							connectNodesWithArrow(nodes[currentNode], positions[currentNode], nodes[otherNode], positions[otherNode]);
						}
					}
					else if (adjacencyMatrix[otherNode][currentNode]) {
						connectNodesWithArrow(nodes[otherNode], positions[otherNode], nodes[currentNode], positions[currentNode]);
					}
				}
			}

			alreadyChecked[currentNode] = true;
		}
	}

	void GraphDrawer::drawNode(const Node &node, Geometry::Point2Di position) {
		_renderer.drawCircle(position, node.getRadius());
	}

	void GraphDrawer::connectNodesWithEdge(const Node &node1, Geometry::Point2Di positionNode1, const Node &node2, Geometry::Point2Di positionNode2) {
		pair<Geometry::Point2Di, Geometry::Point2Di> connectionPoints = getCollitionPoints(node1, positionNode1, node2, positionNode2);
		_renderer.drawLine(connectionPoints.first, connectionPoints.second);
	}

	void GraphDrawer::connectNodesWithArrow(const Node &node1, Geometry::Point2Di positionNode1, const Node &node2, Geometry::Point2Di positionNode2) {
		pair<Geometry::Point2Di, Geometry::Point2Di> connectionPoints = getCollitionPoints(node1, positionNode1, node2, positionNode2);
		_renderer.drawArrow(connectionPoints.first, connectionPoints.second);
	}

	void GraphDrawer::connectNodesWithDoubleArrow(const Node &node1, Geometry::Point2Di positionNode1, const Node &node2, Geometry::Point2Di positionNode2) {
		pair<Geometry::Point2Di, Geometry::Point2Di> connectionPoints = getCollitionPoints(node1, positionNode1, node2, positionNode2);
		_renderer.drawDoubleArrow(connectionPoints.first, connectionPoints.second);
	}

	pair<Geometry::Point2Di, Geometry::Point2Di> GraphDrawer::getCollitionPoints(const Node &node1, Geometry::Point2Di positionNode1, const Node &node2, Geometry::Point2Di positionNode2) const {
		Line lineFromNode1ToNode2 = Line(positionNode1, positionNode2);
		Geometry::Point2Di collitionPointInNode2 = lineFromNode1ToNode2.firstCollitionPointAgainstCircle(Circle(positionNode2, node2.getRadius()));
		Line lineFromNode2ToNode1 = Line(positionNode2, positionNode1);
		Geometry::Point2Di collitionPointInNode1 = lineFromNode2ToNode1.firstCollitionPointAgainstCircle(Circle(positionNode1, node1.getRadius()));

		return pair<Geometry::Point2Di, Geometry::Point2Di>(collitionPointInNode1, collitionPointInNode2);
	}
}