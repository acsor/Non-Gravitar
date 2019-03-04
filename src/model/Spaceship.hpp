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
#ifndef NON_GRAVITAR_SPACESHIP_HPP
#define NON_GRAVITAR_SPACESHIP_HPP

#include "Fuel.hpp"
#include "Shape.hpp"
#include "ShapeTraits.hpp"
#include "Rectangle.hpp"


namespace gvt {
	class Spaceship: public Shape, public WidthTrait, public HeightTrait
	{
		private:
			// Represents the current fuel amount in the ship
			unsigned mFuel;
		protected:
			Rectangle collisionBox() const override;
		public:
			/** Width and height properties of any given spaceship. Note that
			 * these measures depend on the texture data found in
			 * @c static/graphics/ and when the files herein found are changed
			 * (in dimension) the static width and height properties should be
			 * updated accordingly (gruntwork, but avoids the use of an
			 * external image library).
			 */
			static unsigned const constexpr WIDTH = 45;
			static unsigned const constexpr HEIGHT = 46;

			Spaceship(float xcoord, float ycoord, unsigned fuel);
			unsigned fuel() const;
			/**
			 * @brief Recharges the current @c Spaceship instance by the fuel
			 * amount found in @c fuel.
			 * @param fuel @c Fuel object.
			 */
			void recharge(Fuel &fuel);
			/**
			 * @brief Discharges the current <tt>Spaceship</tt>'s fuel by @c
			 * amount, defaulted to @c 1.
			 *
			 * @todo Verify that we can specify a default argument value, and
			 * that Spaceship::discharge() can be specified even with no
			 * arguments.
			 */
			void discharge(unsigned amount = 1);
			/**
			 * @return @c true if the current @c Spaceship instance has still
			 * fuel in it, @c false othwerise.
			 */
			bool charged() const;

			inline float width() const override;
			inline float height() const override;

			bool operator== (Shape const &o) const override;
	};
}


float gvt::Spaceship::width() const {
	return WIDTH;
}

float gvt::Spaceship::height() const {
	return HEIGHT;
}



#endif
