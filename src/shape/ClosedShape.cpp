// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#include "ClosedShape.hpp"


namespace gvt {
	ClosedShape::ClosedShape(Vectord pos, BoundingPolygon cp):
			Shape(pos), mPolygon{std::move(cp)} {
		mPolygon.position(pos);
	}

	void ClosedShape::position(Vectord p) {
		Shape::position(p);

		mPolygon.position(p);
	}

	void ClosedShape::rotation(double r) {
		auto oldRotation = mRotation;

		Shape::rotation(r);

		mPolygon.rotate(r - oldRotation, rotationCenter());
	}

	bool ClosedShape::clashes(Shape const &o) const {
		auto closed = dynamic_cast<ClosedShape const *>(&o);

		// If `o' is an instance of ClosedShape, we know how to detect collisions
		if (closed) {
			return collisionPolygon().intersects(closed->collisionPolygon());
			// otherwise, we delegate the task to `o', which might know more
			// about this all
		} else {
			return o.clashes(*this);
		}
	}

	BoundingPolygon ClosedShape::collisionPolygon() const {
		return mPolygon;
	}
}
