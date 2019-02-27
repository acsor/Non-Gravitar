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


Rectangle Fuel::collisionBox() const {
	// TO-DO This implementation is outright wrong, indeed we have yet no
	// possibility to specify tilted rectangles, but only one whose sides are
	// perpendicular to the x and y axes
	Rectangle r =  {
		{mX - mOriginX, mY - mOriginY},
		{mX + WIDTH - mOriginX, mY + HEIGHT - mOriginY}
	};
	r.rotation(mRotation);

	return r;
}

Fuel::Fuel(float xcoord, float ycoord, unsigned fuel):
	PlaneObject(xcoord, ycoord) {
	mFuel = fuel;
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

bool Fuel::operator== (PlaneObject const &o) const {
	auto *other = dynamic_cast<Fuel const *>(&o);

	if (other)
		return PlaneObject::operator==(*other) && mFuel == other->mFuel;

	return false;
}
