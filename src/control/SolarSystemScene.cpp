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
#include "Game.hpp"
#include "SolarSystemScene.hpp"
#include "PlanetSurfaceScene.hpp"


namespace gvt {
	void SolarSystemScene::onCollision (PairCollisionEvent e) {
		Scene::onCollision(e);

		auto ship = std::dynamic_pointer_cast<Spaceship>(e.first);
		auto planet = std::dynamic_pointer_cast<Planet>(e.second);

		if (!ship)
			ship = std::dynamic_pointer_cast<Spaceship>(e.second);
		if (!planet)
			planet = std::dynamic_pointer_cast<Planet>(e.first);

		if (ship && planet) {
			auto game = Game::getInstance();

			planet->surface()->insert(game->acquireSpaceship());
			game->pushScene(std::make_shared<PlanetSurfaceScene>(planet));

			ship->rotation(0);
			ship->velocity(ship->speed() * Vectord(M_PI / 2.0));
			ship->position({planet->surface()->width() / 2.0, 1});
		}
	}

	void SolarSystemScene::onShapeDestroyed (shared_ptr<Shape> shape) {
		Scene::onShapeDestroyed(shape);
		auto info = mGame->gameInfo();

		if (auto ship = std::dynamic_pointer_cast<Spaceship>(shape)) {
			if (info->spaceships() > 0) {
				shape->position({0, 0});
				shape->velocity({0, 0});
				shape->rotation(M_PI / 2.0);
				shape->destroyed(false);

				mShapes->insert(ship);
			}
		} else if (auto planet = std::dynamic_pointer_cast<Planet>(shape)) {
			info->upgradeScore(planet->bonus());
		}
	}

	void SolarSystemScene::onSceneChanged (SceneChangeEvent e) {
		auto planetScene = std::dynamic_pointer_cast<PlanetSurfaceScene>(
				e.oldScene
		);
		auto systemScene = std::dynamic_pointer_cast<SolarSystemScene>(
				e.newScene
		);

		// If we are transitioning from a planet surface scene back to the
		// starting solar system scene:
		if (planetScene && systemScene) {
			auto ship = Game::getInstance()->spaceship();
			auto planetCenter = planetScene->planet()->position();
			auto spawnAreaCenter = mSystem->spawnArea()->position();
			auto diff = spawnAreaCenter - planetCenter;

			diff.normalize();
			diff = (planetScene->planet()->radius() + ship->height()) * diff;

			ship->position(planetCenter - ship->rotationCenter() + diff);
			ship->rotation(diff.angle() + M_PI / 2.0);
			ship->velocity(ship->speed() * Vectord(diff.angle()));
		}
	}

	SolarSystemScene::SolarSystemScene(
			Vectord size, shared_ptr<SolarSystem> &system
	): Scene(size, system), mSystem{std::move(system)} {
		mSceneCbk = Game::getInstance()->addCallback(
			[this] (SceneChangeEvent e) -> void { onSceneChanged(e); }
		);
	}

	SolarSystemScene::~SolarSystemScene() {
		Game::getInstance()->removeCallback(mSceneCbk);
	}

	shared_ptr<SolarSystem> SolarSystemScene::solarSystem() const {
		return std::dynamic_pointer_cast<SolarSystem>(mShapes);
	}
}
