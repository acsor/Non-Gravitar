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

using Shape = gvt::Shape;
using ShapeEvent = gvt::ShapeEvent;
using Trajectory = gvt::Vectorf;


Shape::Shape(float x, float y): mX{x}, mY{y} {
}

Shape::~Shape() {
	ShapeEvent e{ShapeEvent::Type::destroyed, this};

	notify(&e);
}

void Shape::move(float xcoord, float ycoord) {
	ShapeEvent e{ShapeEvent::Type::moved, this};

	mX += xcoord;
    mY += ycoord;

	notify(&e);
}

void Shape::moveAlong(Vectorf const &t) {
	ShapeEvent e{ShapeEvent::Type::moved, this};

	mX += t.x;
	mY += t.y;

	notify(&e);
}

void Shape::origin(float xcoord, float ycoord) {
	ShapeEvent e{ShapeEvent::Type::origin, this};

	mOriginX = xcoord;
	mOriginY = ycoord;

	notify(&e);
}

void Shape::velocity(Vectorf const &t) {
	mVelocity = t;
}

Trajectory Shape::velocity() const {
	return mVelocity;
}

float Shape::speed() const {
	return mVelocity.norm();
}

void Shape::acceleration(Vectorf const &a) {
	mAcceleration = a;
}

gvt::Vectorf Shape::acceleration() const {
	return mAcceleration;
}


bool Shape::clashes(gvt::Shape const &o) const {
    return globalBounds().clashes(o.globalBounds());
}

bool Shape::operator== (Shape const &o) const {
	return mX == o.mX && mY == o.mY && mOriginX == o.mOriginX &&
			mOriginY == o.mOriginY && mRotation == o.mRotation &&
			mVelocity == mVelocity;
}

bool Shape::operator!= (Shape const &o) const {
	return !operator==(o);
}
