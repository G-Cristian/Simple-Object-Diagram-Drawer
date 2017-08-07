#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point2D.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using cv::Vec2d;

namespace Geometry {
	class Circle {
	public:
		Circle(Point2D center, float radius):_center(center), _radius(radius){
		}
		~Circle() {

		}

		inline Point2D getCenter() const {
			return _center;
		}

		inline float getRadius() const {
			return _radius;
		}

		double distanceFromCenterToOtherCenter(const Circle &other) const {
			Point2D diff = other._center - _center;
			return sqrt(diff.x * diff.x + diff.y * diff.y);
		}

		double distanceFromCircumferenceToOtherCircumference(const Circle &other) const {
			return distanceFromCenterToOtherCenter(other) - _radius - other._radius;
		}

		Point2D distanceVectorFromCircumferenceToOtherCircumference(const Circle &other) const {
			Point2D diff = other._center - _center;
			Vec2d distanceVec = Vec2d(diff.x, diff.y);
			Vec2d xAxisVec = Vec2d(1, 0);
			double distanceVecNorm = norm(distanceVec);
			//a.b = ||a|| * ||b|| * cos(angle)
			//cos(angle) = (a.b) / (||a|| * ||b||)
			// b = xAxis => b norm = xAxis norm = 1;
			double cosAngle = distanceVec.dot(xAxisVec) / distanceVecNorm;

			//||aXb|| = ||a|| * ||b|| * sin(angle)
			//sin(angle) = ||(aXb)|| / (||a|| * ||b||)
			// b = xAxis => b norm = xAxis norm = 1;
			//distanceVec X xAxisVec = distanceVec.x * xAxisVec.y - distanceVec.y * xAxisVec.x = distanceVec.x * 0 - distanceVec.y * 1 = -distanceVec.y.
			//But 'y' increases downway so it's '+distanceVec.y'
			double sinAngle = (distanceVec[1]) / distanceVecNorm;

			double distanceFromCircToOtherCirc = distanceFromCircumferenceToOtherCircumference(other);

			//cos(angle) = x/h
			//sin(angle) = y/h
			return Point2D(cosAngle * distanceFromCircToOtherCirc, sinAngle * distanceFromCircToOtherCirc);
		}

	private:
		Point2D _center;
		float _radius;
	};
}

#endif

