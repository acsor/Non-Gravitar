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
#ifndef NON_GRAVITAR_MOUNTAIN_HPP
#define NON_GRAVITAR_MOUNTAIN_HPP

#include "Shape.hpp"
#include "ShapeVisitor.hpp"
#include "utils/Vector.hpp"


namespace gvt {
	class Mountain: public Shape {
		private:
			Vectord mLeft, mTop, mRight;
		public:
			Mountain(Vectord left, Vectord top, Vectord right);

			inline Vectord left () const;
			inline Vectord top () const;
			inline Vectord right () const;

			Vectord center() const override;
			/**
			 * @return The base of the triangle this mountain is associated to.
			 */
			double width() const override;
			/**
			 * @return The height of the triangle this mountain is associated
			 * to.
			 */
			double height() const override;
			BoundingPolygon collisionPolygon() const override;

			void accept (ShapeVisitor &visitor) override;
	};
}


namespace gvt {
	Vectord Mountain::left () const {
		return mLeft;
	}

	Vectord Mountain::top () const {
		return mTop;
	}

	Vectord Mountain::right () const {
		return mRight;
	}
}


#endif
