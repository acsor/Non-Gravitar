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
#include "bounding-polygon/BoundingPolygon.hpp"
#include "Spaceship.hpp"
#include "RoundMissile.hpp"


namespace gvt {
	Spaceship::Spaceship(Vectord position, unsigned fuel):
			Shape2D::Shape2D(position) {
		mFuel = fuel;
	}

	gvt::BoundingPolygon Spaceship::collisionPolygon() const {
		auto t = BoundingPolygon::triangle(
			Vectord{0, BOUNDING_HEIGHT},
			Vectord{BOUNDING_WIDTH / 2.0, 0},
			Vectord{BOUNDING_WIDTH, BOUNDING_HEIGHT}
		);

		t.position(mPosition);
		t.rotate(mRotation, rotationCenter());

		return t;
	}

	unsigned Spaceship::fuel() const {
		return mFuel;
	}

	void Spaceship::rechargeFuel(Fuel &fuel) {
		auto e = std::make_shared<FuelChangedEvent>(mFuel, 0);

		mFuel += fuel.fuel();
		e->newAmount = mFuel;

		fuel.empty();

		notify(e);
	}

	void Spaceship::dischargeFuel(unsigned amount) {
		auto e = std::make_shared<FuelChangedEvent>(mFuel, 0);

		if (amount > mFuel)
			mFuel = 0;
		else
			mFuel -= amount;

		e->newAmount = mFuel;

		notify(e);
	}

	bool Spaceship::charged() const {
		return mFuel > 0;
	}

	shared_ptr<RoundMissile>
	Spaceship::shoot(double radius, double speed, long lifespan) const {
		// TODO Improve the initial missile position
		auto missile = std::make_shared<RoundMissile> (
			Vectord{0, 0}, lifespan, radius
		);
		auto localPos = Vectord{width() / 2.0, -10.0} - Vectord{
			missile->radius() / 2.0, missile->radius() / 2.0
		};

		localPos.rotate(rotation(), rotationCenter());
		missile->position(position() + localPos);
		missile->velocity(speed * Vectord(rotation() - M_PI / 2.0));

		return missile;
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


	FuelChangedEvent::FuelChangedEvent(unsigned old, unsigned _new) {
		oldAmount = old;
		newAmount = _new;
	}
}
