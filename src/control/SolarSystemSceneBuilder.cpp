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
#include "SolarSystemSceneBuilder.hpp"
#include "shape/SpawnArea.hpp"


namespace gvt {
	SolarSystemSceneBuilder& SolarSystemSceneBuilder::centerPosition(
			Vectord center
	) {
		mCenter = center;

		return *this;
	}

	SolarSystemSceneBuilder& SolarSystemSceneBuilder::planetsNumber(
			unsigned planetsNum
	) {
		mPlanets = planetsNum;

		return *this;
	}

	SolarSystemSceneBuilder& SolarSystemSceneBuilder::planetsLayout(
			shared_ptr<ShapeLayout> layout
	) {
		mLayout = std::move(layout);

		return *this;
	}

	SolarSystemSceneBuilder& SolarSystemSceneBuilder::planetBuilder(
			shared_ptr<PlanetBuilder> b
	) {
		mBuilder = std::move(b);

		return *this;
	}

	shared_ptr<SolarSystemScene> SolarSystemSceneBuilder::operator() () {
		auto s = std::make_shared<SolarSystem>();

		s->insert(std::make_shared<SpawnArea>(mCenter, 50));

		for (unsigned i = 0; i < mPlanets; i++) {
			mBuilder->buildPlanet();
			mBuilder->buildMountains();
			mBuilder->buildBunkers();
			mBuilder->buildFuelTanks();

			auto p = mBuilder->getPlanet();
			mLayout->operator()(p, i);

			s->insert(p);
		}

		return std::make_shared<SolarSystemScene>(2 * mCenter, s, *this);
	}
}
