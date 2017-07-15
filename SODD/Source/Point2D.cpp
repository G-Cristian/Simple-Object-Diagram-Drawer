#include "../Include/Point2D.h"

namespace Geometry {
	Point2Di operator*(double n, const Point2Di &p) {
		return p*n;
	}
}