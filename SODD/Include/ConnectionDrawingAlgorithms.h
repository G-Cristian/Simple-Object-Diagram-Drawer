#ifndef _CONECTION_DRAWING_ALGORITHMS_H_
#define _CONECTION_DRAWING_ALGORITHMS_H_

#include "renderer.h"
#include "Point2D.h"

using namespace Geometry;

class ConnectionDrawingAlgorithm {
public:
	ConnectionDrawingAlgorithm();
	virtual ~ConnectionDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const = 0;
};

class LineDrawingAlgorithm:public ConnectionDrawingAlgorithm {
public:
	LineDrawingAlgorithm();
	virtual ~LineDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DashedLineDrawingAlgorithm:public ConnectionDrawingAlgorithm {
public:
	DashedLineDrawingAlgorithm();
	virtual ~DashedLineDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class ArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	ArrowDrawingAlgorithm();
	virtual ~ArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DashedArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	DashedArrowDrawingAlgorithm();
	virtual ~DashedArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DoubleArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	DoubleArrowDrawingAlgorithm();
	virtual ~DoubleArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DashedDoubleArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	DashedDoubleArrowDrawingAlgorithm();
	virtual ~DashedDoubleArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class ReversedArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	ReversedArrowDrawingAlgorithm();
	virtual ~ReversedArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class ReversedDashedArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	ReversedDashedArrowDrawingAlgorithm();
	virtual ~ReversedDashedArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

#endif // !_CONECTION_DRAWING_ALGORITHMS_H_

