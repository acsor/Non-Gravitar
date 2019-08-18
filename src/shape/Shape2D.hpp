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
#ifndef NON_GRAVITAR_SHAPE2D_HPP
#define NON_GRAVITAR_SHAPE2D_HPP

#include "bounding-polygon/BoundingPolygon.hpp"
#include "Shape.hpp"
#include "ShapeVisitor.hpp"


namespace gvt {
	/**
	 * A @c Shape occupying a well defined rectangular region on the coordinate
	 * space.
	 */
	class Shape2D: public Shape {
		protected:
			inline explicit Shape2D(Vectord position);
		public:
			virtual double width() const = 0;
			virtual double height() const = 0;

			/**
			 * @return The center point of this @c Shape <b>relative</b> to
			 * this object position (i.e. expresses in local coordinates).
			 */
			virtual inline Vectord rotationCenter() const;
			/**
			 * @return A @c Rectangle object representing the bounds used to
			 * detect collisions with another @c Shape. The coordinates
			 * accounted for are <i>global</i>, that is are measured against
			 * the global coordinate system.
			 */
			virtual BoundingPolygon collisionPolygon() const = 0;
			inline bool clashes(Shape const &o) const override;
	};
}


namespace gvt {
	Shape2D::Shape2D(Vectord position): Shape(position) {
	}

	Vectord Shape2D::rotationCenter() const {
		return Vectord{width() / 2.0, height() / 2.0};
	}

	bool Shape2D::clashes(Shape const &o) const {
        auto other = dynamic_cast<Shape2D const *>(&o);

        // If `o' is an instance of Shape2D, we know how to detect collisions
        if (other) {
        	return collisionPolygon().intersects(other->collisionPolygon());
		// otherwise, we delegate the task to `o', which might know more
		// about this all
        } else {
        	return o.clashes(*this);
        }
	}
}


#endif