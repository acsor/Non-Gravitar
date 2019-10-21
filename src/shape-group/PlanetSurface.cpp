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
#include <stdexcept>
#include "PlanetSurface.hpp"
#include "shape/Fuel.hpp"


namespace gvt {
	void PlanetSurface::onInsertShape (shared_ptr<Shape> s) {
		CollisionGroup::onInsertShape(s);

		if (auto b = std::dynamic_pointer_cast<Bunker>(s)) {
			mBunkers.push_front(b);
		} else if (auto m = std::dynamic_pointer_cast<MountainChain>(s)) {
			if (mMountains)
				remove(mMountains);

			mMountains = std::move(m);
		}
	}

	void PlanetSurface::onRemoveShape (shared_ptr<Shape> s) {
		CollisionGroup::onRemoveShape(s);

		if (auto b = std::dynamic_pointer_cast<Bunker>(s)) {
			mBunkers.remove(b);
		} else if (auto m = std::dynamic_pointer_cast<MountainChain>(s)) {
			mMountains.reset();
		}
	}
}
