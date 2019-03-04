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
#ifndef NON_GRAVITAR_LINE_HPP
#define NON_GRAVITAR_LINE_HPP

#include "Shape.hpp"
#include "ShapeTraits.hpp"
#include "Point.hpp"
#include "Rectangle.hpp"


namespace gvt {
	class Line: public Shape, public WidthTrait {
		private:
			Point mEnd;
		protected:
			Rectangle collisionBox() const override;
		public:
			// Default width of the bounding box returned by
			// Line::collisionBox()
			double static const constexpr WIDTH_BBOX = 1E-3;

			Line(Point const &start, Point const &end);
			float width() const override;
			void rotation(float r) override;
			/**
			 * @brief Scales the width of the line object by <b>factor</b>.
			 * @return Stretched out/in Line object
			 */
			Line& operator* (double factor);
			bool operator== (Shape const &o) const override;
	};
}


#endif
