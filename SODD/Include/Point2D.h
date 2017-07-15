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
			return Point2Di(x + other.x, y + other.y);
		}

		Point2Di operator-() const {
			return Point2Di(-x, -y);
		}

		Point2Di operator-(const Point2Di &other) const {
			return *this + (-other);
		}

		Point2Di operator*(double n) const{
			return Point2Di(x*n, y*n);
		}

		int x;
		int y;
	};

	Point2Di operator*(double n, const Point2Di &p);
}

#endif

