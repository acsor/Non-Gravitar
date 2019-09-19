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
#include <memory>
#include <random>
#include "PlanetSurface.hpp"
#include "SolarSystem.hpp"


namespace gvt {
	void SolarSystem::onInsertShape (shared_ptr<Shape> shape) {
		CollisionGroup::onInsertShape(shape);

		auto const pos = shape->position();
		auto shape2d = std::dynamic_pointer_cast<Shape2D>(shape);

		if (shape2d) {
			mWidth = std::max(mWidth, pos.x + shape2d->width());
			mHeight = std::max(mHeight, pos.y + shape2d->height());
		} else {
			mWidth = std::max(mWidth, pos.x);
			mHeight = std::max(mHeight, pos.y);
		}
	}

	std::shared_ptr<SolarSystem> SolarSystem::makeRandom (
		unsigned planets, double minRadius, double maxRadius, Vectord minPos,
		Vectord maxPos
	) {
        std::shared_ptr<SolarSystem> system {new SolarSystem()};
		UniRandom<double> radius{minRadius, maxRadius};
        UniRandom<double> xCoord{minPos.x, maxPos.x};
		UniRandom<double> yCoord{minPos.y, maxPos.y};
        UniRandom<unsigned> bonus{1, 8};

        while (planets > 0) {
			auto p = std::make_shared<Planet>(
				Vectord{xCoord(), yCoord()}, radius()
			);
			auto surface = std::make_shared<PlanetSurface>();

			surface->mountains(MountainChain::randomChain({0, 600}, 20));
			surface->randomBunkers(5);
			surface->randomFuel(2, Vector<unsigned>{100, 500});
			p->surface(surface);
			p->bonus(1000 * bonus());

			system->insert(p);

        	planets--;
        }

        return system;
	}
}
