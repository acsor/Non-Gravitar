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
#ifndef NON_GRAVITAR_TRAJECTORY_HPP
#define NON_GRAVITAR_TRAJECTORY_HPP


namespace gvt {
	/**
	 * Utility struct to handle missile, particles and other movable objects'
	 * trajectory.
	 */
	struct Trajectory {
		float x, y;

		/**
		 * @brief Instantiates a normalized Trajectory object from the number
		 * of degrees
		 * @param degrees Value (specified in radians) in [0, 2π)
		 */
		Trajectory(float degrees);
		/**
		 * @brief Normalizes the given Trajectory instance such that the module
		 * of the vector it represents has unitary length
		 */
		void normalize();
		float degrees() const;

		Trajectory operator+ (Trajectory const &o);
		Trajectory& operator+= (Trajectory const &o);
	};
}


#endif
