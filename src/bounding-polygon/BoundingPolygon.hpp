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
#ifndef NON_GRAVITAR_BOUNDING_POLYGON_HPP
#define NON_GRAVITAR_BOUNDING_POLYGON_HPP

#include <initializer_list>
#include <vector>
#include "Vector.hpp"

template<typename T> using vector = std::vector<T>;


namespace gvt {
	struct AxialProjection;

	class BoundingPolygon {
		public:
			using float_type = float;
			using Vertex = Vector<float_type>;
		protected:
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
			virtual vector<Vector<float_type>> normalAxes() const final;
		public:
			/**
			 * @param vertices a std::initializer_list of @c Vertex values
			 * composing the convex polygon. These are expected to be ordered
			 * in clockwise manner; not complying with this specification can
			 * lead to unspecified behavior in some @c BoundingPolygon
			 * primitives.
			 * @throw std::domain_error if the number of vertices is minor
			 * than 3
			 */
			BoundingPolygon(std::initializer_list<Vertex> vertices);

			/**
			 * @brief Shifts (i.e. translates) the polygon by the given vector
			 * quantity @c translation
			 */
			void shift(Vector<float_type> translation);
			/**
			 * @brief Rotates the polygon by @c rad radiants around @c center.
			 */
			void rotate(float_type rad, Vertex center);
			/**
			 * @brief Rotates the polygon by @c rad radiants around the (0, 0)
			 * locus
			 */
			void rotate(float_type rad);
			/**
			 * @brief Projects the given polygon along @c axis
			 * @return An @c AxialProjection, representing the project extremes
			 * along @c axis
			 */
			AxialProjection projectAlong(Vector<float_type> axis) const;
			/**
			 * SAT (Separating Axes Theorem) algorithm implementation for
			 * detecting collisions between two arbitrarily-oriented convex 2D
			 * polygons. The @c BoundingPolygon class abstracts away their
			 * shape, assuming their vertices are predisposed in a convex
			 * manner.
			 *
			 * @return @c true if @c *this clashes with @c o, false otherwise.
			 * @see https://en.wikipedia.org/wiki/Hyperplane_separation_theorem
			 * @see https://www.metanetsoftware.com/technique/tutorialA.html
			 */
			virtual bool intersects(BoundingPolygon const &o) const final;

			virtual bool operator== (BoundingPolygon const &o) const;
			virtual bool operator!= (BoundingPolygon const &o) const;
	};

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


#endif