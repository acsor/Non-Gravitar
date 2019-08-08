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
#include <bounding-polygon/BoundingTriangle.hpp>
#include "Spaceship.hpp"

using Spaceship = gvt::Spaceship;
using Rectangle = gvt::Rectangle;


gvt::Vectorf const Spaceship::sCollisionOffset = {3, 0};


Spaceship::Spaceship(Vectorf position, unsigned fuel): Shape::Shape(position) {
	mFuel = fuel;
}

gvt::BoundingPolygon Spaceship::collisionPolygon() const {
	BoundingTriangle t = {
		mPosition + sCollisionOffset,
		mPosition + sCollisionOffset + Vectorf{
			height(), static_cast<float>(width() / 2.0)
		},
		mPosition + sCollisionOffset + Vectorf{0, width()}
	};
	
	t.rotate(mRotation);

	return t;
}

unsigned Spaceship::fuel() const {
	return mFuel;
}

void Spaceship::recharge(Fuel &fuel) {
	mFuel += fuel.fuel();
	fuel.empty();
}

void Spaceship::discharge(unsigned amount) {
	mFuel -= amount;
}

bool Spaceship::charged() const {
	return mFuel > 0;
}

void gvt::Spaceship::accept(gvt::ShapeVisitor &visitor) {
	visitor.visitSpaceship(*this);
}

bool Spaceship::operator==(Shape const &o) const {
	auto *other = dynamic_cast<Spaceship const *>(&o);

	if (other)
		return Shape::operator==(*other) && mFuel == other->mFuel;

	return false;
}

