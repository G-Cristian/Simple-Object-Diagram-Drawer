#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <string>

#include "Point2D.h"

using namespace std;
using namespace cv;

class Renderer {
public:
	struct Window {
		String name;
		int width;
		int height;
	};

	Renderer(Window &window);
	~Renderer();

	void resizeWindow(int width, int height);

	void drawCircle(Geometry::Point2D center, int radius);
	void drawLine(Geometry::Point2D p1, Geometry::Point2D p2);
	void drawDashedLine(Geometry::Point2D p1, Geometry::Point2D p2, int linesLength = 5);
	void drawArrow(Geometry::Point2D p1, Geometry::Point2D p2);
	void drawDashedArrow(Geometry::Point2D p1, Geometry::Point2D p2, int linesLength = 5);
	void drawDoubleArrow(Geometry::Point2D p1, Geometry::Point2D p2);
	void drawDashedDoubleArrow(Geometry::Point2D p1, Geometry::Point2D p2, int linesLength = 5);
	void drawArrowTip(Geometry::Point2D p1, Geometry::Point2D directionVector);

	void show(int x, int y) const;
	void exportToImage(const char *imageName) const;

private:
	Window _window;
	Mat _img;

	Vec2d getRotated(const Vec2d &vector, float angle) const;
};

#endif
