#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include "Point2D.h"

namespace Geometry {
	class Circle {
	public:
		Circle(Point2Di center, float radius):_center(center), _radius(radius){
		}
		~Circle() {

		}

		inline Point2Di getCenter() const {
			return _center;
		}

		inline float getRadius() const {
			return _radius;
		}
	private:
		Point2Di _center;
		float _radius;
	};
}

#endif

