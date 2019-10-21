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
#include "Fuel.hpp"
#include "Rectangle.hpp"
#include "utils/BoundingPolygon.hpp"


namespace gvt {
	BoundingPolygon Fuel::polygonFactory() const {
		return BoundingPolygon::rectangle({0, 0}, {WIDTH, HEIGHT});
	}
	
	Fuel::Fuel(Vectord position, unsigned initialCapacity):
			ClosedShape(position, polygonFactory()) {
		mFuel = initialCapacity;
	}

	unsigned Fuel::fuel() const {
		return mFuel;
	}

	void Fuel::empty() {
		mFuel = 0;
	}

	void Fuel::accept(ShapeVisitor &visitor) {
		visitor.visitFuel(*this);
	}

	double Fuel::width() const {
		return WIDTH;
	}

	double Fuel::height() const {
		return HEIGHT;
	}

	bool Fuel::operator== (Shape const &o) const {
		auto *other = dynamic_cast<Fuel const *>(&o);

		if (other)
			return Shape::operator==(*other) && mFuel == other->mFuel;

		return false;
	}
}
