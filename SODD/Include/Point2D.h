#ifndef _POINT2D_H_
#define _POINT2D_H_

namespace Geometry {
	class Point2Di {
	public:
		Point2Di(int x, int y) {
			this->x = x;
			this->y = y;
		}
		~Point2Di() {

		}

		Point2Di operator+(const Point2Di &other) const {
			return Point2Di(this->x + other.x, this->y + other.y);
		}

		int x;
		int y;
	};
}

#endif

