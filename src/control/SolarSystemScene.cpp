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
#include <utility>

#include "Game.hpp"
#include "SolarSystemScene.hpp"
#include "PlanetSurfaceScene.hpp"


namespace gvt {
	SolarSystemScene::SolarSystemScene (shared_ptr<SolarSystem> system):
			Scene(std::move(system)) {
		mShapes->addCallback(EnterPlanetCallback());
	}


	void EnterPlanetCallback::operator() (shared_ptr<gvt::Event> e) {
		auto ce = std::dynamic_pointer_cast<CollisionEvent>(e);

		if (ce) {
			auto ship = std::dynamic_pointer_cast<Spaceship>(ce->mFirst);
			auto planet = std::dynamic_pointer_cast<Planet>(ce->mSecond);

			if (!ship)
				ship = std::dynamic_pointer_cast<Spaceship>(ce->mSecond);
			if (!planet)
				planet = std::dynamic_pointer_cast<Planet>(ce->mFirst);

			if (ship && planet) {
				Game *game = Game::getInstance();

				planet->surface()->insert(game->acquireSpaceship());
				game->pushScene(
					std::make_shared<PlanetSurfaceScene>(planet)
				);
			}
		}
	}

	SolarSystemScene::SolarSystemScene (dim d, shared_ptr<SolarSystem> system):
			Scene(d, std::move(system)) {
		auto _1 = std::placeholders::_1;

		// TODO Set up removal in destructor
		mShapes->addCallback(
			std::bind(&SolarSystemScene::enterPlanet, this, _1)
		);
	}
}
