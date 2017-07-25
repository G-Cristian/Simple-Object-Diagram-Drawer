#include "../Include/includes.h"
#include "../Include/Point2D.h"
#include <vector>
#include <list>

using namespace std;

int main() {
	Renderer::Window window = Renderer::Window();
	window.name = "Test";
	window.width = 600;
	window.height = 800;
	
	Renderer renderer = Renderer(window);
	
	/*renderer.drawCircle(Geometry::Point2D(100, 100), 20);
	renderer.drawLine(Geometry::Point2D(150, 150), Geometry::Point2D(200, 350));
	renderer.drawArrowTip(Geometry::Point2D(300, 300), Geometry::Point2D(10,10));
	renderer.drawArrow(Geometry::Point2D(400, 400), Geometry::Point2D(400, 200));
	renderer.drawArrow(Geometry::Point2D(400, 400), Geometry::Point2D(250, 400));
	renderer.drawDoubleArrow(Geometry::Point2D(250, 250), Geometry::Point2D(320, 540));
	*/

	vector<GraphDrawer::Node> nodes = vector<GraphDrawer::Node>();

	nodes.push_back(GraphDrawer::Node(10));
	nodes.push_back(GraphDrawer::Node(20));
	nodes.push_back(GraphDrawer::Node(30));
	nodes.push_back(GraphDrawer::Node(40));

	vector<list<int> > edges = vector<list<int> >();
	list<int> adjLst = list<int>();
	adjLst.push_back(1);
	adjLst.push_back(2);
	adjLst.push_back(3);
	edges.push_back(adjLst);

	adjLst = list<int>();
	adjLst.push_back(0);
	adjLst.push_back(2);
	edges.push_back(adjLst);

	adjLst = list<int>();
	adjLst.push_back(0);
	adjLst.push_back(1);
	adjLst.push_back(3);
	edges.push_back(adjLst);

	adjLst = list<int>();
	adjLst.push_back(0);
	adjLst.push_back(2);
	edges.push_back(adjLst);

	GraphDrawer::matrix_b adjacencyMatrix = vector<vector<bool> >(nodes.size());
	vector<bool> row = vector<bool>(nodes.size(), false);
	row[1] = true;
	row[2] = true;
	row[3] = false;
	adjacencyMatrix[0] = row;

	row = vector<bool>(nodes.size(), false);
	row[0] = false;
	row[2] = true;
	adjacencyMatrix[1] = row;

	row = vector<bool>(nodes.size(), false);
	row[0] = true;
	row[1] = true;
	row[3] = false;
	adjacencyMatrix[2] = row;

	row = vector<bool>(nodes.size(), false);
	row[0] = true;
	row[2] = true;
	adjacencyMatrix[3] = row;
	
	GraphDrawer::Graph graph = GraphDrawer::Graph(nodes, edges, adjacencyMatrix);
	GraphDrawer::GraphDrawer gd = GraphDrawer::GraphDrawer(renderer);
	gd.drawGraph(graph);


	renderer.show(100, 100);
	
	waitKey();

	return 0;
}