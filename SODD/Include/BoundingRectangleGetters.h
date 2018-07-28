#ifndef _BOUNDINGRECTANGLEGETTERS_H_
#define _BOUNDINGRECTANGLEGETTERS_H_

#include "Rectangle.h"

namespace gd {
	class Graph;

	class AbstractBoundingRectangleGetter {
	public:
		AbstractBoundingRectangleGetter();
		virtual ~AbstractBoundingRectangleGetter();

		const Geometry::Rectangle &getRectangle() const { return _rectangle; }
	protected:
		Geometry::Rectangle _rectangle;
	};

	class AutomaticWidthAndHeightBoundingRectangleGetter : public AbstractBoundingRectangleGetter {
	public:
		AutomaticWidthAndHeightBoundingRectangleGetter(const Graph &graph);
		~AutomaticWidthAndHeightBoundingRectangleGetter() override;
	private:
		float summatoryRadius(const Graph &graph) const;
	};

	class AutomaticWidthManualHeightBoundingRectangleGetter : public AbstractBoundingRectangleGetter {
	public:
		AutomaticWidthManualHeightBoundingRectangleGetter(const Graph &graph, double height);
		~AutomaticWidthManualHeightBoundingRectangleGetter() override;
	};

	class ManualWidthAutomaticHeightBoundingRectangleGetter : public AbstractBoundingRectangleGetter {
	public:
		ManualWidthAutomaticHeightBoundingRectangleGetter(const Graph &graph, double width);
		~ManualWidthAutomaticHeightBoundingRectangleGetter() override;
	};

	class ManualWidthAndHeightBoundingRectangleGetter : public AbstractBoundingRectangleGetter {
	public:
		ManualWidthAndHeightBoundingRectangleGetter(double width, double height);
		~ManualWidthAndHeightBoundingRectangleGetter() override;
	};
}
#endif // !_BOUNDINGRECTANGLEGETTERS_H_
