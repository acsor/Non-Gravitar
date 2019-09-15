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
	SceneChangedEvent::SceneChangedEvent(
			shared_ptr<Scene> old, shared_ptr<Scene> _new
	): oldScene{std::move(old)}, newScene{std::move(_new)} {
	}


	// Game class section
	Game* Game::sInstance = nullptr;

	void Game::onShipMoved(shared_ptr<PositionEvent> e) {
		auto pos = mShip->position();
		auto sceneSize = mCurrScene->size() - Vectord{
				mShip->width(), mShip->height()
		};

		if (!pos.within({0, 0}, sceneSize)) {
			pos.x = std::max(pos.x, 0.0);
			pos.x = std::min(pos.x, sceneSize.x);
			pos.y = std::max(pos.y, 0.0);
			pos.y = std::min(pos.y, sceneSize.y);

			mShip->position(pos);
			mShip->velocity({0, 0});
			mShip->acceleration({0, 0});
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
		mSceneFrame.reset(new SceneFrame(this, mShip));

		mInfo.reset(new GameInfo(0, 3));
		mInfoView.reset(new GameInfoView(mInfo, mShip));

		mShip->positionDispatcher().addCallback(
				std::bind(&Game::onShipMoved, this, _1)
		);
		mViewEvents.addCallback(
				MoveShipCallback(this, mShip, 150.0, deg2rad(10))
		);
		mViewEvents.addCallback(std::bind(&Game::toggleDebug, this, _1));
	}

	Game::~Game () {
		mShip->positionDispatcher().clearCallbacks();
		mViewEvents.clearCallbacks();
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

	shared_ptr<Spaceship> Game::spaceship() {
		return mShip;
	}

	void Game::updateGameLoop () {
		auto elapsed = mClock.restart().asSeconds();

		mCurrScene->onUpdateGame(elapsed);
	}

	void Game::pushScene (shared_ptr<Scene> scene) {
		auto e = std::make_shared<SceneChangedEvent>(mCurrScene, scene);

		mCurrScene = std::move(scene);
		mSceneStack.push(mCurrScene);

		raiseEvent(e);
	}

	shared_ptr<Scene> Game::popScene () {
		if (mSceneStack.empty()) {
			throw std::logic_error("No scene to pop out from the stack");
		} else {
			auto e = std::make_shared<SceneChangedEvent>(
					mCurrScene, mSceneStack.top()
			);

			mSceneStack.pop();
			mCurrScene = mSceneStack.top();

			raiseEvent(e);
		}

		return mCurrScene;
	}

	EventDispatcher<sf::Event>& Game::viewEventsDispatcher() {
		return mViewEvents;
	}

	void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		auto targetSize = target.getSize();
		sf::View infoFrame;

		infoFrame.setSize(targetSize.x, .2f * targetSize.y);
		infoFrame.setCenter(.5f * targetSize.x, .1f * targetSize.y);
		infoFrame.setViewport({0, 0, 1, .2});
		target.setView(infoFrame);
		target.draw(*mInfoView, states);

		target.setView(mSceneFrame->sceneView());
		target.draw(*mCurrScene, states);
	}


	// SceneFrame class section
	void SceneFrame::onWindowResized(shared_ptr<sf::Event> const &e) {
		if (e->type == sf::Event::Resized) {
			auto windowSize = Vectord(e->size.width, 0.8 * e->size.height);

			mView.setSize(windowSize.x, windowSize.y);

			mMin = windowSize / 2.0;
			mMax = mGame->currentScene()->size() - mMin;
		}
	}

	void SceneFrame::onSceneChanged(shared_ptr<SceneChangedEvent> e) {
		mMax = e->newScene->size() - mMin;
	}

	void SceneFrame::onShipMoved (shared_ptr<PositionEvent> e) {
		auto position = mShip->position() + mShip->rotationCenter();

		position.x = std::max(mMin.x, position.x);
		position.x = std::min(mMax.x, position.x);
		position.y = std::max(mMin.y, position.y);
		position.y = std::min(mMax.y, position.y);

		mView.setCenter(position.x, position.y);
	}

	SceneFrame::SceneFrame(Game *game, shared_ptr<Spaceship> ship):
			mGame{game}, mShip{std::move(ship)} {
		auto _1 = std::placeholders::_1;

		mView.setViewport({0.0, 0.2, 1, 0.8});
		mResizeHandle = mGame->viewEventsDispatcher().addCallback(
			std::bind(&SceneFrame::onWindowResized, this, _1)
		);
		mSceneHandle = mGame->addCallback(
			std::bind(&SceneFrame::onSceneChanged, this, _1)
		);
		mShipHandle = mShip->positionDispatcher().addCallback(
			std::bind(&SceneFrame::onShipMoved, this, _1)
		);
	}

	SceneFrame::~SceneFrame() {
		mGame->viewEventsDispatcher().removeCallback(mResizeHandle);
		mGame->removeCallback(mSceneHandle);
		mShip->positionDispatcher().removeCallback(mShipHandle);
	}


	// MoveShipCallback class section
	MoveShipCallback::MoveShipCallback (
			Game *game, shared_ptr<Spaceship> ship, double accel, double angle
	): mGame{game}, mShip(std::move(ship)) {
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
					mShip->dischargeFuel(1);
					break;
				case (sf::Keyboard::Key::D):
					mShip->rotate(mAngleStep);
					break;
				case (sf::Keyboard::Key::S):
					// Should activate the shields in a future version
					// of the program
					break;
				case (sf::Keyboard::Key::Space):
					mGame->currentScene()->shapes()->insert(
							mShip->shoot(6, 700, 2000)
					);
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
