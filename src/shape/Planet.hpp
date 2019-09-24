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
#ifndef NON_GRAVITAR_PLANET_HPP
#define NON_GRAVITAR_PLANET_HPP

#include "CRPolygon.hpp"
#include "utils/Vector.hpp"


namespace gvt {
	class PlanetSurface;

	class Planet: public CRPolygon {
		protected:
			unsigned mBonus{0};
			shared_ptr<PlanetSurface> mSurface;
		public:
			using Shape::position;

			Planet (Vectord position, double radius);

			void surface(shared_ptr<PlanetSurface> s);
			/**
			 * @return The @c PlanetSurface of this @c Planet, comprising an
			 * area where various mountains, bunkers and other game objects
			 * are placed.
			 */
			shared_ptr<PlanetSurface> surface();

			/**
			 * Setter method of bonus().
			 */
			inline void bonus(unsigned bonus);
			/**
			 * @return Bonus points received upon the destruction of this
			 * planet.
			 */
			inline unsigned bonus() const;

			void accept (ShapeVisitor &visitor) override;
			bool operator== (Shape const &o) const override;
	};
}


namespace gvt {
	void Planet::bonus(unsigned bonus) {
		mBonus = bonus;
	}

	unsigned Planet::bonus() const {
		return mBonus;
	}
}


#endif