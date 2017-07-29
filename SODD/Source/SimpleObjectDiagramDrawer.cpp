#include "../Include/includes.h"
#include "../Include/Point2D.h"
#include "../Include/ConnectivityMatrix.h"
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

	ConnectivityMatrix connectivityMatrix = ConnectivityMatrix(4);
	connectivityMatrix.setArrowBetweenNodes(0, 1);
	connectivityMatrix.setArrowBetweenNodes(0, 2);

	connectivityMatrix.setArrowBetweenNodes(1, 2);
	connectivityMatrix.setDashedArrowBetweenNodes(1, 3);

	connectivityMatrix.setArrowBetweenNodes(2, 0);
	connectivityMatrix.setArrowBetweenNodes(2, 1);
	connectivityMatrix.setDashedArrowBetweenNodes(1, 2);

	connectivityMatrix.setArrowBetweenNodes(3, 0);
	connectivityMatrix.setArrowBetweenNodes(3, 2);
	connectivityMatrix.setDashedArrowBetweenNodes(3, 1);
	connectivityMatrix.setDashedArrowBetweenNodes(3, 2);
	
	GraphDrawer::Graph graph = GraphDrawer::Graph(nodes, connectivityMatrix);
	GraphDrawer::GraphDrawer gd = GraphDrawer::GraphDrawer(renderer);
	gd.drawGraph(graph);


	renderer.show(100, 100);
	
	waitKey();

	return 0;
}