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
#ifndef NON_GRAVITAR_TRACTOR_BEAM_HPP
#define NON_GRAVITAR_TRACTOR_BEAM_HPP

#include "Shape2D.hpp"
#include "Spaceship.hpp"


namespace gvt {
	/**
	 * A tractor beam is associated to a @c Spaceship, having the ability to
	 * lead fuel from land areas to it.
	 */
	class TractorBeam: public Shape2D {
		private:
			static const constexpr unsigned WIDTH = 40;
			static const constexpr unsigned HEIGHT = 50;

			Spaceship &mSpaceship;
		public:
			TractorBeam(Vectord position, Spaceship &spaceship);

			inline Spaceship& spaceship() const;

			Vectord rotationCenter() const override;
			inline double width() const override;
			inline double height() const override;

			void accept(ShapeVisitor &visitor) override;
			BoundingPolygon collisionPolygon() const override;
			bool operator== (Shape const &o) const override;
	};
}


namespace gvt {
	Spaceship& TractorBeam::spaceship() const {
		return mSpaceship;
	}

	double TractorBeam::width() const {
		return WIDTH;
	}

	double TractorBeam::height() const {
		return HEIGHT;
	}
}


#endif