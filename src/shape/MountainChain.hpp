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

#include <set>
#include <utility>
#include "utils/Random.hpp"
#include "Polyline.hpp"


namespace gvt {
	/**
	 * @c MountainChain, subclassing @c Polyline, represents the profile of a
	 * series of mountains, little hills and plains.
	 */
	class MountainChain: public Polyline {
		protected:
			static double const constexpr MAX_MOUNTAIN_HEIGHT = 100;
			static double const constexpr MAX_MOUNTAIN_WIDTH = 200;

			static ShapeGenerator const sMountainGen, sHillGen, sPlainGen;
		public:
			template<typename iterator>
			MountainChain(Vectord position, iterator begin, iterator end):
					Polyline(position, begin, end) {
			}

			inline double height() const override;
			inline double width() const override;

			/**
			 * @param position Initial position of the @c MountainChain.
			 * @param pieces Number of pieces (e.g. single mountain, hill
			 * or plain profiles) to be generated.
			 * @return a @c MountainChain object, randomly initialized.
			 */
			static shared_ptr<MountainChain> randomChain (
				Vectord position, size_t pieces
			);
			template<typename iter>
			/**
			 * Aligns an iterator of @c Shapes objects in a random fashion
			 * along this @c MountainChain.
			 */
			void alignRandomly(iter shapesBegin, iter shapesEnd);
	};
}


namespace gvt {
	double MountainChain::height() const {
		return mPosition.y + MAX_MOUNTAIN_HEIGHT;
	}

	double MountainChain::width() const {
		return mVertices.empty() ? 0: mVertices.back().x;
	}

	template<typename iter>
	void MountainChain::alignRandomly(iter shapesBegin, iter shapesEnd) {
		unsigned const toInsert = std::distance(shapesBegin, shapesEnd);
		std::set<unsigned> positions;
		UniRandom<int> randomPos{0, static_cast<int>(size() - 2)};

		while (positions.size() < toInsert)
			positions.insert(randomPos());

		for (unsigned int position: positions) {
			align(position, *shapesBegin);

			shapesBegin++;
		}
	}
}


#endif