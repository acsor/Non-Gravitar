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
#include "utils/Utils.hpp"
#include "Game.hpp"
#include "SpaceshipController.hpp"


namespace gvt {
	SceneChangeEvent::SceneChangeEvent(
			shared_ptr<Scene> old, shared_ptr<Scene> _new
	): oldScene{std::move(old)}, newScene{std::move(_new)} {
	}


	// Game class section
	Game* Game::sInstance = nullptr;

	void Game::onShipMoved(PositionEvent e) {
		auto sceneSize = mCurrScene->size() - Vectord{
				mShip->width(), mShip->height()
		};

		if (!mShip->position().within({0, 0}, sceneSize))
			mCurrScene->onExitBoundaries(mShip);
	}

	void Game::toggleDebug (sf::Event e) {
		if (
			e.type == sf::Event::KeyPressed && e.key.control &&
			e.key.code == sf::Keyboard::Key::B
		) {
			mCurrScene->mShapesView->setDebug(
					!mCurrScene->mShapesView->isDebug()
			);
		}
	}

	Game::Game () {
		mShip.reset(new Spaceship(Vectord{0, 0}, 50));

		mSceneFrame.reset(new SceneFrame(this, mShip));
		mInfoFrame.setViewport({0, 0, 1, .2});

		mInfo.reset(new GameInfo(0, 3));
		mInfoView.reset(new GameInfoView(this, mShip));

		mShip->positionDispatcher().addCallback(
			[this] (PositionEvent e) -> void { onShipMoved(e); }
		);
		mViewDisp.addCallback(
				SpaceshipController(this, mShip, 150.0, deg2rad(10))
		);
		mViewDisp.addCallback(
			[this] (sf::Event e) -> void { toggleDebug(e); }
		);
	}

	Game::~Game () {
		mShip->positionDispatcher().clearCallbacks();
		mViewDisp.clearCallbacks();
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

		if (mCurrScene->hasNextScene())
			swapScene(mCurrScene->nextScene());

		// If the current scene is not hold as a separate variable, some
		// code might pop it out and remove the only references to it (both
		// on stack and on mCurrScene). At that point, that scene object
		// would be destroyed by std::shared_ptr, causing segfaults.
		auto currScene = mCurrScene;

		currScene->onUpdateGame(elapsed);
	}

	void Game::pushScene (shared_ptr<Scene> scene) {
		auto e = SceneChangeEvent(mCurrScene, scene);

		mCurrScene = std::move(scene);
		mSceneStack.push(mCurrScene);

		mSceneDisp.raiseEvent(e);
	}

	void Game::swapScene (shared_ptr<Scene> newScene) {
		auto e = SceneChangeEvent(mCurrScene, newScene);

		mCurrScene = std::move(newScene);
		mSceneStack.top() = mCurrScene;

		mSceneDisp.raiseEvent(e);
	}

	shared_ptr<Scene> Game::popScene () {
		if (mSceneStack.empty()) {
			throw std::logic_error("No scene to pop out from the stack");
		} else {
			auto e = SceneChangeEvent(mCurrScene, nullptr);

			mSceneStack.pop();
			mCurrScene = mSceneStack.top();

			e.newScene = mCurrScene;
			mSceneDisp.raiseEvent(e);
		}

		return mCurrScene;
	}

	EventDispatcher<sf::Event>& Game::viewEventsDispatcher() {
		return mViewDisp;
	}

	void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const {
		auto targetSize = target.getSize();

		mInfoFrame.setSize(targetSize.x, .2f * targetSize.y);
		mInfoFrame.setCenter(.5f * targetSize.x, .1f * targetSize.y);
		target.setView(mInfoFrame);
		target.draw(*mInfoView, states);

		target.setView(*mSceneFrame);
		target.draw(*mCurrScene, states);
	}
}
