#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <opencv2/core.hpp>
#include <math.h>
#include "Point2D.h"
#include "Circle.h"

using cv::Vec2d;
using namespace std;

namespace Geometry {
	class Rectangle {
	public:
		Rectangle(double left, double top, double width, double height) {
			_left = left;
			_top = top;
			_width = width;
			_height = height;
		}

		~Rectangle() {}

		inline double getLeft() const {
			return _left;
		}

		inline double getTop() const {
			return _top;
		}

		inline double getWidth() const {
			return _width;
		}

		inline double getHeight() const {
			return _height;
		}

		inline double getRight() const {
			return _left + _width;
		}

		inline double getBottom() const {
			return _top + _height;
		}

		void scaleToBoundingCircle(const Circle &circle) {
			Vec2d normalVectorFromCenterToTopLeftCorner = cv::normalize(Vec2d(_width * 0.5, _height * 0.5));
			Point2D topRightCorner = Point2D(normalVectorFromCenterToTopLeftCorner[0], normalVectorFromCenterToTopLeftCorner[1]) * circle.getRadius();
			Point2D newWidthAndHeight = topRightCorner * 2;

			_width = newWidthAndHeight.x - 4;
			_height = newWidthAndHeight.y - 4;
		}

		void centerInCircle(const Circle &circle) {
			Point2D leftTop = circle.getCenter() - (Point2D(_width, _height) * 0.5);
			_left = leftTop.x;
			_top = leftTop.y;
		}

	private:
		double _top;
		double _left;
		double _width;
		double _height;
	};
}

#endif // !_RECTANGLE_H_

