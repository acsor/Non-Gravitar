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
#ifndef NON_GRAVITAR_CIRCLE_HPP
#define NON_GRAVITAR_CIRCLE_HPP

#include "Shape2D.hpp"


namespace gvt {
	class Circle: public Shape2D {
		private:
			static unsigned const constexpr COLLISION_PRECISION = 8;

			BoundingPolygon polygonFactory(double radius) const;
		protected:
			double mRadius;
		public:
			using Shape2D::clashes;

			Circle(Vectord position, double radius);

			inline double width() const override;
			inline double height() const override;

			inline void radius(double r);
			inline double radius() const;
			inline double area() const;
			bool clashes(Circle const &o) const;

			void accept (ShapeVisitor &visitor) override;
			bool operator== (Shape const &o) const override;
	};
}


namespace gvt {
	void Circle::radius(double r) {
		mRadius = r;
	}

	double Circle::radius() const {
		return mRadius;
	}

	double Circle::area() const {
		return M_PI * pow(mRadius, 2);
	}

	double Circle::width() const {
        return 2 * mRadius;
	}

	double Circle::height() const {
		return 2 * mRadius;
	}
}


#endif
