// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#include "RoundMissileView.hpp"


namespace gvt {
	sf::Color const RoundMissileView::DEFAULT_MISSILE_COLOR = sf::Color(
			255, 245, 0
	);

	RoundMissileView::RoundMissileView (shared_ptr<RoundMissile> missile):
			ClosedShapeView(missile), mMissile(std::move(missile)) {
		mCircle = sf::CircleShape(mMissile->radius());
		mCircle.setFillColor(DEFAULT_MISSILE_COLOR);
	}


	void RoundMissileView::draw(sf::RenderTarget &t, sf::RenderStates s) const {
		ClosedShapeView::draw(t, s);

		t.draw(mCircle, mTranslation * mRotation);
	}
}
