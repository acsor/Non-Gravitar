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
#include <random>
#include <cmath>
#include <ctime>
#include "Bunker.hpp"
#include "bounding-polygon/BoundingRectangle.hpp"

using Bunker = gvt::Bunker;
using Bunker2D = gvt::Bunker2D;
using Bunker3D = gvt::Bunker3D;
using Rectangle = gvt::Rectangle;
using RoundMissile = gvt::RoundMissile;
using Shape = gvt::Shape;


Bunker::Bunker(Vectorf position, size_t directions):
	Shape(position), mPaths{directions} {
	std::uniform_real_distribution<float> angles{
		static_cast<float>(mRotation - M_PI / 2.0),
		static_cast<float>(mRotation + M_PI / 2.0)
	};
	std::default_random_engine e(time(NULL));

	while (directions > 0) {
		mPaths[directions - 1] = Vectorf(angles(e));

		directions--;
	}
}

RoundMissile Bunker::shoot() {
	// Bear in mind that by default, on the graphics layer the Bunker is
	// rotated by default by 90. deg (the normal out of its ceiling has
	// direction (1, 0))
	RoundMissile m{
		mPosition + Vectorf{height(), static_cast<float>(width() / 2.0)}
	};

	m.rotation(mRotation);
	m.velocity(mPaths[mCurr]);
	mCurr = (mCurr + 1) % mPaths.size();

	return m;
}

void Bunker::accept (ShapeVisitor &visitor) {
	visitor.visitBunker(*this);
}

gvt::BoundingPolygon Bunker::collisionPolygon() const {
    BoundingRectangle r = {
		mPosition, mPosition + Vectorf{COLLIDING_WIDTH, COLLIDING_HEIGHT}
    };
    r.rotate(mRotation);

    return r;
}

bool Bunker::operator== (Shape const &o) const {
	auto other = dynamic_cast<Bunker const *>(&o);

	if (other)
		return mPaths == other->mPaths && Shape::operator==(o);

	return false;
}


Bunker2D::Bunker2D(Vectorf position): Bunker(position, 2) {
}

bool Bunker2D::operator== (Shape const &o) const {
	auto other = dynamic_cast<Bunker2D const *>(&o);

	if (other)
		return Bunker::operator==(o);

	return false;
}


Bunker3D::Bunker3D(Vectorf position): Bunker(position, 3) {
}

bool Bunker3D::operator== (Shape const &o) const {
	auto other = dynamic_cast<Bunker3D const *>(&o);

	if (other)
		return Bunker::operator==(o);

	return false;
}
