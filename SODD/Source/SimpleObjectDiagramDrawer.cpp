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

	vector<gd::Node> nodes = vector<gd::Node>();

	nodes.push_back(gd::Node(50, "Renderer"));
	nodes.push_back(gd::Node(50, "Circle"));
	nodes.push_back(gd::Node(20, "Point2D"));
	nodes.push_back(gd::Node(50, "GraphDrawer"));
	nodes.push_back(gd::Node(50, "Graph"));
	nodes.push_back(gd::Node(80, "Lista de Nodos"));
	nodes.push_back(gd::Node(50, "Rectangle"));
	nodes.push_back(gd::Node(30, "Line"));
	nodes.push_back(gd::Node(30, "Punto 1"));
	nodes.push_back(gd::Node(30, "Punto 2"));

	ConnectivityMatrix connectivityMatrix = ConnectivityMatrix(10);
	connectivityMatrix.setDashedArrowBetweenNodes(0, 1);
	connectivityMatrix.setDashedArrowBetweenNodes(0, 2);
	connectivityMatrix.setDashedArrowBetweenNodes(0, 4);
	connectivityMatrix.setDashedArrowBetweenNodes(0, 6);

	connectivityMatrix.setDashedArrowBetweenNodes(1, 3);

	connectivityMatrix.setArrowBetweenNodes(3, 0);
	connectivityMatrix.setDashedArrowBetweenNodes(3, 4);

	connectivityMatrix.setArrowBetweenNodes(4, 5);

	connectivityMatrix.setArrowBetweenNodes(6, 2);

	connectivityMatrix.setArrowBetweenNodes(7, 8);
	connectivityMatrix.setArrowBetweenNodes(7, 9);
	
	
	
	gd::Graph graph = gd::Graph(nodes, connectivityMatrix);
	gd::GraphDrawer gd = gd::GraphDrawer(renderer);
	gd.drawGraph(graph);

	//renderer.drawTextCenteredInBoundingCircle("Casa\nGrande\Moco\nLoco", Circle(Point2D(450, 450), 160),0);
	//renderer.drawTextCenteredInBoundingCircle("ObjectDrawerForGraphsNodes\nAndObjectDrawerForGraphEdges\nAnd Stuff\nTesting Multilines\nAnd one last line", Circle(Point2D(450, 450), 160), 5);
	//renderer.drawTextCenteredInBoundingCircle("A\nA\nA\nA\nA\nA\nA\nA\nA\nA\nA\nA\nA\nA\nA", Circle(Point2D(450, 450), 160),0);
	//renderer.drawTextCenteredInBoundingCircle("A", Circle(Point2D(450, 450), 160),0);
	renderer.show(0, 0);
	
	waitKey();

	return 0;
}