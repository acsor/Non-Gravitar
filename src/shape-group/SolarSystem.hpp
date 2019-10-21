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
#ifndef NON_GRAVITAR_SOLAR_SYSTEM_HPP
#define NON_GRAVITAR_SOLAR_SYSTEM_HPP

#include <forward_list>
#include <memory>
#include "shape/Planet.hpp"
#include "shape/SpawnArea.hpp"
#include "CollisionGroup.hpp"


namespace gvt {
	class SolarSystem: public CollisionGroup {
		private:
			shared_ptr<SpawnArea> mSpawnArea;
			std::forward_list<shared_ptr<Planet>> mPlanets;

			/**
			 * Updates height, width and mPlanets values upon insertion of a new
			 * @c Shape.
			 */
			void onInsertShape (shared_ptr<Shape> shape) override;
			/**
			 * Updates height, width and mPlanets values upon removal of an old
			 * @c Shape.
			 */
			void onRemoveShape (shared_ptr<Shape> shape) override;
		public:
			using iterator = std::forward_list<shared_ptr<Planet>>::iterator;

			inline shared_ptr<SpawnArea> spawnArea() const;
			/**
			 * @return The begin iterator of the planets list.
			 */
			inline iterator planetsBegin();
			/**
			 * @return The end iterator of the planets list.
			 */
			inline iterator planetsEnd();
	};
}


namespace gvt {
	shared_ptr<SpawnArea> SolarSystem::spawnArea() const {
		return mSpawnArea;
	}

	SolarSystem::iterator SolarSystem::planetsBegin() {
		return mPlanets.begin();
	}

	SolarSystem::iterator SolarSystem::planetsEnd() {
		return mPlanets.end();
	}
}


#endif