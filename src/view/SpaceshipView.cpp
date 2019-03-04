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
#include "Utils.hpp"

using SpaceshipView = gvt::SpaceshipView;


SpaceshipView::SpaceshipView(shared_ptr<Spaceship> spaceship, bool debug):
	mSpaceship{spaceship}, mDebug{debug} {
	if (
			!mTexture.loadFromFile(gvt::staticsGet(GVT_ASSET_SPACESHIP)) ||
			!mAccelTexture.loadFromFile(
				gvt::staticsGet(GVT_ASSET_SPACESHIP_ACCEL)
			)
	   ) {
		throw std::runtime_error{
			"Could not load spaceship textures from disk"
		};
	}

	mTexture.setSmooth(true);
	mAccelTexture.setSmooth(true);

	mSprite.setPosition(spaceship->x(), spaceship->y());
	mSprite.setOrigin(spaceship->originX(), spaceship->originY());
	mSprite.setRotation(gvt::rad2deg(spaceship->rotation()));
	mSprite.setTexture(mTexture);

	spaceship->attach(*this);
}

SpaceshipView::~SpaceshipView() {
	if (auto p = mSpaceship.lock()) {
		p->detach(*this);
	}
}

void SpaceshipView::draw(RenderTarget &target, RenderStates state) const {
	if (mAccel) {
		mSprite.setTexture(mAccelTexture);
		target.draw(mSprite);
		mSprite.setTexture(mTexture);

		mAccel = false;
	} else {
		target.draw(mSprite);
	}
}

void SpaceshipView::handle(Event const &e) {
	if (auto p = mSpaceship.lock()) {
		if (e == Shape::MOVE) {
			mSprite.setPosition(p->x(), p->y());
			mAccel = true;
		} else if (e == Shape::ORIGIN) {
			mSprite.setOrigin(p->originX(), p->originY());
		} else if (e == Shape::ROTATION) {
			mSprite.setRotation(gvt::rad2deg(p->rotation()));
		} else if (e == Shape::DESTROIED) {
			mSprite = sf::Sprite();
		}
	}
}
