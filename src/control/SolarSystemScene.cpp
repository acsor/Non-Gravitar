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
#include <cmath>

#include "Game.hpp"
#include "SolarSystemScene.hpp"
#include "PlanetSurfaceScene.hpp"


namespace gvt {
	void SolarSystemScene::onEnterPlanet (shared_ptr<gvt::Event> e) {
		auto ce = std::dynamic_pointer_cast<CollisionEvent>(e);

		if (ce) {
			auto ship = std::dynamic_pointer_cast<Spaceship>(ce->mFirst);
			auto planet = std::dynamic_pointer_cast<Planet>(ce->mSecond);

			if (!ship)
				ship = std::dynamic_pointer_cast<Spaceship>(ce->mSecond);
			if (!planet)
				planet = std::dynamic_pointer_cast<Planet>(ce->mFirst);

			if (ship && planet) {
				auto *game = Game::getInstance();

				planet->surface()->insert(game->acquireSpaceship());
				game->pushScene(std::make_shared<PlanetSurfaceScene>(planet));

				ship->acceleration({0, 0});
				ship->velocity({0, 0});
				ship->position({planet->surface()->width() / 2.0, 0});
				ship->rotation(M_PI);
			}
		}
	}

	SolarSystemScene::SolarSystemScene (shared_ptr<SolarSystem> const &system):
			Scene({system->width(), system->height()}, system) {
		auto _1 = std::placeholders::_1;

		mPlanetHandle = mShapes->addCallback(
			std::bind(&SolarSystemScene::onEnterPlanet, this, _1)
		);
	}

	SolarSystemScene::~SolarSystemScene () {
		mShapes->removeCallback(mPlanetHandle);
	}
}
