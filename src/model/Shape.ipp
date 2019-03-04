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


void gvt::Shape::x(float xcoord) {
    mX = xcoord;
	notify(MOVE);
}

void gvt::Shape::y(float ycoord) {
    mY = ycoord;
	notify(MOVE);
}

float gvt::Shape::x() const {
    return mX;
}

float gvt::Shape::y() const {
    return mY;
}

float gvt::Shape::originX () const {
	return mOriginX;
}

float gvt::Shape::originY () const {
	return mOriginY;
}

void gvt::Shape::rotation(float r) {
	// TO-DO Shorten, if at all possible, this code that I have produced, which
	// at first sight looks orribly bigger than it ought to be
	if (r >= 0)
		mRotation = r - (2.0 * M_PI) * floor(r / (2.0 * M_PI));
	else
		mRotation = r - (2.0 * M_PI) * ceil(r / (2.0 * M_PI));

	notify(ROTATION);
}

void gvt::Shape::rotate(float r) {
	rotation(mRotation + r);
}
