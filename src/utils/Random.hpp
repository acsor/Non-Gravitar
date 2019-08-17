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
#ifndef NON_GRAVITAR_RANDOM_HPP
#define NON_GRAVITAR_RANDOM_HPP

#include <algorithm>
#include <random>


namespace gvt {
	class UniRandInt {
		private:
            std::uniform_int_distribution<int> mDist;
			std::default_random_engine mEngine;
		public:
			UniRandInt(int low, int high);
			int operator()();
	};

	template<typename I> class IteratorRandomizer {
		private:
			I mBegin;
			UniRandInt mRandInt;
		public:
			IteratorRandomizer (I begin, I end);
			I operator() ();
	};
}


namespace gvt {
	template<typename I> IteratorRandomizer<I>::IteratorRandomizer (I begin, I end):
			mBegin{begin}, mRandInt(0, std::distance(begin, end) - 1) {
	}

	template<typename I> I IteratorRandomizer<I>::operator() () {
        auto copy = mBegin;
        std::advance(copy, mRandInt.operator()());

        return copy;
	}
}


#endif