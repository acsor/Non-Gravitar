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
#ifndef NON_GRAVITAR_PLANE_TRAITS_HPP
#define NON_GRAVITAR_PLANE_TRAITS_HPP


namespace gvt {
	/**
	 * Abstract class giving a width trait to derived classes.
	 */
	// TO-DO Find a way to make WidthTrait and HeightTrait really abstract
	class WidthTrait {
		protected:
			float mWidth;
		public:
			explicit WidthTrait(float width);

			inline float width() const;
			inline void width(float w);
	};

	/**
	 * Abstract class giving an height trait to derived classes.
	 */
	class HeightTrait {
		protected:
			float mHeight;
		public:
			explicit HeightTrait(float height);

			inline float height() const;
			inline void height(float h);
	};
}


// Implementation of inline member functions
#include "PlaneTraits.ipp"


#endif
