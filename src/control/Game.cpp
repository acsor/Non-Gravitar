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
#include <SFML/Graphics.hpp>

#include "shape/Planet.hpp"
#include "shape-group/CollisionGroup.hpp"
#include "shape-group/PlanetSurface.hpp"
#include "utils/Utils.hpp"
#include "Game.hpp"


namespace gvt {
	Game* Game::sInstance = nullptr;

	void Game::centerSceneView (std::shared_ptr<gvt::Event> const &e) {
		auto shapeEvent = std::dynamic_pointer_cast<ShapeEvent>(e);

		if (shapeEvent && shapeEvent->type == ShapeEvent::Type::moved) {
			auto position = mShip->position();

			mSceneView.setCenter(position.x, position.y);
		}
	}

	void Game::resizeSceneView (std::shared_ptr<sf::Event> const &e) {
		if (e->type == sf::Event::Resized) {
			mSceneView.setSize(e->size.width, e->size.height);
		}
	}

	void Game::toggleDebug (std::shared_ptr<sf::Event> const &e) {
		if (
			e->type == sf::Event::KeyPressed && e->key.control &&
			e->key.code == sf::Keyboard::Key::B
		) {
			mCurrScene->mShapesView->setDebug(
					!mCurrScene->mShapesView->isDebug()
			);
		}
	}

	Game::Game () {
		auto _1 = std::placeholders::_1;

		mShip.reset(new Spaceship(Vectord{0, 0}, 1000));
		mViewEvents.reset(new EventDispatcher<sf::Event>());

		mShip->addCallback(std::bind(&Game::centerSceneView, this, _1));

		mViewEvents->addCallback(std::bind(&Game::resizeSceneView, this, _1));
		mViewEvents->addCallback(MoveShipCallback(mShip, 150.0, deg2rad(10)));
		mViewEvents->addCallback(std::bind(&Game::toggleDebug, this, _1));

		mShip->position({960, 540});
	}

	Game::~Game () {
		mShip->clearCallbacks();
		mViewEvents->clearCallbacks();
	}

	Game* Game::getInstance () {
		if (sInstance == nullptr) {
			sInstance = new Game();
		}

		return sInstance;
	}

	shared_ptr<Spaceship> Game::acquireSpaceship() {
		if (mCurrScene)
			mCurrScene->mShapes->remove(mShip);

		return mShip;
	}

	void Game::updateGameLoop () {
		auto elapsed = mClock.restart().asSeconds();

		mCurrScene->onUpdateGame(elapsed);
	}

	void Game::pushScene (shared_ptr<Scene> scene) {
		mCurrScene = std::move(scene);
		mSceneStack.push(mCurrScene);
	}

	shared_ptr<Scene> Game::popScene () {
		if (mSceneStack.empty()) {
			throw std::logic_error("No scene to pop out from the stack");
		} else {
			mCurrScene = mSceneStack.top();
			mSceneStack.pop();
		}

		return mCurrScene;
	}

	shared_ptr<EventDispatcher<sf::Event>> Game::viewEventsDispatcher() const {
		return mViewEvents;
	}

	void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.setView(mSceneView);
		target.draw(*mCurrScene);
	}


	MoveShipCallback::MoveShipCallback (
			shared_ptr<Spaceship> ship, double accel, double angle
	): mShip(std::move(ship)) {
		mAccelStep = accel;
		mAngleStep = angle;
	}

	void MoveShipCallback::operator() (shared_ptr<sf::Event> e) {
		auto accelIncrement = mAccelStep * Vectord(mShip->rotation());
		accelIncrement.rotate(M_PI / -2.0);

		if (e->type == sf::Event::KeyPressed) {
			switch (e->key.code) {
				case (sf::Keyboard::Key::A):
					mShip->rotate(-mAngleStep);
					break;
				case (sf::Keyboard::Key::W):
					mShip->acceleration(accelIncrement);
					break;
				case (sf::Keyboard::Key::D):
					mShip->rotate(mAngleStep);
					break;
				case (sf::Keyboard::Key::S):
					// Should activate the shields in a future version
					// of the program
					break;
				default:
					break;
			}
		} else if (e->type == sf::Event::KeyReleased) {
			if (e->key.code == sf::Keyboard::Key::W) {
				mShip->acceleration(Vectord{0, 0});
			}
		}
	}
}
