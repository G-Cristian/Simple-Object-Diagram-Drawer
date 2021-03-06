#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "../Include/appInputParser.h"
#include "../Include/appInputParserStrategy.h"
#include "../Include/ConnectivityMatrix.h"
#include "../Include/FileOpener.h"
#include "../Include/graphdrawer.h"
#include "../Include/Parser.h"
#include "../Include/renderer.h"

using namespace std;

int main(int argc, char *argv[]) {
	try {
		aip::AppInputParser appInputParser(argc, argv);
		FileOpener fileOpener;
		const aip::Parameters parameters = appInputParser.getParameters();
		vector<string> text = fileOpener.openFile(parameters._inputFileName);
		prsr::Parser parser(text);
		gd::Graph graph = parser.parseGraph();

		Renderer::Window window = Renderer::Window();
		window.name = parameters._appName;
		window.width = 600;		//dummy width to create the window. It will be replaced when calculating the positions of the nodes when drawing the graph.
		window.height = 800;	//dummy height to create the window. It will be replaced when calculating the positions of the nodes when drawing the graph.
		Renderer renderer = Renderer(window);

		gd::GraphDrawer graphDrawer(renderer);
		graphDrawer.drawGraph(graph, parameters.getBoundingRectangleGetter(graph));

		renderer.show(0, 0);
		renderer.exportToImage(parameters._outputFileName);
	}
	catch (exception &e) {
		cout << e.what();
	}
	
	waitKey();

	return 0;
}