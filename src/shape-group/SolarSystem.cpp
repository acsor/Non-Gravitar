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
#include <memory>
#include "PlanetSurface.hpp"
#include "SolarSystem.hpp"


namespace gvt {
	void SolarSystem::onInsertShape (shared_ptr<Shape> shape) {
		CollisionGroup::onInsertShape(shape);

		auto const pos = shape->position();

		mWidth = std::max(mWidth, pos.x + shape->width());
		mHeight = std::max(mHeight, pos.y + shape->height());

		if (auto planet = std::dynamic_pointer_cast<Planet>(shape)) {
			mPlanets.push_front(planet);
		} else if (auto area = std::dynamic_pointer_cast<SpawnArea>(shape)) {
			mSpawnArea = std::move(area);
		}
	}

	void SolarSystem::onRemoveShape (shared_ptr<Shape> shape) {
		CollisionGroup::onRemoveShape(shape);

		if (auto planet = std::dynamic_pointer_cast<Planet>(shape)) {
			mPlanets.remove(planet);
		} else if (auto area = std::dynamic_pointer_cast<SpawnArea>(shape)) {
			if (mSpawnArea == area)
				mSpawnArea.reset();
		}
	}
}
