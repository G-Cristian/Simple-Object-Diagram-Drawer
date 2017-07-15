#include "../Include/renderer.h"

Renderer::Renderer(Window &window) {
	_window = Window();
	_window.name = window.name;
	_window.width = window.width;
	_window.height = window.height;

	_img = Mat::zeros(window.height, window.width, CV_8UC3);
}

Renderer::~Renderer() {

}

void Renderer::drawCircle(Geometry::Point2Di center, int radius) {
	circle(_img, Point(center.x, center.y), radius, Scalar(255, 255, 255));
}

void Renderer::drawLine(Geometry::Point2Di p1, Geometry::Point2Di p2) {
	line(_img, Point(p1.x, p1.y), Point(p2.x, p2.y), Scalar(255,255,255));
}

void Renderer::drawArrow(Geometry::Point2Di p1, Geometry::Point2Di p2) {
	drawLine(p1, p2);
	drawArrowTip(p2, Geometry::Point2Di(p2.x - p1.x, p2.y - p1.y));
}

void Renderer::drawDoubleArrow(Geometry::Point2Di p1, Geometry::Point2Di p2) {
	drawLine(p1, p2);
	drawArrowTip(p2, Geometry::Point2Di(p2.x - p1.x, p2.y - p1.y));
	drawArrowTip(p1, Geometry::Point2Di(p1.x - p2.x, p1.y - p2.y));
}

void Renderer::drawArrowTip(Geometry::Point2Di p1, Geometry::Point2Di directionVector) {
	Vec2d localDirection = normalize(Vec2d(directionVector.x, directionVector.y));

	Vec2d l1 = getRotated(localDirection, 50) * 25;
	Vec2d l2 = getRotated(localDirection, -50) * 25;
	
	drawLine(p1, p1 + Geometry::Point2Di(-l1[0], -l1[1]));
	drawLine(p1, p1 + Geometry::Point2Di(-l2[0], -l2[1]));
}

Vec2d Renderer::getRotated(const Vec2d &vector, float angle) const {
	Vec2d res = Vec2d();
	res[0] = vector[0] * cosf(angle) - vector[1] * sinf(angle);
	res[1] = vector[0] * sinf(angle) + vector[1] * cosf(angle);

	return res;
}

void Renderer::show(int x, int y)  const{
	imshow(_window.name, _img);
	moveWindow(_window.name, x, y);
}