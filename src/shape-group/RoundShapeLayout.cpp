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
#include "RoundShapeLayout.hpp"
#include <stdexcept>


namespace gvt {
	RoundShapeLayout::RoundShapeLayout (
			Vectord center, double radius, unsigned shapesNum
	): mCenter{center}, mRadius{radius}, mShapesNum{shapesNum} {
		mFactor = 2 * M_PI / shapesNum;
	}

	Vectord RoundShapeLayout::operator() (shared_ptr<Shape> shape, unsigned pos) {
		Vectord retpos;
		auto shapeCenter = Vectord{shape->width(), shape->height()} / 2.0;

		if (pos > mShapesNum) {
			throw std::domain_error("Layout position index exceeded");
		} else {
			retpos = mCenter + mRadius * Vectord(mFactor * pos) - shapeCenter;
		}

		shape->position(retpos);

		return retpos;
	}
}
