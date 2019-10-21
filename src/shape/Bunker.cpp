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
#include <cmath>
#include <ctime>
#include "Bunker.hpp"
#include "utils/Random.hpp"
#include "utils/BoundingPolygon.hpp"


namespace gvt {
	gvt::BoundingPolygon Bunker::polygonFactory() const {
		return BoundingPolygon::rectangle({0, 0}, {WIDTH, HEIGHT});
	}

	Bunker::Bunker(Vectord position, size_t directions):
			ClosedShape(position, polygonFactory()) {
		UniRandom<double> angles {0, M_PI};

		mDirections.resize(directions);

		while (directions > 0) {
			mDirections[directions - 1] = angles();

			directions--;
		}
	}

	shared_ptr<RoundMissile>
	Bunker::shoot(double speed, long lifespan, double radius) {
		auto m = std::make_shared<RoundMissile>(
				Vectord{0, 0}, lifespan, radius
		);
		auto localPos = Vectord{width() / 2.0, 0} - Vectord{radius, 3 * radius};
		auto missileDir = Vectord(mDirections[mCurr] + M_PI + mRotation);

		localPos.rotate(mRotation, rotationCenter());

		m->position(mPosition + localPos);
		m->velocity(speed * missileDir);
		mCurr = (mCurr + 1) % mDirections.size();

		return m;
	}

	void Bunker::accept (ShapeVisitor &visitor) {
		visitor.visitBunker(*this);
	}

	bool Bunker::operator== (Shape const &o) const {
		auto other = dynamic_cast<Bunker const *>(&o);

		if (other)
			return mDirections == other->mDirections && Shape::operator==(o);

		return false;
	}
}
