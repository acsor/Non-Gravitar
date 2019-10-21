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
#ifndef NON_GRAVITAR_PLANET_SURFACE_HPP
#define NON_GRAVITAR_PLANET_SURFACE_HPP

#include <forward_list>
#include "shape/MountainChain.hpp"
#include "shape/Bunker.hpp"
#include "shape-group/CollisionGroup.hpp"


namespace gvt {
	/**
	 * @c PlanetSurface represents the 2D layout of a planet view, where its
	 * width and height measures are directly determined by that of the
	 * mountain chain inside it.
	 */
	class PlanetSurface: public CollisionGroup {
		private:
			shared_ptr<MountainChain> mMountains;
			std::forward_list<shared_ptr<Bunker>> mBunkers;

			void onInsertShape (shared_ptr<Shape> s) override;
			void onRemoveShape (shared_ptr<Shape> s) override;
		public:
			inline double height() const;
			inline double width() const;

			inline shared_ptr<MountainChain> mountains() const;
			inline std::forward_list<shared_ptr<Bunker>> bunkers() const;
	};
}


namespace gvt {
	double PlanetSurface::height() const {
		return mMountains ? mMountains->height(): 0;
	}

	double PlanetSurface::width() const {
		return mMountains ? mMountains->width(): 0;
	}

	shared_ptr<MountainChain> PlanetSurface::mountains() const {
		return mMountains;
	}

	std::forward_list<shared_ptr<Bunker>> PlanetSurface::bunkers() const {
		return mBunkers;
	}
}


#endif