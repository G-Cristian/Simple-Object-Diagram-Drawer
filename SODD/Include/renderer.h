#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <vector>
#include <string>

#include "Point2D.h"
#include "Circle.h"
#include "Rectangle.h"

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
	//'boundingOffsetPerLineOfText' will be scaled.
	void drawTextCenteredInBoundingCircle(string text, const Geometry::Circle &circle, double boundingOffsetPerLineOfText);

	void show(int x, int y) const;
	void exportToImage(const char *imageName) const;

private:
	Window _window;
	Mat _img;

	Vec2d getRotated(const Vec2d &vector, float angle) const;
	vector<string> splitStringByDelimiter(const string &stringToSplit, const string &delimiter) const;
	//'boundingOffsetPerLine' will be scaled.
	Geometry::Rectangle getBoundingRectangle(const vector<string> &lines, double boundingOffsetPerLine) const;
	//'boundingOffset' will be scaled by 'scale'.
	Geometry::Rectangle getBoundingRectangleUntilBaseOfWords(const string &singleLine, double boundingOffset, double scale) const;
	//TODO: remove if not used.
	//'boundingOffset' will be scaled by 'scale'.
	//Geometry::Rectangle getBoundingRectangleIncludingDescender(const string &singleLine, double boundingOffset, double scale) const;
	//'boundingOffsetPerLine' will be scaled.
	void drawTextToRectangle(const vector<string> &lines, const Geometry::Rectangle &rect, double boundingOffsetPerLine);
	//'boundingOffset' will be scaled by 'scale'.
	void drawTextCentered(const string &text, double boundingOffset, double scale, const Geometry::Point2D &center);
};

#endif
