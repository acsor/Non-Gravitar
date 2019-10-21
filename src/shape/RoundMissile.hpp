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
#ifndef NON_GRAVITAR_ROUND_MISSILE_HPP
#define NON_GRAVITAR_ROUND_MISSILE_HPP

#include <chrono>
#include "Circle.hpp"

using steady_clock = std::chrono::steady_clock;


namespace gvt {
	class RoundMissile: public Circle {
		private:
			steady_clock::time_point mBirth;
			std::chrono::duration<long, std::milli> mLifespan;
		public:
			static constexpr unsigned DEFAULT_RADIUS = 2;

			/**
			 * @param lifespan Missile duration, in milliseconds
			 */
			explicit RoundMissile(Vectord position, long lifespan=1000);
			/**
			 * @param lifespan Missile duration, in milliseconds
			 */
			RoundMissile(Vectord position, long lifespan, double radius);

			/**
			 * @return @c true if this missile lifetime expired, or if it is
			 * arbitrarily marked destroyed by a call to @c destroyed(bool).
			 */
			bool destroyed() const override;
			/**
			 * @return This @c RoundMissile lifespan, in milliseconds.
			 */
			inline long lifespan () const;
			inline void lifespan (long millis);

			void accept (ShapeVisitor &visitor) override;
			bool operator== (Shape const &o) const override;
	};
}


// Implementation of inline functions
namespace gvt {
	long RoundMissile::lifespan () const {
		return mLifespan.count();
	}

	void RoundMissile::lifespan (long millis) {
		mLifespan = std::chrono::duration<long, std::milli>(millis);
	}
}


#endif
