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
#include "Point.hpp"
#include "Rectangle.hpp"


using Point = gvt::Point;


gvt::Rectangle gvt::Point::collisionBox() const {
	Point halfWidth{WIDTH_BBOX / 2.0, WIDTH_BBOX / 2.0};

	// TO-DO Check/unit test this
	return Rectangle{*this - halfWidth, *this + halfWidth};
}

void Point::rotate() {
	// TO-DO Implement
}

Point::Point(float xcoord, float ycoord): PlaneObject(xcoord, ycoord) {
}

float Point::distance(Point const &o) const {
	return sqrt(pow(mX - o.mX, 2) + pow(mY - o.mY, 2));
}

Point gvt::Point::operator+ (Point const &o) const {
	return Point{mX + o.mX, mY + o.mY};
}

Point gvt::Point::operator- (Point const &o) const {
	return Point{mX - o.mX, mY - o.mY};
}

Point gvt::operator* (float factor, Point const &p) {
	return Point{factor * p.mX, factor * p.mY};
}

bool Point::operator== (PlaneObject const &o) const {
	auto *other = dynamic_cast<Point const *>(&o);

	if (other)
		return PlaneObject::operator==(*other);

	return false;
}
