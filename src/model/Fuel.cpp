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
#include "Fuel.hpp"
#include "Rectangle.hpp"

using namespace gvt;


Fuel::Fuel(float xcoord, float ycoord, unsigned fuel):
	Shape(xcoord, ycoord) {
	mFuel = fuel;
	mOriginX = WIDTH / 2;
	mOriginY = HEIGHT / 2;
}

unsigned Fuel::fuel() const {
	return mFuel;
}

void Fuel::empty() {
	mFuel = 0;
}

float Fuel::width() const {
	return Fuel::WIDTH;
}

float Fuel::height() const {
	return Fuel::HEIGHT;
}

Rectangle Fuel::collisionBox() const {
	Rectangle r =  {
		{mX, mY}, {mX + WIDTH, mY + HEIGHT}
	};
	r.origin(mOriginX, mOriginY);
	r.rotation(mRotation);

	return r;
}

bool Fuel::operator== (Shape const &o) const {
	auto *other = dynamic_cast<Fuel const *>(&o);

	if (other)
		return Shape::operator==(*other) && mFuel == other->mFuel;

	return false;
}
