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
#ifndef NON_GRAVITAR_CLOSEDSHAPE_HPP
#define NON_GRAVITAR_CLOSEDSHAPE_HPP

#include "utils/BoundingPolygon.hpp"
#include "Shape.hpp"
#include "ShapeVisitor.hpp"


namespace gvt {
	/**
	 * A @c Shape capable of being represented as a closed curve. Its
	 * interface distinguishes from ClosedShape primarily for the presence of
	 * @c collisionPolygon() function.
	 */
	class ClosedShape: public Shape {
		protected:
			BoundingPolygon mPolygon;

			/**
			 * @param pos
			 * @param cp Collision polygon to approximate this shape with.
			 */
			ClosedShape(Vectord pos, BoundingPolygon cp);
		public:
			using Shape::position;
			using Shape::rotation;

			virtual double width() const = 0;
			virtual double height() const = 0;

			void position(Vectord p) override;
			void rotation(double r) override;

			/**
			 * @return The center point of this @c Shape <b>relative</b> to
			 * this object position (i.e. expressed in local coordinates).
			 */
			virtual inline Vectord rotationCenter() const;
			/**
			 * @return A @c Rectangle object representing the bounds used to
			 * detect collisions with another @c Shape. The coordinates
			 * accounted for are <i>global</i>, that is are measured against
			 * the global coordinate system.
			 */
			BoundingPolygon collisionPolygon() const;
			bool clashes(Shape const &o) const override;
	};
}


namespace gvt {
	Vectord ClosedShape::rotationCenter() const {
		return Vectord{width() / 2.0, height() / 2.0};
	}
}


#endif