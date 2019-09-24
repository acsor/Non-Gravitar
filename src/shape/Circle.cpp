// MIT License
//
// Copyright (c) 2018 Oscar B. et al.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <cmath>
#include "utils/BoundingPolygon.hpp"
#include "shape/Circle.hpp"
#include "utils/Utils.hpp"
#include "shape/ShapeVisitor.hpp"


namespace gvt {
	BoundingPolygon Circle::polygonFactory(double radius) const {
		auto polygon = BoundingPolygon(8);
		auto const center = Vectord{radius, radius};
		auto const step = 2.0 * M_PI / COLLISION_PRECISION;

		for (unsigned vertex = 0; vertex < COLLISION_PRECISION; vertex++)
			polygon[vertex] = center + radius * Vectord(step * vertex);

		return polygon;
	}

	Circle::Circle(Vectord position, double radius):
			ClosedShape{position, polygonFactory(radius)}, mRadius{radius} {
	}

	bool Circle::clashes(Circle const &o) const {
		// TODO Test
		return (mPosition + Vectord{mRadius, mRadius}).distance(
				o.mPosition + Vectord{o.mRadius, o.mRadius}
		) <= mRadius + o.mRadius;
	}

	void Circle::accept (ShapeVisitor &visitor) {
		visitor.visitCircle(*this);
	}

	bool Circle::operator== (Shape const &o) const {
		auto *other = dynamic_cast<Circle const *>(&o);

		if (other)
			return Shape::operator==(*other) && mRadius == other->mRadius;

		return false;
	}
}
