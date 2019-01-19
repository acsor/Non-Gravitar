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
#ifndef NON_GRAVITAR_FUEL_HPP
#define NON_GRAVITAR_FUEL_HPP

#include "PlaneObject.hpp"
#include "PlaneTraits.hpp"


namespace gvt {
	class Spaceship;


	class Fuel: public PlaneObject, public WidthTrait, public HeightTrait {
		private:
			size_t mFuel;
		protected:
			Rectangle collisionBox() const override;
		public:
			static float const constexpr DEFAULT_WIDHT = 4;
			static float const constexpr DEFAULT_HEIGHT = 5;

			Fuel(float xcoord, float ycoord, size_t fuel);
			/**
			 * @returns The current fuel amount.
			 */
			size_t fuel() const;
			/**
			 * @brief Recharges the given Spaceship argument by the total
			 * fuel amount available in the current Fuel instance. After the
			 * call, this->fuel() == 0.
			 * @param ship Spaceship instance to recharge.
			 */
			void recharge(Spaceship &ship);

			bool operator== (PlaneObject const &o) const override;
	};
}


#endif
