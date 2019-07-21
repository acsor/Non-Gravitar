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
#ifndef NON_GRAVITAR_RECTANGLE_HPP
#define NON_GRAVITAR_RECTANGLE_HPP

#include <ostream>
#include "Shape.hpp"
#include "ShapeTraits.hpp"
#include "Point.hpp"
#include "ShapeVisitor.hpp"


namespace gvt {
	class Rectangle;
}


namespace std {
	template<> struct hash<gvt::Rectangle> {
		size_t operator()(gvt::Rectangle const &r) const;
	};
	template<> struct equal_to<gvt::Rectangle> {
		bool operator()(
			gvt::Rectangle const &r1, gvt::Rectangle const &r2
		) const;
	};
	ostream& operator<< (ostream &out, gvt::Rectangle const &r);
};


namespace gvt {
    class Rectangle: public Shape, public WidthTrait, public HeightTrait {
		using ostream = std::ostream;

		friend struct std::hash<Rectangle>;
		friend struct std::equal_to<Rectangle>;

		friend ostream& std::operator<< (ostream &out, Rectangle const &r);

		private:
			Point mEnd{0, 0};
    	public:
    		/**
    		 * @brief Constructs a @c Rectangle with width > 0 and height > 0.
    		 * @throw std::domain_error if width < 0 or height < 0.
    		 */
			Rectangle(Point topLeft, Point bottomRight);
			/**
			 * @param o Other @c Rectangle instance to detect clashing with.
			 * @return @c true if the two <tt>Rectangle</tt>s share an area
			 * portion, @c false otherwise.
			 */
			bool clashes(Rectangle const &o) const;

			void accept (ShapeVisitor &visitor) override;
			Rectangle globalBounds() const override;
			bool operator==(Shape const &o) const override;

			// TO-DO Check why the override below obfuscates the
			// Shape::rotation() function
			// virtual void rotation(float r) override;

			float width() const override;
			float height() const override;
    };
}


#endif
