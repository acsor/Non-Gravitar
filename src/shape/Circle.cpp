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
#include <bounding-polygon/BoundingRectangle.hpp>
#include "Circle.hpp"
#include "utils/Utils.hpp"

using Circle = gvt::Circle;
using Shape = gvt::Shape;
using Rectangle = gvt::Rectangle;


Circle::Circle(Vectorf position, float radius):
	Shape{position}, mRadius{radius} {
}

bool Circle::clashes(Circle const &o) const {
	// TODO Test
	return (mPosition + Vectorf{mRadius, mRadius}).distance(
			o.mPosition + Vectorf{o.mRadius, o.mRadius}
	) <= mRadius + o.mRadius;
}

void Circle::accept (ShapeVisitor &visitor) {
	visitor.visitCircle(*this);
}

gvt::BoundingPolygon Circle::collisionPolygon() const {
	BoundingPolygon r = BoundingRectangle{
		mPosition, mPosition + 2 * Vectorf{mRadius, mRadius}
	};

	r.rotate(mRotation);

	return r;
}

bool Circle::operator== (Shape const &o) const {
	auto *other = dynamic_cast<Circle const *>(&o);

	if (other)
		return Shape::operator==(*other) && mRadius == other->mRadius;

	return false;
}
