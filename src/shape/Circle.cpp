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
#include "Circle.hpp"
#include "Utils.hpp"

using Circle = gvt::Circle;
using Shape = gvt::Shape;
using Rectangle = gvt::Rectangle;


Circle::Circle(float xcoord, float ycoord): Circle{xcoord, ycoord, 0} {
}

Circle::Circle(float xcoord, float ycoord, float radius):
	Shape{xcoord, ycoord}, mRadius{radius} {
	mOriginX = radius;
	mOriginY = radius;
}

float Circle::area() const {
	return M_PI * pow(mRadius, 2);
}

bool Circle::clashes(Circle const &o) const {
	// TO-DO Test
	return sqrt(
		pow(mX + mRadius - mOriginX - (o.mX + mRadius - o.mOriginX), 2) +
		pow(mY + mRadius - mOriginY - (o.mY + mRadius - o.mOriginY), 2)
	) <= mRadius + o.mRadius;
}

void Circle::accept (ShapeVisitor &visitor) {
	visitor.visitCircle(*this);
}

Rectangle Circle::globalBounds() const {
	// TO-DO Improve by taking into account rotation as well
	Rectangle r = Rectangle{
		{mX, mY}, {mX + 2 * mRadius, mY + 2 * mRadius}
	};

	r.origin(mRadius, mRadius);
	r.rotation(mRotation);

	return r;
}

bool Circle::operator== (Shape const &o) const {
	auto *other = dynamic_cast<Circle const *>(&o);

	if (other)
		return Shape::operator==(*other) && mRadius == other->mRadius;

	return false;
}
