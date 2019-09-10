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


namespace gvt {
	void PlanetSurface::mountains(shared_ptr<MountainChain> mountains) {
		if (mMountains)
			remove(mMountains);

		mMountains = std::move(mountains);
		insert(mMountains);
	}

	void PlanetSurface::randomBunkers(unsigned bunkers) {
		UniRandInt bunkerType{2, 3};

		for (auto &b: mBunkers)
			remove(b);

		if (mMountains) {
			mBunkers.clear();
			mBunkers.reserve(bunkers);

			while (bunkers > 0) {
				auto b = std::make_shared<Bunker>(Vectord{0, 0}, bunkerType());

				mBunkers.push_back(b);
				insert(b);

				bunkers--;
			}

			mMountains->alignRandomly(mBunkers.begin(), mBunkers.end());
		} else {
			throw std::logic_error("Mountain chains not set");
		}
	}
}
