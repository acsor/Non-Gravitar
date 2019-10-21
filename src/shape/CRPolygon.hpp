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
#ifndef NON_GRAVITAR_CRPOLYGON_HPP
#define NON_GRAVITAR_CRPOLYGON_HPP

#include "ClosedShape.hpp"


namespace gvt {
	/**
	 * A convex, regular polygon.
	 */
	class CRPolygon: public ClosedShape {
		private:
			BoundingPolygon polygonFactory(
					double radius, unsigned vertices
			) const;
		protected:
			double mRadius;
			unsigned mVertices;
		public:
			CRPolygon(Vectord position, double radius, unsigned vertices);

			inline double radius() const;
			/**
			 * @return The vertices number of this polygon.
			 */
			inline unsigned vertices() const;
			inline double width() const override;
			inline double height() const override;

			Vectord rotationCenter() const override;
			bool operator== (Shape const &other) const override;
	};
}


namespace gvt {
	double CRPolygon::radius() const {
		return mRadius;
	}

	unsigned CRPolygon::vertices() const {
		return mVertices;
	}

	double CRPolygon::width() const {
		return 2.0 * mRadius;
	}

	double CRPolygon::height() const {
		return 2.0 * mRadius;
	}
}


#endif