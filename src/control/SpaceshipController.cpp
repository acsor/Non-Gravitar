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
#include "SpaceshipController.hpp"
#include "Game.hpp"


namespace gvt {
	SpaceshipController::SpaceshipController (
			Game *game, shared_ptr<Spaceship> ship, double accel, double angle
	): mGame{game}, mShip(std::move(ship)) {
		mAccelStep = accel;
		mAngleStep = angle;
	}

	void SpaceshipController::operator() (sf::Event e) {
		auto accelIncrement = mAccelStep * Vectord(mShip->rotation());
		accelIncrement.rotate(M_PI / -2.0);

		if (mGame->gameInfo()->spaceships() <= 0)
			return;

		if (e.type == sf::Event::KeyPressed) {
			switch (e.key.code) {
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
				case (sf::Keyboard::Key::K):
					if (!mLastScene) {
						mLastScene = mGame->currentScene();
						mLastScene->shapeGroup()->insert(mShip->tractorBeam());
					}
					break;
				case (sf::Keyboard::Key::Space):
					mGame->currentScene()->shapeGroup()->insert(
							mShip->shoot(6, 700, 2000)
					);
					break;
				default:
					break;
			}
		} else if (e.type == sf::Event::KeyReleased) {
			switch (e.key.code) {
				case sf::Keyboard::Key::W:
					mShip->acceleration(Vectord{0, 0});
					break;
				case sf::Keyboard::Key::K:
					if (mLastScene) {
						mLastScene->shapeGroup()->remove(mShip->tractorBeam());
						mLastScene = nullptr;
					}
					break;
				default:
					break;
			}
		}
	}
}
