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
#include "SceneFrame.hpp"
#include "Game.hpp"


namespace gvt {
	void SceneFrame::onWindowResized(sf::Event e) {
		if (e.type == sf::Event::Resized) {
			auto windowSize = Vectord(e.size.width, 0.8 * e.size.height);

			mView.setSize(windowSize.x, windowSize.y);

			mMin = windowSize / 2.0;
			mMax = mGame->currentScene()->size() - mMin;
		}
	}

	void SceneFrame::onSceneChanged(SceneChangeEvent e) {
		mMax = e.newScene->size() - mMin;
	}

	void SceneFrame::onShipMoved (PositionEvent e) {
		auto position = mShip->position() + mShip->rotationCenter();

		position.x = std::max(mMin.x, position.x);
		position.x = std::min(mMax.x, position.x);
		position.y = std::max(mMin.y, position.y);
		position.y = std::min(mMax.y, position.y);

		mView.setCenter(position.x, position.y);
	}

	SceneFrame::SceneFrame(Game *game, shared_ptr<Spaceship> ship):
			mGame{game}, mShip{std::move(ship)} {
		mView.setViewport({0.0, 0.2, 1, 0.8});

		mResizeCbk = mGame->viewEventsDispatcher().addCallback(
				[this] (sf::Event e) -> void { onWindowResized(e); }
		);
		mSceneCbk = mGame->addCallback(
				[this] (SceneChangeEvent e) -> void { onSceneChanged (e); }
		);
		mShipCbk = mShip->positionDispatcher().addCallback(
				[this] (PositionEvent e) -> void { onShipMoved (e); }
		);
	}

	SceneFrame::~SceneFrame() {
		mGame->viewEventsDispatcher().removeCallback(mResizeCbk);
		mGame->removeCallback(mSceneCbk);
		mShip->positionDispatcher().removeCallback(mShipCbk);
	}
}
