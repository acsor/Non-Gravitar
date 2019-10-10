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
#ifndef NON_GRAVITAR_PLANET_BUILDER_HPP
#define NON_GRAVITAR_PLANET_BUILDER_HPP

#include "shape/Planet.hpp"
#include "PlanetSurface.hpp"


namespace gvt {
	/**
	 * A builder class aiding in the construction of @c Planet objects.
	 *
	 * @see https://en.wikipedia.org/wiki/Builder_pattern
	 */
	class PlanetBuilder {
		protected:
			shared_ptr<Planet> mPlanet;

			PlanetBuilder() = default;
		public:
			virtual void buildPlanet() {};
			virtual void buildMountains() {};
			virtual void buildBunkers() {};
			virtual void buildFuelTanks() {};

			shared_ptr<Planet> getPlanet();
	};

	class RandomPlanetBuilder: public PlanetBuilder {
		private:
			UniRandom<double> mRadius;
			UniRandom<unsigned> mBonus {1, 5};
			unsigned const mMountainPieces, mBunkers, mTanks;

			std::vector<bool> mTaken;
		public:
			RandomPlanetBuilder(
				Vectord radiusRange, unsigned mountainPieces, unsigned bunkers,
				unsigned fuelTanks
			);

			void buildPlanet() override;
			void buildMountains() override;
			void buildBunkers() override;
			void buildFuelTanks() override;
	};
}


#endif