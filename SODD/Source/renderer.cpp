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

void Renderer::drawCircle(Point center, int radius) {
	circle(_img, center, radius, Scalar(255, 255, 255));
}

void Renderer::drawLine(Point p1, Point p2) {
	line(_img, p1, p2, Scalar(255,255,255));
}

void Renderer::drawArrow(Point p1, Point p2) {
	drawLine(p1, p2);
	drawArrowPoint(p2, Vec2d(p2.x - p1.x, p2.y - p1.y));
}

void Renderer::drawDoubleArrow(Point p1, Point p2) {
	drawLine(p1, p2);
	drawArrowPoint(p2, Vec2d(p2.x - p1.x, p2.y - p1.y));
	drawArrowPoint(p1, Vec2d(p1.x - p2.x, p1.y - p2.y));
}

void Renderer::drawArrowPoint(Point p1, Vec2d direction) {
	direction = normalize(direction);

	Vec2d l1 = getRotated(direction, 50) * 25;
	Vec2d l2 = getRotated(direction, -50) * 25;
	
	drawLine(p1, p1 + Point(-l1[0], -l1[1]));
	drawLine(p1, p1 + Point(-l2[0], -l2[1]));
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