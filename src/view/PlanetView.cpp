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

#include "PlanetView.hpp"
#include "GraphicAssets.hpp"


namespace gvt {
	const sf::Color PlanetView::DEFAULT_OUTLINE_COLOR = sf::Color(0, 138, 0);

	PlanetView::PlanetView (shared_ptr<Planet> const &planet):
			Shape2DView{planet} {
		mCircle = sf::CircleShape(planet->radius());

		mCircle.setFillColor(sf::Color::Transparent);
		mCircle.setOutlineColor(DEFAULT_OUTLINE_COLOR);
		mCircle.setOutlineThickness(2);
	}

	void PlanetView::draw(RenderTarget &t, RenderStates s) const {
		Shape2DView::draw(t, s);

		t.draw(mCircle, mTranslation * mRotation);
	}
}
