#ifndef _GRAPHDRAWER_H_
#define _GRAPHDRAWER_H_

#include <string>
#include <vector>
#include <list>
#include <utility>
#include "renderer.h"
#include "Point2D.h"

using namespace std;

namespace GraphDrawer {
	typedef vector<vector <bool> > matrix_b;

	class Node {
	public:
		Node(float radius);
		Node(float radius, string text);
		~Node();

		inline float getRadius() const;
		inline string getText() const;
	private:
		float _radius;
		string _text;
	};

	class Graph {
	public:
		Graph(const vector<Node> &nodes, const vector<list<int> > &edges, const matrix_b &adjacencyMatrix);
		~Graph();

		const vector<Node>& getNodes()const;
		const vector<list<int> >& getEdges()const;
		const matrix_b& getAdjacencyMatrix()const;

	private:
		vector<Node> _nodes;
		vector<list<int> > _edges;
		matrix_b _adjacencyMatrix;
	};

	class GraphDrawer {
	public:
		GraphDrawer(Renderer &rendererToDrawTo);
		~GraphDrawer();

		void drawGraph(const Graph &graph);

	private:
		vector<Geometry::Point2D> calculateNodesPositions(const Graph &graph) const;
		void actuallyDrawGraph(const Graph &graph, const vector<Geometry::Point2D> &nodePositions);
		void drawNodes(const Graph &graph, const vector<Geometry::Point2D> &positions);
		void drawEdges(const Graph &graph, const vector<Geometry::Point2D> &positions);
		void drawNode(const Node &node, Geometry::Point2D position);
		void connectNodesWithEdge(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2);
		void connectNodesWithArrow(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2);
		void connectNodesWithDoubleArrow(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2);
		pair<Geometry::Point2D, Geometry::Point2D> getCollitionPoints(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2) const;
		
		Renderer & _renderer;
	};
}

#endif
