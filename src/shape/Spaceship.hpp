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
#ifndef NON_GRAVITAR_SPACESHIP_HPP
#define NON_GRAVITAR_SPACESHIP_HPP

#include "Fuel.hpp"
#include "TractorBeam.hpp"
#include "ClosedShape.hpp"
#include "Rectangle.hpp"
#include "ShapeVisitor.hpp"
#include "utils/BoundingPolygon.hpp"


namespace gvt {
	struct FuelEvent: public gvt::Event {
			unsigned oldAmount, newAmount;

			FuelEvent(unsigned old, unsigned _new);
	};

	class Spaceship: public ClosedShape {
		private:
			// Represents the current fuel amount in the ship
			unsigned mFuel;
			shared_ptr<TractorBeam> mBeam;

			EventDispatcher<FuelEvent> mFuelDisp;

			/** Width and height properties of any given spaceship. Note that
			 * these measures depend on the texture data found in
			 * @c static/graphics/ and when the files herein found are changed
			 * (in dimension) the static width and height properties should be
			 * updated accordingly (gruntwork, but avoids the use of an
			 * external image library).
			 */
			static unsigned const constexpr WIDTH = 46;
			static unsigned const constexpr HEIGHT = 45;

			// Variables specifying the width and height and the bounding
			// polygon (which needs not necessarily be a rectangle).
			static unsigned const constexpr BOUNDING_WIDTH = 46;
			static unsigned const constexpr BOUNDING_HEIGHT = 42;

			BoundingPolygon polygonFactory() const;
		public:
			using Shape::position;
			using Shape::rotation;
			using Shape::destroyed;

			Spaceship(Vectord position, unsigned fuel);

			unsigned fuel() const;
			/**
			 * @brief Recharges the current @c Spaceship instance by the fuel
			 * amount found in @c fuel.
			 * @param fuel @c Fuel object.
			 */
			void rechargeFuel(Fuel &fuel);
			/**
			 * @brief Discharges the current <tt>Spaceship</tt> fuel by @c
			 * amount.
			 */
			void dischargeFuel(unsigned amount);
			/**
			 * @return @c true if the current @c Spaceship instance has still
			 * fuel in it, @c false otherwise.
			 */
			bool charged() const;

			shared_ptr<RoundMissile> shoot(
					double radius, double speed, long lifespan
			) const;
			inline shared_ptr<TractorBeam> tractorBeam();

			void position(Vectord position) override;
			void rotation(double r) override;
			void destroyed(bool destroyed) override;

			inline double width() const override;
			inline double height() const override;
			Vectord rotationCenter() const override;

			EventDispatcher<FuelEvent>& fuelDispatcher();

			void accept(ShapeVisitor &visitor) override;
			bool operator== (Shape const &o) const override;
	};
}


namespace gvt {
	shared_ptr<TractorBeam> Spaceship::tractorBeam() {
		return mBeam;
	}

	double Spaceship::width() const {
		return WIDTH;
	}

	double Spaceship::height() const {
		return HEIGHT;
	}
}


#endif
