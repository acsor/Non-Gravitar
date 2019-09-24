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
#include "utils/BoundingPolygon.hpp"
#include "Spaceship.hpp"
#include "RoundMissile.hpp"


namespace gvt {
	FuelEvent::FuelEvent(unsigned old, unsigned _new) {
		oldAmount = old;
		newAmount = _new;
	}


	BoundingPolygon Spaceship::polygonFactory() const {
		return BoundingPolygon::triangle(
				Vectord{0, BOUNDING_HEIGHT}, Vectord{BOUNDING_WIDTH / 2.0, 0},
				Vectord{BOUNDING_WIDTH, BOUNDING_HEIGHT}
		);
	}

	Spaceship::Spaceship(Vectord position, unsigned fuel):
			ClosedShape::ClosedShape(position, polygonFactory()), mFuel{fuel} {
		mBeam = std::make_shared<TractorBeam>(Vectord{0, height()}, *this);
	}

	void Spaceship::position(Vectord position) {
		ClosedShape::position(position);
		auto widthDiff = width() - mBeam->width();

		mBeam->position(position + Vectord{widthDiff / 2.0, height()});
	}

	void Spaceship::rotation(double r) {
		ClosedShape::rotation(r);

		mBeam->rotation(r);
	}

	void Spaceship::destroyed(bool destroyed) {
		ClosedShape::destroyed(destroyed);

		mBeam->destroyed(destroyed);
	}

	Vectord Spaceship::rotationCenter() const {
		return {BOUNDING_WIDTH / 2.0, BOUNDING_HEIGHT / 2.0};
	}

	unsigned Spaceship::fuel() const {
		return mFuel;
	}

	void Spaceship::rechargeFuel(Fuel &fuel) {
		auto e = FuelEvent(mFuel, 0);

		mFuel += fuel.fuel();
		e.newAmount = mFuel;

		fuel.empty();

		mFuelDisp.raiseEvent(e);
	}

	void Spaceship::dischargeFuel(unsigned amount) {
		auto e = FuelEvent(mFuel, 0);

		if (amount > mFuel)
			mFuel = 0;
		else
			mFuel -= amount;

		e.newAmount = mFuel;

		mFuelDisp.raiseEvent(e);
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

		localPos.rotate(Shape::rotation(), rotationCenter());
		missile->position(Shape::position() + localPos);
		missile->velocity(
			(speed + this->speed()) * Vectord(Shape::rotation() - M_PI / 2.0)
		);

		return missile;
	}

	void Spaceship::accept(ShapeVisitor &visitor) {
		visitor.visitSpaceship(*this);
	}

	EventDispatcher<FuelEvent>& Spaceship::fuelDispatcher() {
		return mFuelDisp;
	}

	bool Spaceship::operator==(Shape const &o) const {
		auto *other = dynamic_cast<Spaceship const *>(&o);

		if (other)
			return Shape::operator==(*other) && mFuel == other->mFuel;

		return false;
	}
}
