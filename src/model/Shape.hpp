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
#ifndef NON_GRAVITAR_SHAPE_HPP
#define NON_GRAVITAR_SHAPE_HPP

#include <ostream>
#include "../Event.hpp"
#include "../Vector.hpp"


namespace gvt {
	class Rectangle;

	/**
	 * @brief An abstract base class for subsequent shape objects. Note that
	 * coordinates are taken by default from the <i>top left</i> corner, hence
	 * not an arbitrary center (which may vary from shape to shape).
	 * @see gvt::Plane
	 */
	class Shape: public EventDispatcher {
		protected:
			// Coordinates of the top-left corner by default, not of an
			// arbitrary center
			float mX{0}, mY{0};
			float mOriginX{0}, mOriginY{0};
			float mRotation{0};
			Trajectory mVelocity{0, 0};
		public:
			using ostream = std::ostream;

			static const Event MOVE;
			static const Event ORIGIN;
			static const Event ROTATION;
			static const Event DESTROIED;

			Shape(float x, float y);
			virtual ~Shape();

			/**
			 * @param xcoord the value of the new x coordinate of the shape
			 * top-left corner.
			 */
			virtual inline void x(float xcoord);
			/**
			 * @param ycoord the value of the new y coordinate of the shape
			 * top-left corner.
			 */
			virtual inline void y(float ycoord);
			/**
			 * @return Top-left corner x coordinate.
			 */
			virtual inline float x() const;
			/**
			 * @return Top-left corner y coordinate.
			 */
			virtual inline float y() const;
			/**
			 * @return The origin x coordinate, used for various geometrical
			 * transformations (e.g. translation, rotation, ...)
			 */
			virtual inline float originX() const;
			/**
			 * @return The origin y coordinate, used for various geometrical
			 * transformations (e.g. translation, rotation, ...)
			 */
			virtual inline float originY() const;
			/**
			 * @param p The origin used as a reference for various geometrical
			 * transformations
			 */
			virtual void origin(float xcoord, float ycoord);
			/**
			 * @return The angle with respect to the object origin of the
			 * current @c Shape instance, given in radians.
			 */
			virtual inline float rotation() const;
			/**
			 * @param r The rotation angle to set for this object, in radians
			 * @todo Test the implementation
			 */
			virtual inline void rotation(float r);
			/**
			 * @param r Amount of radians to add to the current rotation value
			 */
			virtual inline void rotate(float r);
			/**
			 * @param t Velocity value to set to the current @c Shape instance.
			 */
			virtual void velocity(Trajectory const &t);
			/**
			 * @return The velocity vector associated with the current
			 * @c Shape.
			 */
			virtual Trajectory velocity() const;
			/**
			 * @return The current @c Shape speed, as a scalar value.
			 */
			virtual float speed() const;

			/**
			 * @return A @c Rectangle object representing the bounds used to
			 * detect collision with another @c Shape.
			 */
			virtual Rectangle collisionBox() const = 0;
			/**
			 * @return @c true if the boundaries of the current @c Shape clash
			 * with those of the object @c o.
			 */
			virtual bool clashes(Shape const &o) const;
			/**
			 * @brief Adds xcoord and ycord to the current space object
			 * coordinates.
			 */
			virtual void move(float xcoord, float ycoord);
			/**
			 * @brief Move the current object along the given trajectory.
			 * @param t Trajectory to follow
			 */
			virtual void moveAlong(Trajectory const &t);
			/**
			 * @return @c true if the object at the current position meets the
			 * other @c Shape given as argument by following the
			 * trajectory @c t
			 */
			bool meets(Shape const &o, Trajectory const &t) const;

			virtual bool operator== (Shape const &o) const;
			virtual bool operator!= (Shape const &o) const;
	};
}


// Definitions of constructs to be kept in the local translation-unit.
// The `i' in `.ipp' stands for "implementation".
#include "Shape.ipp"


#endif
