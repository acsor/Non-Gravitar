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
#include "FuelView.hpp"
#include "utils/Utils.hpp"
#include "GraphicAssets.hpp"


namespace gvt {
	void FuelView::draw (sf::RenderTarget &t, sf::RenderStates s) const {
		ClosedShapeView::draw(t, s);

		t.draw(mSprite, mTranslation * mRotation);
		t.draw(mText, mTranslation * mRotation);
	}

	FuelView::FuelView (shared_ptr<Fuel> const &fuel): ClosedShapeView(fuel) {
		auto a = GraphicAssets::getInstance();
		mSprite.setTexture(a->fuelTexture);

		mText = sf::Text(std::to_string(fuel->fuel()), a->defaultFont, 16);
		mText.setPosition(0, fuel->height() / 2.0);
		mText.setFillColor(sf::Color::White);
		mText.setLetterSpacing(1.5);
		mText.setStyle(sf::Text::Bold);
	}
}
