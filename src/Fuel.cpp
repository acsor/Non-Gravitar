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


Rectangle Rectangle::collisionBox() const {
	// TO-DO This implementation is outright wrong, indeed we have yet no
	// possibility to specify tilted rectangles, but only one whose sides are
	// perpendicular to the x and y axes
	return Rectangle(mX, mY, mWidth, mHeight);
}

Fuel::Fuel(float xcoord, float ycoord, size_t fuel):
	PlaneObject(xcoord, ycoord), WidthTrait(Fuel::DEFAULT_WIDHT),
	HeightTrait(Fuel::DEFAULT_HEIGHT) {
	mFuel = fuel;
}

size_t Fuel::fuel() const {
	return mFuel;
}

void Fuel::recharge(Spaceship &ship) {
	// TO-DO Implement
}

bool Fuel::operator== (PlaneObject const &o) const {
	auto *other = dynamic_cast<Fuel const *>(&o);

	if (other)
		return PlaneObject::operator==(*other) && mFuel == other->mFuel;

	return false;
}
