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
#include <stdexcept>
#include <utils/Random.hpp>
#include "PlanetSurface.hpp"
#include "shape/Fuel.hpp"


namespace gvt {
	void PlanetSurface::onRemoveShape (shared_ptr<Shape> s) {
		CollisionGroup::onRemoveShape(s);

		if (auto bunker = std::dynamic_pointer_cast<Bunker>(s))
			mBunkers.remove(bunker);
	}

	void PlanetSurface::mountains(shared_ptr<MountainChain> mountains) {
		if (mMountains)
			remove(mMountains);

		mMountains = std::move(mountains);
		insert(mMountains);
	}

	void PlanetSurface::randomBunkers(unsigned bunkers) {
		UniRandom<unsigned> bunkerType{2, 3};

		for (auto &b: mBunkers)
			remove(b);

		if (mMountains) {
			mBunkers.clear();

			while (bunkers > 0) {
				auto b = std::make_shared<Bunker>(Vectord{0, 0}, bunkerType());

				mBunkers.push_front(b);
				insert(b);

				bunkers--;
			}

			mMountains->alignRandomly(mBunkers.begin(), mBunkers.end());
		} else {
			throw std::logic_error("Mountain chains not set");
		}
	}

	void PlanetSurface::randomFuel(unsigned fuels, Vector<unsigned> capRange) {
		UniRandom<unsigned> fuel{capRange.x, capRange.y};
		UniRandom<int> segment{0, static_cast<int>(mMountains->size() - 2)};

		while (fuels > 0) {
			auto f = std::make_shared<Fuel>(Vectord{0, 0}, 100 * fuel());

			insert(f);
			mMountains->align(segment(), f);

			fuels--;
		}
	}
}
