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
#include "TractorBeam.hpp"


namespace gvt {
	TractorBeam::TractorBeam (Vectord position, Spaceship &spaceship):
			Shape2D(position), mSpaceship(spaceship) {
	}

	Vectord TractorBeam::rotationCenter() const {
		return Vectord{0, -mSpaceship.height()} + mSpaceship.rotationCenter();
	}

	BoundingPolygon TractorBeam::collisionPolygon() const {
		auto t = BoundingPolygon::triangle(
				{0, HEIGHT}, {WIDTH / 2.0, 0}, {WIDTH, HEIGHT}
		);

		t.position(mPosition);
		t.rotate(mRotation, rotationCenter());

		return t;
	}

	void TractorBeam::accept(ShapeVisitor &visitor) {
		visitor.visitTractorBeam(*this);
	}

	bool TractorBeam::operator== (Shape const &o) const {
		auto b = dynamic_cast<TractorBeam const *>(&o);

		if (b)
			return Shape2D::operator==(o);

		return false;
	}
}