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
#include "bounding-polygon/BoundingRectangle.hpp"
#include "Rectangle.hpp"
#include "utils/Utils.hpp"

using Rectangle = gvt::Rectangle;


size_t std::hash<Rectangle>::operator()(Rectangle const &r) const {
	auto h = hash<float>{};

	return h(r.mPosition.x) ^ h(r.mPosition.y) ^ h(r.mEnd.x) ^ h(r.mEnd.y);
}

bool std::equal_to<Rectangle>::operator()(
	Rectangle const &r1, Rectangle const &r2
) const {
	return r1 == r2;
}

std::ostream& std::operator<< (std::ostream &out, Rectangle const &r) {
	// TODO Learn and eventually tweak the output conversion of your types.
	//  Also learn to use manipulators
	out << "{" << r.mPosition.x << ", " << r.mPosition.y << ", " << r.mEnd.x
			<< ", " << r.mEnd.y << "}";

	return out;
}


void Rectangle::accept (ShapeVisitor &visitor) {
	visitor.visitRectangle(*this);
}

gvt::BoundingPolygon Rectangle::collisionPolygon() const {
    BoundingRectangle r {mPosition, mPosition + Vectorf{width(), height()}};

    r.rotate(mRotation);

    return r;
}

Rectangle::Rectangle(Vectorf topLeft, Vectorf bottomRight):
	Shape(topLeft), mEnd{bottomRight} {
}

bool Rectangle::operator==(Shape const &o) const {
	auto *other = dynamic_cast<Rectangle const *>(&o);

	if (other)
		return Shape::operator==(*other) && mEnd == other->mEnd;

	return false;
}

float Rectangle::width() const {
	return std::abs(mEnd.x - mPosition.x);
}

float Rectangle::height() const {
	return std::abs(mEnd.y - mPosition.y);
}
