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
#ifndef NON_GRAVITAR_PLANET_SURFACE_HPP
#define NON_GRAVITAR_PLANET_SURFACE_HPP

#include <vector>
#include "shape/MountainChain.hpp"
#include "shape/Bunker.hpp"
#include "shape-group/CollisionGroup.hpp"


namespace gvt {
	class PlanetSurface: public CollisionGroup {
		private:
			std::vector<std::shared_ptr<Bunker>> mBunkers;
			std::unique_ptr<MountainChain> mMountains;

			/**
			 * Default positions of the mountain chain with respect to this
			 * planet surface.
			 */
			static const Vectord MOUNTAINS_POS;
		public:
			static shared_ptr<gvt::PlanetSurface> makeRandom(
				unsigned bunkers, unsigned mountainsPerBunker
			);
	};
}


#endif