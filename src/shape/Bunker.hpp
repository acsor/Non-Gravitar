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

#include <vector>
#include "Shape2D.hpp"
#include "Rectangle.hpp"
#include "RoundMissile.hpp"
#include "ShapeVisitor.hpp"

template<typename T> using vector = std::vector<T>;


namespace gvt {
	class Bunker: public Shape2D {
		private:
			double mDelay{0};
			vector<Vectord> mPaths;
			unsigned mCurr{0};

			static unsigned const constexpr WIDTH = 66;
			static unsigned const constexpr HEIGHT = 45;
		public:
			Bunker(Vectord position, size_t directions);

			inline double width() const override;
			inline double height() const override;

			/**
			 * Sets the missile delay, i.e. the time to wait before the next
			 * missile is shot.
			 */
			inline void missileDelay (double delay);
			/**
			 * Getter method of @c missileDelay(double).
			 */
			inline double missileDelay () const;

			/**
			 * @return a @c RoundMissile instance shot by the calling @c Bunker
			 * object, with a random velocity vector of unitary norm.
			 */
			shared_ptr<RoundMissile> shoot();
			inline unsigned directions() const;

			void accept (ShapeVisitor &visitor) override;

			BoundingPolygon collisionPolygon() const override;
			bool operator==(Shape const &o) const override;
	};
}


namespace gvt {
	void Bunker::missileDelay (double delay) {
		mDelay = delay;
	}

	double Bunker::missileDelay () const {
		return mDelay;
	}

	// Implementation of inline Bunker functions
	double Bunker::width() const {
		return WIDTH;
	}

	double Bunker::height() const {
		return HEIGHT;
	}

	unsigned Bunker::directions() const {
		return mPaths.size();
	}
}

#endif
