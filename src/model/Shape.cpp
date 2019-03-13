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
#include "Shape.hpp"
#include "Rectangle.hpp"

using Event = gvt::Event;
using Shape = gvt::Shape;
using Trajectory = gvt::Trajectory;


const Event Shape::MOVE = Event::create();
const Event Shape::ORIGIN = Event::create();
const Event Shape::ROTATION = Event::create();
const Event Shape::DESTROIED = Event::create();


Shape::Shape(float x, float y): mX{x}, mY{y} {
}

Shape::~Shape() {
	Event e = DESTROIED;
	e.data = this;

	notify(e);
}

void Shape::origin(float xcoord, float ycoord) {
	Event e = ORIGIN;

	mOriginX = xcoord;
	mOriginY = ycoord;
	e.data = this;

	notify(e);
}

void Shape::velocity(Trajectory const &t) {
	mVelocity = t;
}

Trajectory Shape::velocity() const {
	return mVelocity;
}

float Shape::speed() const {
	return mVelocity.norm();
}

bool Shape::clashes(gvt::Shape const &o) const {
    return collisionBox().clashes(o.collisionBox());
}

void Shape::move(float xcoord, float ycoord) {
	Event e = MOVE;

    mX += xcoord;
    mY += ycoord;
	e.data = this;

	notify(e);
}

void Shape::moveAlong(Trajectory const &t) {
	Event e = MOVE;

	mX += t.x;
	mY += t.y;
	e.data = this;

	notify(e);
}

bool Shape::operator== (Shape const &o) const {
	return mX == o.mX && mY == o.mY && mOriginX == o.mOriginX &&
			mOriginY == o.mOriginY && mRotation == o.mRotation &&
			mVelocity == mVelocity;
}

bool Shape::operator!= (Shape const &o) const {
	return !operator==(o);
}
