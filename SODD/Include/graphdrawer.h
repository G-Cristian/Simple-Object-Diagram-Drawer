#ifndef _GRAPHDRAWER_H_
#define _GRAPHDRAWER_H_

#include <string>
#include <vector>
#include <list>
#include <utility>
#include "renderer.h"
#include "Point2D.h"
#include "Line.h"
#include "ConnectivityMatrix.h"
#include "ConnectionDrawingAlgorithms.h"

using namespace std;

namespace GraphDrawer {
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
		Graph(const vector<Node> &nodes, const ConnectivityMatrix &connectivityMatrix);
		~Graph();

		const vector<Node>& getNodes()const;
		const vector<list<int> >& getEdges()const;
		const ConnectivityMatrix& getConnectivityMatrix()const;

	private:
		vector<Node> _nodes;
		vector<list<int> > _edges;
		ConnectivityMatrix _connectivityMatrix;
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
		void drawNode(const Node &node, Geometry::Point2D position);
		void drawEdges(const Graph &graph, const vector<Geometry::Point2D> &positions);
		void drawConnectivity(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2, list<ConnectionDrawingAlgorithm*> &connectivities);
		pair<Geometry::Point2D, Geometry::Point2D> getCollitionPoints(const Node &node1, Geometry::Point2D positionNode1, const Node &node2, Geometry::Point2D positionNode2, const Line &ray) const;
		
		Renderer & _renderer;
	};
}

#endif
