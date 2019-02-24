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
#ifndef NON_GRAVITAR_PLANE_OBJECT_HPP
#define NON_GRAVITAR_PLANE_OBJECT_HPP

#include <ostream>
#include "Plane.hpp"
#include "Trajectory.hpp"


namespace gvt {
	class Rectangle;
	class Point;

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
			float mOriginX{0}, mOriginY{0};
			float mRotation{0};
			Plane *mPlane{nullptr};

			/**
			 * @return A Rectangle object representing the bounds used to
			 * detect collision with another PlaneObject.
			 */
			virtual Rectangle collisionBox() const = 0;
			virtual void rotate() = 0;
		public:
			using ostream = std::ostream;

			PlaneObject(float x, float y);
			virtual ~PlaneObject() = default;

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
			 * @return The origin point, used for various geometrical
			 * transformations (e.g. translation, rotation, ...)
			 */
			virtual Point origin() const;
			/**
			 * @param p The origin used as a reference for various geometrical
			 * transformations
			 */
			virtual void origin(Point const &p);
			/**
			 * @return The angle with respect to the object origin of the
			 * current PlaneObject instance.
			 */
			virtual float rotation() const;
			/**
			 * @param r The rotation angle to set for this object
			 */
			virtual void rotation(unsigned r);
			/**
			 * @return <b>true</b> if the boundaries of the current PlaneObject
			 * clash with those of the object o.
			 */
			bool clashes(PlaneObject const &o) const;
			/**
			 * @brief Adds xcoord and ycord to the current space object
			 * coordinates.
			 */
			void move(float xcoord, float ycoord);
			/**
			 * @brief Move the current object along the given trajectory.
			 * @param t Trajectory to follow
			 * @param steps Amount of steps to perform in a given metric space
			 */
			void move(Trajectory const &t, size_t steps);
			/**
			 * @return True if the object at the current position meets the
			 * other PlaneObject given as argument by following the trajectory
			 * t
			 */
			bool meets(PlaneObject const &o, Trajectory const &t) const;

			virtual bool operator== (PlaneObject const &o) const = 0;
			virtual bool operator!= (PlaneObject const &o) const;
	};
}


// Definitions of constructs to be kept in the local translation-unit.
// The `i' in `.ipp' stands for "implementation".
#include "PlaneObject.ipp"


#endif
