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
#include "PlanetSurfaceScene.hpp"
#include "Game.hpp"


namespace gvt {
	void PlanetSurfaceScene::exitPlanet() {
		auto game = Game::getInstance();
		auto ship = game->acquireSpaceship();
		auto solarSystem = game->popScene();

		ship->acceleration({0, 0});
		ship->position(mPlanet->position() - Vectord{0, 100});

		solarSystem->shapes()->insert(ship);
	}

	void PlanetSurfaceScene::onShipMoved (shared_ptr<PositionEvent> e) {
		if (mShip->position().y < 0)
			exitPlanet();
	}

	PlanetSurfaceScene::PlanetSurfaceScene (shared_ptr<Planet> const &planet):
			Scene({planet->surface()->width(), planet->surface()->height()}, planet->surface())
	{
		auto _1 = std::placeholders::_1;
		auto surface = planet->surface();

		mPlanet = planet;
		mShip = Game::getInstance()->spaceship();
		mShipCbk = mShip->positionDispatcher().addCallback(
				std::bind(&PlanetSurfaceScene::onShipMoved, this, _1)
		);
	}

	PlanetSurfaceScene::~PlanetSurfaceScene () {
		mShip->positionDispatcher().removeCallback(mShipCbk);
	}

	void PlanetSurfaceScene::onUpdateGame (double seconds) {
		Scene::onUpdateGame(seconds);

		// Update bunkers' shooting delay
		for (auto const &bunker: mPlanet->surface()->bunkers())
			bunker->missileDelay(bunker->missileDelay() - seconds);

		// Shoot missiles
		for (auto const &bunker: mPlanet->surface()->bunkers()) {
			if (bunker->missileDelay() <= 0) {
				auto missile = bunker->shoot(
						MISSILE_SPEED, MISSILE_LIFESPAN, MISSILE_RADIUS
				);

				mPlanet->surface()->insert(missile);
				bunker->missileDelay(MISSILE_DELAY);
			}
		}
	}
}
