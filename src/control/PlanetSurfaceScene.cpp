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
#include "SolarSystemScene.hpp"


namespace gvt {
	void PlanetSurfaceScene::exitPlanet() {
		auto game = Game::getInstance();
		auto ship = game->acquireSpaceship();

		game->popScene();
		// game->currentScene() will be a SolarSystemScene
		game->currentScene()->shapeGroup()->insert(ship);
	}

	void PlanetSurfaceScene::onExitBoundaries(shared_ptr<Spaceship> ship) {
		if (ship->position().y <= 0)
			exitPlanet();
		else
			Scene::onExitBoundaries(ship);
	}

	void PlanetSurfaceScene::onSpaceshipDestroyed (shared_ptr<Spaceship> ship) {
		Scene::onSpaceshipDestroyed(ship);

		if (mGame->gameInfo()->spaceships() > 0) {
			ship->position({mSize.x / 2.0, 1});
			ship->velocity({0, 0});
			ship->rotation(M_PI);
			ship->destroyed(false);

			mShapes->insert(ship);
		}
	}

	PlanetSurfaceScene::PlanetSurfaceScene(shared_ptr<PlanetSurface> const &s):
			Scene({s->width(), s->height()}, s) {
	}

	PlanetSurfaceScene::PlanetSurfaceScene (shared_ptr<Planet> const &planet):
			PlanetSurfaceScene(planet->surface()) {
		mPlanet = planet;
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
