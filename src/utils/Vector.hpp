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
#ifndef NON_GRAVITAR_VECTOR_HPP
#define NON_GRAVITAR_VECTOR_HPP


namespace gvt {
	/**
	 * Utility struct to handle missile, particles and other movable objects'
	 * trajectory.
	 */
	template <typename T> struct Vector {
		T x, y;

		// TODO Have gvt::Vector provide a return value for most of its methods
		Vector();
		/**
		 * @brief Instantiates a 2D-vector from its @a x and @a y components.
		 */
		Vector(T x, T y);
		/**
		 * @brief Instantiates a normalized @c Vector<T> object from the angle
		 * value
		 * @param degrees Value (specified in radians) in [0, 2π). Any outside
		 * value will be reduced to this range
		 **/
		explicit Vector(T r);
		/**
		 * @brief Normalizes the given @c Vector<T> instance such that the
		 * module of the vector it represents has unitary length
		 */
		void normalize();
		void rotate(double rad);
		/**
		 * Rotate the vector by @c rad radiants around 2D point @c center.
		 */
		void rotate(double rad, Vector center);
		/**
		 * @return The norm, aka length, of the given vector
		 */
		double inline norm() const;
		/**
		 * @return The distance between this vector and @c other.
		 */
		double inline distance(Vector const &other) const;
		Vector<T> midpoint (Vector<T> const &other) const;
		/*
		 * @return The angle this vector forms with the x axis.
		 */
		double inline angle() const;
		/**
		 * @return The dot product of this vector with @c other.
		 */
		T inline dotProduct(Vector const &other) const;
		/**
		 * @return The projection of this vector along the axis vector @c axis
		 */
		double projectAlong(Vector const &axis) const;

		Vector operator+ (Vector const &o) const;
		Vector operator- (Vector const &o) const;
		Vector operator* (double f) const;
		Vector operator/ (double f) const;
		Vector& operator+= (Vector const &o);

		bool operator==(Vector const &o) const;
		bool operator!=(Vector const &o) const;
	};

	template<typename T> Vector<T> operator* (double f, Vector<T> v);
	template<typename T> Vector<T> operator/ (double f, Vector<T> v);

	using Vectorf = Vector<float>;
	using Vectord = Vector<double>;
}


namespace std {
	template<typename T> struct hash<gvt::Vector<T>> {
		size_t operator() (gvt::Vector<T> const &key) const;
	};
}


// Implementation file for inline and template functions
#include "Vector.ipp"


#endif
