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

		Vector();
		/**
		 * @brief Instantiates a 2D-vector from its x and y components.
		 */
		Vector(T x, T y);
		/**
		 * @brief Instantiates a normalized Vector<T> object from the number
		 * of degrees
		 * @param degrees Value (specified in radians) in [0, 2π)
		 */
		Vector(T degrees);
		/**
		 * @brief Normalizes the given Vector<T> instance such that the module
		 * of the vector it represents has unitary length
		 */
		void normalize();
		/**
		 * @return The norm, aka length, of the given vector
		 */
		double inline norm() const;
		/*
		 * @return The angle subtended with the x axis (y = 0) by the Vector
		 */
		double inline degrees() const;

		Vector operator* (double l) const;
		Vector operator+ (Vector const &o) const;
		Vector& operator+= (Vector const &o);
	};

	using Trajectory = Vector<float>;
}


// Implementation file for inline and template functions
#include "Vector.ipp"


#endif
