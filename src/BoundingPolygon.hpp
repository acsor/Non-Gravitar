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

#include <Vector.hpp>


namespace gvt {
	class BoundingPolygon {
		protected:
			/**
			 * @return A series of vectors giving the normal axes of the convex
			 * polygon making the call. These will be later used to to
			 * project the polygon onto them.
			 */
			virtual std::vector<Vector<float>> normalAxes() const = 0;
		public:
			bool clashes(BoundingPolygon const &o) const final;
			virtual bool operator== (BoundingPolygon const &o) const = 0;
	};
}


#endif
