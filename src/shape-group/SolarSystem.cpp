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
#include <cstdlib>
#include <random>
#include "SolarSystem.hpp"


namespace gvt {
	std::shared_ptr<SolarSystem> SolarSystem::makeRandom (
		unsigned planets, double minRadius, double maxRadius, Vectord minPos,
		Vectord maxPos
	) {
        std::shared_ptr<SolarSystem> system {new SolarSystem()};
        std::default_random_engine e;
		std::uniform_real_distribution<double> radius{minRadius, maxRadius};
        std::uniform_real_distribution<double>
				xCoord{minPos.x, maxPos.x}, yCoord{minPos.y, maxPos.y};

        e.seed(time(nullptr));

        while (planets > 0) {
			auto p = std::shared_ptr<Planet>(
				new Planet(Vectord{xCoord(e), yCoord(e)}, radius(e))
			);
			system->insert(p);

        	planets--;
        }

        return system;
	}
}
