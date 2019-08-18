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
#include <stdexcept>
#include "SpaceshipView.hpp"
#include "utils/Utils.hpp"

using SpaceshipView = gvt::SpaceshipView;


const std::string SpaceshipView::SPACESHIP_TEXTURE = "graphics/spaceship.png";
const std::string SpaceshipView::ACCEL_SPACESHIP_TEXTURE =
	"graphics/spaceship-accelerating.png";


SpaceshipView::SpaceshipView(shared_ptr<Spaceship> const &spaceship):
	Shape2DView(spaceship), mSpaceship{spaceship} {
	if (
			!mTexture.loadFromFile(gvt::staticsGet(SPACESHIP_TEXTURE)) ||
			!mAccelTexture.loadFromFile(
				gvt::staticsGet(ACCEL_SPACESHIP_TEXTURE)
			)
	   ) {
		throw std::runtime_error{
			"Could not load spaceship textures from disk"
		};
	}

	mTexture.setSmooth(true);
	mAccelTexture.setSmooth(true);
	mSprite.setTexture(mTexture);
}

void SpaceshipView::onDraw(
		shared_ptr<Shape> shape, RenderTarget &target, RenderStates s
) const {
	Shape2DView::onDraw(shape, target, s);

	if (mAccel) {
		mSprite.setTexture(mAccelTexture);
		target.draw(mSprite, mTranslation * mRotation);
		mSprite.setTexture(mTexture);

		mAccel = false;
	} else {
		target.draw(mSprite, mTranslation * mRotation);
	}
}

void SpaceshipView::onMoved () {
	Shape2DView::onMoved();

    if (auto ship = mSpaceship.lock())
    	mAccel = ship->acceleration().norm() != 0;
}

void SpaceshipView::onDestroyed () {
	Shape2DView::onDestroyed();
	mSprite = sf::Sprite();
}
