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
#include "PlanetBuilder.hpp"
#include "shape/Bunker.hpp"
#include "shape/Fuel.hpp"
#include "shape/MountainChain.hpp"


namespace gvt {
	shared_ptr<Planet> PlanetBuilder::getPlanet() {
		return mPlanet;
	}


	RandomPlanetBuilder::RandomPlanetBuilder(
			Vectord radiusRange, unsigned mountainPieces, unsigned bunkers,
			unsigned fuelTanks
	): mRadius{radiusRange.x, radiusRange.y}, mMountainPieces{mountainPieces},
	   mBunkers{bunkers}, mTanks{fuelTanks} {
		mTaken.resize(mountainPieces);
	}

	void RandomPlanetBuilder::buildPlanet() {
		mPlanet.reset(new Planet({0, 0}, mRadius()));

		mTaken.assign(mTaken.size(), false);
		mPlanet->surface(std::make_shared<PlanetSurface>());
		mPlanet->bonus(1000 * mBonus());
	}

	void RandomPlanetBuilder::buildMountains() {
		mPlanet->surface()->insert(
				MountainChain::randomChain({0, 1200}, mMountainPieces)
		);
	}

	void RandomPlanetBuilder::buildBunkers() {
		UniRandom<unsigned long> randomPos{0, mTaken.size()};
		UniRandom<unsigned> randomDir{2, 3};
		unsigned long pos;

		for (unsigned i = 0; i < mBunkers; i++) {
			auto b = std::make_shared<Bunker>(Vectord{0, 0}, randomDir());

			do {
				pos = randomPos();
			} while (mTaken[pos]);

			mTaken[pos] = true;
			mPlanet->surface()->mountains()->align(pos, b);
			mPlanet->surface()->insert(b);
		}
	}

	void RandomPlanetBuilder::buildFuelTanks() {
		auto randomPos = UniRandom<unsigned long>(0, mTaken.size());
		auto capacity = UniRandom<unsigned>(1, 3);
		unsigned long pos;

		for (unsigned i = 0; i < mTanks; i++) {
			auto f = std::make_shared<Fuel>(Vectord{0, 0}, 100 * capacity());

			do {
				pos = randomPos();
			} while (mTaken[pos]);

			mTaken[pos] = true;
			mPlanet->surface()->mountains()->align(pos, f);
			mPlanet->surface()->insert(f);
		}
	}
}
