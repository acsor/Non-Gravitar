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
#ifndef NON_GRAVITAR_ENTITIES_HPP
#define NON_GRAVITAR_ENTITIES_HPP

#include <ostream>


namespace gvt {
	class Plane {
		public:
			void updateCollisions();
	};

	class Rectangle;
}


namespace std {
	ostream& operator<< (ostream &out, gvt::Rectangle const &r);
}


namespace gvt {
	/**
	 * @brief An abstract base class for subsequent plane objects. Note that
	 * coordinates are taken by default from the <i>top left</i> corner, hence
	 * not an arbitrary center (which may vary from shape to shape).
	 * @see gvt::Plane
	 */
	class PlaneObject {
		protected:
			// Coordinates of the top-left corner by default, not of an
			// arbitrary center
			float mX{0}, mY{0};
			Plane *mPlane{nullptr};

			/**
			 * @return A Rectangle object representing the bounds used to
			 * detect collision with another PlaneObject.
			 */
			virtual Rectangle collisionBox() const = 0;
		public:
			using ostream = std::ostream;

			PlaneObject(float x, float y);
			virtual ~PlaneObject() = default;

			/**
			 * @return <b>true</b> if the boundaries of the current PlaneObject
			 * clash with those of the object o.
			 */
			virtual bool clashes(PlaneObject const &o) const;
			/**
			 * @param xcoord the value of the new x coordinate of the shape
			 * top-left corner.
			 */
			inline void x(float xcoord);
			/**
			 * @param ycoord the value of the new y coordinate of the shape
			 * top-left corner.
			 */
			inline void y(float ycoord);
			/**
			 * @return Top-left corner x coordinate.
			 */
            inline float x() const;
			/**
			 * @return Top-left corner y coordinate.
			 */
			inline float y() const;
			/**
			 * @brief Adds xcoord and ycord to the current space object
			 * coordinates.
			 */
			void move(float xcoord, float ycoord);

			virtual bool operator== (PlaneObject const &o) const = 0;
	};

	/**
	 * Abstract class giving a width trait to derived classes.
	 */
	// TO-DO Find a way to make WidthTrait and HeightTrait really abstract
	class WidthTrait {
		protected:
			float mWidth;
		public:
			explicit WidthTrait(float width);

			inline float width() const;
			inline void width(float w);
	};

	/**
	 * Abstract class giving an height trait to derived classes.
	 */
	class HeightTrait {
		protected:
			float mHeight;
		public:
			explicit HeightTrait(float height);

			inline float height() const;
			inline void height(float h);
	};


	class Line: public PlaneObject, public WidthTrait {
		protected:
			Rectangle collisionBox() const override;
		public:
			// Default width of the bounding box returned by
			// Line::collisionBox()
			double static const constexpr WIDTH_BBOX = 0.0001;

			Line(float xcoord, float ycoord, float width);
			/**
			 * @brief Scales the width of the line object by <b>factor</b>.
			 * @return Stretched out/in Line object
			 */
			Line& operator* (double factor);
			bool operator== (PlaneObject const &o) const;
	};

    class Rectangle: public PlaneObject, public WidthTrait, public HeightTrait
	{
		using ostream = std::ostream;

		friend class std::hash<Rectangle>;
		friend class std::equal_to<Rectangle>;

		protected:
			Rectangle collisionBox() const override;
    	public:
    		/**
    		 * @brief Constructs a Rectangle with width > 0 and height > 0.
    		 * @throw std::domain_error if width < 0 or height < 0.
    		 */
			Rectangle(float x, float y, float width, float height);
			/**
			 * @param o Other Rectangle instance to detect clashing with.
			 * @return true if the two Rectangles share an area portion, false
			 * otherwise.
			 */
			bool clashes(Rectangle const &o) const;
			bool operator==(PlaneObject const &o) const override;

			friend ostream& std::operator<< (ostream &out, Rectangle const &r);
    };

	class SpaceMissile: public PlaneObject {
		private:
			float mRadius;

		protected:
			Rectangle collisionBox() const override;
			bool operator== (PlaneObject const &o) const override;
	};

	class Spaceship: public PlaneObject {
		protected:
			Rectangle collisionBox() const override;
			bool operator== (PlaneObject const &o) const override;
	};
}


namespace std {
	using namespace gvt;


	template<> struct hash<Rectangle> {
		size_t operator()(Rectangle const &r) const;
	};
	template<> struct equal_to<Rectangle> {
		bool operator()(Rectangle const &r1, Rectangle const &r2) const;
	};
};


// Definitions of constructs to be kept in the local translation-unit.
// The `i' in `.ipp' stands for "implementation".
#include "Entities.ipp"


#endif
