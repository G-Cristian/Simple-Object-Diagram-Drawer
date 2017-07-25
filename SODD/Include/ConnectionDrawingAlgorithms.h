#ifndef _CONECTION_DRAWING_ALGORITHMS_H_
#define _CONECTION_DRAWING_ALGORITHMS_H_

#include "renderer.h"
#include "Point2D.h"

using namespace Geometry;

class ConnectionDrawingAlgorithm {
public:
	ConnectionDrawingAlgorithm();
	~ConnectionDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const = 0;
};

class LineDrawingAlgorithm:public ConnectionDrawingAlgorithm {
public:
	LineDrawingAlgorithm();
	~LineDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DashedLineDrawingAlgorithm:public ConnectionDrawingAlgorithm {
public:
	DashedLineDrawingAlgorithm();
	~DashedLineDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class ArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	ArrowDrawingAlgorithm();
	~ArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DashedArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	DashedArrowDrawingAlgorithm();
	~DashedArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DoubleArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	DoubleArrowDrawingAlgorithm();
	~DoubleArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class DashedDoubleArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	DashedDoubleArrowDrawingAlgorithm();
	~DashedDoubleArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class ReversedArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	ReversedArrowDrawingAlgorithm();
	~ReversedArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

class ReversedDashedArrowDrawingAlgorithm :public ConnectionDrawingAlgorithm {
public:
	ReversedDashedArrowDrawingAlgorithm();
	~ReversedDashedArrowDrawingAlgorithm();

	virtual void drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const;
};

#endif // !_CONECTION_DRAWING_ALGORITHMS_H_

