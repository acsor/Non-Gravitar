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
#include <list>
#include <memory>
#include <algorithm>
#include "MountainChain.hpp"
#include "utils/Random.hpp"


namespace gvt {
	ShapeGenerator const MountainChain::sMountainGen = []() {
		return std::vector<Vectord>{
				{0, MAX_HEIGHT}, {MAX_WIDTH / 2.0, MAX_HEIGHT * 0.2},
				{MAX_WIDTH, MAX_HEIGHT}
		};
	};
	ShapeGenerator const MountainChain::sHillGen = []() {
		return std::vector<Vectord>{
				{0, MAX_HEIGHT}, {MAX_WIDTH / 3.0, MAX_HEIGHT * 0.4},
				{MAX_WIDTH * 2.0 / 3.0, MAX_HEIGHT * 0.4},
				{MAX_WIDTH, MAX_HEIGHT}
		};
	};
	ShapeGenerator const MountainChain::sPlainGen = []() {
		return std::vector<Vectord>{{0, MAX_HEIGHT}, {MAX_WIDTH, MAX_HEIGHT}};
	};

	shared_ptr<MountainChain> MountainChain::randomChain (
			Vectord position, size_t pieces
	) {
		std::list<Vectord> vertices;
		vector<Vectord> generated;
        vector<ShapeGenerator> generators = {
        		sMountainGen, sHillGen, sPlainGen
        };
		IteratorRandomizer<vector<ShapeGenerator>::iterator> randGen {
				generators.begin(), generators.end()
		};
        Vectord offset{0, 0};

        while (pieces > 0) {
			generated = randGen()->operator()();

			for (Vectord const &vertex: generated)
                vertices.push_back(offset + vertex);

            offset.x += generated.back().x;

        	pieces--;
        }

        // vertices.push_back(vertices.front());

		return std::make_shared<MountainChain>(
			position, vertices.begin(), vertices.end()
		);
	}
}
