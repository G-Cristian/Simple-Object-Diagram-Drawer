#include "../Include/ConnectionDrawingAlgorithms.h"

ConnectionDrawingAlgorithm::ConnectionDrawingAlgorithm(){
}

ConnectionDrawingAlgorithm::~ConnectionDrawingAlgorithm() {

}

LineDrawingAlgorithm::LineDrawingAlgorithm() {

}

LineDrawingAlgorithm::~LineDrawingAlgorithm() {

}

void LineDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawLine(p1, p2);
}

DashedLineDrawingAlgorithm::DashedLineDrawingAlgorithm() {

}

DashedLineDrawingAlgorithm::~DashedLineDrawingAlgorithm() {

}

void DashedLineDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawDashedLine(p1, p2);
}

ArrowDrawingAlgorithm::ArrowDrawingAlgorithm() {

}

ArrowDrawingAlgorithm::~ArrowDrawingAlgorithm() {

}

void ArrowDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawArrow(p1, p2);
}

DashedArrowDrawingAlgorithm::DashedArrowDrawingAlgorithm() {

}

DashedArrowDrawingAlgorithm::~DashedArrowDrawingAlgorithm() {

}

void DashedArrowDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawDashedArrow(p1, p2);
}

DoubleArrowDrawingAlgorithm::DoubleArrowDrawingAlgorithm() {

}

DoubleArrowDrawingAlgorithm::~DoubleArrowDrawingAlgorithm() {

}

void DoubleArrowDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawDoubleArrow(p1, p2);
}

DashedDoubleArrowDrawingAlgorithm::DashedDoubleArrowDrawingAlgorithm() {

}

DashedDoubleArrowDrawingAlgorithm::~DashedDoubleArrowDrawingAlgorithm() {

}

void DashedDoubleArrowDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawDashedDoubleArrow(p1, p2);
}

ReversedArrowDrawingAlgorithm::ReversedArrowDrawingAlgorithm() {

}

ReversedArrowDrawingAlgorithm::~ReversedArrowDrawingAlgorithm() {

}

void ReversedArrowDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawArrow(p2, p1);
}

ReversedDashedArrowDrawingAlgorithm::ReversedDashedArrowDrawingAlgorithm() {

}

ReversedDashedArrowDrawingAlgorithm::~ReversedDashedArrowDrawingAlgorithm() {

}

void ReversedDashedArrowDrawingAlgorithm::drawConnection(Renderer &renderer, const Point2D &p1, const Point2D &p2) const {
	renderer.drawDashedArrow(p2, p1);
}
