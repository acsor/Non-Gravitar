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
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "RoundMissile.hpp"
#include "ShapeVisitor.hpp"

template<typename T> using vector = std::vector<T>;


namespace gvt {
	class Bunker: public Shape {
		protected:
			vector<Vectorf> mPaths;
			unsigned mCurr{0};

			Bunker(Vectorf position, size_t directions);

			// Width and height measures of the collision boxes
			static unsigned const constexpr COLLIDING_WIDTH = 29;
			static unsigned const constexpr COLLIDING_HEIGHT = 42;
		public:
			static unsigned const constexpr WIDTH = 45;
			static unsigned const constexpr HEIGHT = 66;

			inline float width() const override;
			inline float height() const override;

			/**
			 * @return a @c RoundMissile instance shot by the calling @c Bunker
			 * object.
			 */
			RoundMissile shoot();

			void accept (ShapeVisitor &visitor) override;

			BoundingPolygon collisionPolygon() const override;
			bool operator==(Shape const &o) const override;
	};

	// If I recall correctly, templates can even be used to pass concrete
	// values between specializations, e.g. ClassName<4>. Could that be an idea
	// to simplify the inheritance for Bunker2D and Bunker3D?
	class Bunker2D: public Bunker {
		public:
			Bunker2D(Vectorf position);

			bool operator==(Shape const &o) const override;
	};

	class Bunker3D: public Bunker {
		public:
			Bunker3D(Vectorf position);

			bool operator==(Shape const &o) const override;
	};
}


// Implementation of Bunker inline functions
float gvt::Bunker::width() const {
	return WIDTH;
}

float gvt::Bunker::height() const {
	return HEIGHT;
}


#endif
