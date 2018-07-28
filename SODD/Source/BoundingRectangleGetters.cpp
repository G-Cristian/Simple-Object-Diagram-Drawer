#include "../Include/BoundingRectangleGetters.h"
#include "../Include/graphdrawer.h"
#include "../Include/Rectangle.h"

namespace gd {
	//AbstractBoundingRectangleGetter
	AbstractBoundingRectangleGetter::AbstractBoundingRectangleGetter()
		: _rectangle(0,0,1,1){
	}
	
	AbstractBoundingRectangleGetter::~AbstractBoundingRectangleGetter() {
	}

	//AutomaticWidthAndHeightBoundingRectangleGetter
	AutomaticWidthAndHeightBoundingRectangleGetter::AutomaticWidthAndHeightBoundingRectangleGetter(const Graph &graph)
		:AbstractBoundingRectangleGetter() {
		float widthAndHeight = summatoryRadius(graph)*1.5;
		_rectangle = Geometry::Rectangle(0, 0, widthAndHeight, widthAndHeight);
	}
	
	AutomaticWidthAndHeightBoundingRectangleGetter::~AutomaticWidthAndHeightBoundingRectangleGetter() {
	}

	float AutomaticWidthAndHeightBoundingRectangleGetter::summatoryRadius(const Graph &graph) const {
		const vector<Node> &nodes = graph.getNodes();
		size_t n = nodes.size();
		float sum = 0;
		for (int i = 0; i < n; ++i) {
			sum += nodes[i].getRadius();
		}

		return sum;
	}

	//AutomaticWidthManualHeightBoundingRectangleGetter
	AutomaticWidthManualHeightBoundingRectangleGetter::AutomaticWidthManualHeightBoundingRectangleGetter(const Graph &graph, double height)
		:AbstractBoundingRectangleGetter() {
		AutomaticWidthAndHeightBoundingRectangleGetter autoWidthHeight(graph);
		_rectangle = Geometry::Rectangle(0, 0, autoWidthHeight.getRectangle().getWidth(), height);
	}

	AutomaticWidthManualHeightBoundingRectangleGetter::~AutomaticWidthManualHeightBoundingRectangleGetter() {
	}

	//ManualWidthAutomaticHeightBoundingRectangleGetter
	ManualWidthAutomaticHeightBoundingRectangleGetter::ManualWidthAutomaticHeightBoundingRectangleGetter(const Graph &graph, double width)
		:AbstractBoundingRectangleGetter() {
			AutomaticWidthAndHeightBoundingRectangleGetter autoWidthHeight(graph);
			_rectangle = Geometry::Rectangle(0, 0, width, autoWidthHeight.getRectangle().getHeight());
		}
	
	ManualWidthAutomaticHeightBoundingRectangleGetter::~ManualWidthAutomaticHeightBoundingRectangleGetter() {
	}

	//ManualWidthAndHeightBoundingRectangleGetter
	ManualWidthAndHeightBoundingRectangleGetter::ManualWidthAndHeightBoundingRectangleGetter(double width, double height)
		:AbstractBoundingRectangleGetter() {
		_rectangle = Geometry::Rectangle(0, 0, width, height);
	}
	
	ManualWidthAndHeightBoundingRectangleGetter::~ManualWidthAndHeightBoundingRectangleGetter() {
	}
}
