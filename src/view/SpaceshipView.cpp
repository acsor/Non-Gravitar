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
#include "SpaceshipView.hpp"

using SpaceshipView = gvt::SpaceshipView;


SpaceshipView::SpaceshipView(shared_ptr<Spaceship> const &spaceship):
		ClosedShapeView(spaceship), mShip{spaceship} {
	mAssets = GraphicAssets::getInstance();

	mSprite.setTexture(mAssets->spaceshipTexture);
}

void SpaceshipView::draw(sf::RenderTarget &target, sf::RenderStates s) const {
	ClosedShapeView::draw(target, s);

	if (mAccel) {
		mSprite.setTexture(mAssets->spaceshipTextureAccel);
		target.draw(mSprite, mTranslation * mRotation);
		mSprite.setTexture(mAssets->spaceshipTexture);
	} else {
		target.draw(mSprite, mTranslation * mRotation);
	}
}

void SpaceshipView::onShapeMoved(PositionEvent e) {
	ClosedShapeView::onShapeMoved(e);

	mAccel = mShip->acceleration().norm() != 0;
}
