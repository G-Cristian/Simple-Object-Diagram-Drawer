#ifndef _LINE_H_
#define _LINE_H_

#include <opencv2/core.hpp>
#include <math.h>
#include "Point2D.h"
#include "Circle.h"

using cv::Vec2d;
using namespace std;

namespace Geometry {
	class Line {
	public:
		Line(Point2Di p1, Point2Di p2):_p1(p1), _p2(p2) {
		}
		~Line() {

		}

		inline Point2Di getPoint1() const {
			return _p1;
		}

		inline Point2Di getPoint2() const {
			return _p2;
		}

		//Precondition: There is at least one collition point.
		Point2Di firstCollitionPointAgainstCircle(const Circle &circle) const{
			//I want line as _p1 + t*d
			Point2Di d = (_p2 - _p1);
			Point2Di v = _p1 - circle.getCenter();
			float r = circle.getRadius();

			double a = Vec2d(d.x, d.y).dot(Vec2d(d.x, d.y));
			double b = Vec2d(2 * d.x, 2 * d.y).dot(Vec2d(v.x, v.y));
			double c = Vec2d(v.x, v.y).dot(Vec2d(v.x, v.y)) - (r*r);

			pair<double, double> t1t2 = solveQuadraticEquation(a,b,c);

			if (abs(t1t2.first) < abs(t1t2.second)) {
				return _p1 + d*t1t2.first;
			}
			else {
				return _p1 + d*t1t2.second;
			}
		}

	private:
		//Precondition: It has at least one real solution
		pair<double, double> solveQuadraticEquation(double a, double b, double c) const{
			double sqrRootPart = sqrt(b*b - 4 * a*c);

			return pair<double, double>((-b + sqrRootPart) / (2 * a), (-b - sqrRootPart) / (2 * a));
		}

		Point2Di _p1;
		Point2Di _p2;
	};
}

#endif
