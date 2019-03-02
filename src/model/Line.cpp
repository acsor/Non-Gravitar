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
#include "Line.hpp"

using namespace gvt;

using Line = gvt::Line;
using Point = gvt::Point;
using Rectangle = gvt::Rectangle;


Rectangle Line::collisionBox() const {
	// TO-DO Enhance the collision box creation by minimizing the area covered
	// by the rectangle
	return Rectangle({mX, mY}, mEnd);
}

void Line::rotate() {
	// TO-DO Implement
}

Line::Line(Point const &start, Point const &end):
	Shape(start.x(), start.y()), mEnd{end} {
}

Line& Line::operator* (double factor) {
	if (factor <= 0)
		throw std::domain_error("scaling factor cannot be <= 0");

	mEnd = factor * mEnd;

	return *this;
}

bool Line::operator== (Shape const &o) const {
	auto other = dynamic_cast<Line const *>(&o);

	if (other)
		return Shape::operator==(*other) && mEnd == other->mEnd;

	return false;
}

float Line::width() const {
	return Point(mX, mY).distance(mEnd);
}
