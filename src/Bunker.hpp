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
#ifndef NON_GRAVITAR_BUNKER_HPP
#define NON_GRAVITAR_BUNKER_HPP

#include "PlaneObject.hpp"
#include "PlaneTraits.hpp"
#include "Missile.hpp"


namespace gvt {
	enum class BunkerType {
		DoubleDir, TripleDir
	};

	class Bunker: public PlaneObject, public WidthTrait, public HeightTrait {
		private:
			Trajectory *mTrajectories;
		protected:
			Rectangle collisionBox() const override;
		public:
			static float const constexpr	BUNKER_WIDTH = 5;
			static float const constexpr	BUNKER_HEIGHT = 4;

			BunkerType type;

			Bunker(float xcoord, float ycoord, BunkerType type);
			virtual ~Bunker();
			/**
			 * @return a Missile instance shot by the calling Bunker object.
			 */
			virtual Missile shoot() const = 0;

			bool operator== (PlaneObject const &o) const override;
	};
}


#endif
