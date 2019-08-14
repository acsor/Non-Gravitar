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
#ifndef NON_GRAVITAR_MOUNTAIN_CHAIN_HPP
#define NON_GRAVITAR_MOUNTAIN_CHAIN_HPP

#include <utility>
#include "Polyline.hpp"



namespace gvt {
	/**
	 * @c MountainChain, subclassing @c Polyline, represents the profile of a
	 * series of mountains, little hills and plains.
	 */
	class MountainChain: public Polyline {
		protected:
			static double const constexpr MAX_HEIGHT = 100;
			static double const constexpr MAX_WIDTH = 150;

			static ShapeGenerator const sMountainGen, sHillGen, sPlainGen;
		public:
			template<typename iterator>
			MountainChain(Vectord position, iterator begin, iterator end):
					Polyline(position, begin, end) {
			}

			/**
			 * @param position Initial position of the @c MountainChain.
			 * @param pieces Number of pieces (e.g. single mountain, hill
			 * or plain profiles) to be generated.
			 * @return a @c MountainChain object, randomly initialized.
			 */
			static shared_ptr<MountainChain> randomChain (
				Vectord position, size_t pieces
			);
	};
}

#endif