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
#include "Rectangle.hpp"
#include "Utils.hpp"

using Rectangle = gvt::Rectangle;


size_t std::hash<Rectangle>::operator()(Rectangle const &r) const {
	auto h = hash<float>{};

	return h(r.mX) ^ h(r.mY) ^ h(r.mEnd.x()) ^ h(r.mEnd.y());
}

bool std::equal_to<Rectangle>::operator()(
	Rectangle const &r1, Rectangle const &r2
) const {
	return r1 == r2;
}

std::ostream& std::operator<< (std::ostream &out, Rectangle const &r) {
	// TO-DO Learn and eventually tweak the output conversion of your types.
	// Also learn to use manipulators
	out << "{" << r.mX << ", " << r.mY << ", " << r.mEnd.x() << ", " <<
		r.mEnd.y() << "}";

	return out;
}


void Rectangle::rotate() {
	// TO-DO Implement
}

Rectangle Rectangle::collisionBox() const {
	return *this;
}

Rectangle::Rectangle(Point topLeft, Point bottomRight):
	PlaneObject(topLeft.x(), topLeft.y()), mEnd{bottomRight} {
}

bool Rectangle::clashes(Rectangle const &o) const {
	// TO-DO Update with reference to rotation
	return IN_CLOSED_INTERVAL(mX - o.mX, -width(), o.width()) &&
			IN_CLOSED_INTERVAL(mY - o.mY, -height(), o.height());
}

bool Rectangle::operator==(PlaneObject const &o) const {
	auto *other = dynamic_cast<Rectangle const *>(&o);

	if (other) {
		return mX == other->mX && mY == other->mY && mEnd == other->mEnd;
	}

	return false;
}

float Rectangle::width() const {
	return abs(mEnd.x() - mX);
}

float Rectangle::height() const {
	return abs(mEnd.y() - mY);
}
