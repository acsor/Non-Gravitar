// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#ifndef NON_GRAVITAR_BOUNDING_POLYGON_HPP
#define NON_GRAVITAR_BOUNDING_POLYGON_HPP

#include <initializer_list>
#include <vector>
#include "utils/Vector.hpp"

template<typename T> using vector = std::vector<T>;


namespace gvt {
	struct AxialProjection;

	/**
	 * Auxiliary class aiding in the detection of collision between shape
	 * objects. @c BoundingPolygon instances are generally instantiated as an
	 * approximation to the area the user wants to check collisions for, and
	 * they are specified in local coordinates. The algorithm for
	 * detecting collisions is an implementation of the Separating Axes Theorem:
	 * https://www.metanetsoftware.com/technique/tutorialA.html.
	 *
	 * Note that @c BoundingPolygons also accept the case of a straight line,
	 * which can be specified with just two vertices.
	 */
	class BoundingPolygon {
		public:
			using float_type = double;
			using Vertex = Vector<float_type>;
		protected:
			Vector<float_type> mPosition;
			/**
			 * A sequence of vertices, ordered in clockwise manner,
			 * composing the convex polygon (NOTE: faiing to order the
			 * vertices in the prescribed way will lead to unexpected behavior
			 * in some other BoundingPolygon primitives.)
			 */
			std::vector<Vertex> mVertices;

			/**
			 * @return A series of vectors representing the normal axes of the
			 * convex polygon making the call. These will be later used by the
			 * Separating Axes Theorem
			 */
			vector<Vector<float_type>> normalAxes() const;
			/**
			 * @brief Projects the given polygon along @c axis, expressed as
			 * a vector.
			 * @return An @c AxialProjection, representing the projection
			 * extremes along @c axis
			 */
			AxialProjection projectAlong(Vector<float_type> axis) const;
		public:
			/**
			 * @param vertices a std::initializer_list of @c Vertex values
			 * composing the convex polygon. These are expected to be ordered
			 * in clockwise manner; not complying with this specification can
			 * lead to unspecified behavior in some @c BoundingPolygon
			 * primitives.
			 *
			 * @return A @c BoundingPolygon with an initial absolute position at
			 * @c (0, 0).
			 * @throw std::domain_error if the number of vertices is minor
			 * than 2.
			 */
			BoundingPolygon(std::initializer_list<Vertex> vertices);
			template<typename iterator>
			/**
			 * Constructs a @c BoundingPolygon out of an iterator of @c Vertex
			 * values composing the convex polygon. These are expected to be
			 * ordered in clockwise manner; not complying with this
			 * specification can lead to unspecified behavior in some
			 * @c BoundingPolygon primitives.
			 *
			 * @return A @c BoundingPolygon with an initial absolute position at
			 * @c (0, 0).
			 * @throw std::domain_error if the number of vertices is minor
			 * than 2.
			 */
			BoundingPolygon(iterator begin, iterator end);
			/**
			 * Constructs a @c BoundingPolygon with the specified initial
			 * number of default-constructed vertices.
			 */
			explicit BoundingPolygon(unsigned vertices);

			/**
			 * Sets the absolute position of this @c BoundingPolygon.
			 */
			inline void position (Vectord position);
			/**
			 * @return The absolute position of this @c BoundingPolygon.
			 */
			inline Vectord position () const;
			/**
			 * @brief Rotates the polygon by @c rad radians around its
			 * <b>local</b> @c (0, 0) point.
			 */
			void rotate(float_type rad);
			/**
			 * @brief Rotates the polygon by @c rad radians around @c center.
			 * @param center Point in <b>local</b> coordinates around which
			 * rotate this polygon.
			 */
			void rotate(float_type rad, Vertex center);
			/**
			 * SAT (Separating Axes Theorem) algorithm implementation for
			 * detecting collisions between two arbitrarily-oriented convex 2D
			 * polygons. The @c BoundingPolygon class abstracts away their
			 * shape, assuming their vertices are predisposed in a convex,
			 * clock-wise manner.
			 *
			 * @return @c true if @c *this clashes with @c o, false otherwise.
			 * @see https://en.wikipedia.org/wiki/Hyperplane_separation_theorem
			 * @see https://www.metanetsoftware.com/technique/tutorialA.html
			 */
			bool intersects(BoundingPolygon const &o) const;

			Vertex& operator[] (unsigned i);
			/**
			 * @return The "list" of vertices comprising this @c
			 * BoundingPolygon.
			 */
			std::vector<Vertex> vertices () const;
			unsigned size() const;
			/**
			 * @return The mean point of this @c BoundingPolygon in its
			 * <b>local</b> coordinate space.
			 */
			Vertex center () const;

			/**
			 * Constructs a bounding triangle, assuming an initial absolute
			 * position at @c (0, 0) and an orientation of zero radians.
			 * @return What you expect it to return.
			 */
			static BoundingPolygon triangle (
					Vectord first, Vectord second, Vectord third
			);
			/**
			 * Constructs a bounding rectangle, assuming an initial absolute
			 * position at @c (0, 0) and an orientation of zero radians.
			 * @param topLeft Top-left corner of the rectangle,
			 * @param bottomRight  Bottom-right corner of the triangle
			 * @return What you expect it to return.
			 */
			static BoundingPolygon rectangle (
				Vectord topLeft, Vectord bottomRight
			);

			bool operator== (BoundingPolygon const &o) const;
			bool operator!= (BoundingPolygon const &o) const;
	};

	/**
	 * Utility struct, holding a pair of coordinates representing the extremes
	 * of a projection over an axis.
	 */
	struct AxialProjection {
		using float_type = BoundingPolygon::float_type;
		float_type start, end;

		/**
		 * @return @c true if this axial projection intersects with @c o,
		 * @c false otherwise.
		 */
		bool intersects(AxialProjection const &o) const;
	};
}


namespace gvt {
	template<typename iterator>
	BoundingPolygon::BoundingPolygon(iterator begin, iterator end) {
		if (std::distance(begin, end) < 2)
			throw std::domain_error(
				"Unable to instantiate a BoundingPolygon with fewer than 2 vertices"
			);

		mVertices.assign(begin, end);
	}

	void BoundingPolygon::position (Vectord position) {
		mPosition = position;
	}

	Vectord BoundingPolygon::position () const {
		return mPosition;
	}
}


#endif
