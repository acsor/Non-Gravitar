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

#include "PlanetView.hpp"
#include "GraphicAssets.hpp"
#include "utils/Random.hpp"


namespace gvt {
	const std::vector<sf::Color> PlanetView::OUTLINE_COLORS = {
			sf::Color(207, 245, 0),	// Fluorescent yellow
			sf::Color(197, 0, 0),	// Almost red
	};

	PlanetView::PlanetView (shared_ptr<Planet> const &planet):
			ClosedShapeView{planet} {
		auto a = GraphicAssets::getInstance();
		auto cPolygon = planet->collisionPolygon();

		auto bonusAngle = UniRandom<float>(0, 2 * M_PI)();
		float bonusRadius = 2.0f * planet->radius();
		auto bonusText = std::to_string(planet->bonus());

		auto randomColor = UniRandom<int>(0, OUTLINE_COLORS.size() - 1);

		mBonus = sf::Text(bonusText, a->defaultFont, BONUS_FONT_SIZE);
		mBonus.setPosition(
			bonusRadius * sf::Vector2f(cos(bonusAngle), sin(bonusAngle))
		);
		mBonus.setFillColor(sf::Color::Cyan);

		mOutlineColor = OUTLINE_COLORS[randomColor()];
		mPolygon = sf::VertexArray(sf::LineStrip, cPolygon.size() + 1);

		for (size_t i = 0; i < mPolygon.getVertexCount(); i++) {
			auto v = cPolygon.vertices()[i];

			mPolygon[i].color = mOutlineColor;
			mPolygon[i].position = {(float) v.x, (float) v.y};
		}

		mPolygon[8].color = mOutlineColor;
		mPolygon[8].position = {(float) cPolygon[0].x, (float) cPolygon[0].y};
	}

	void PlanetView::draw(sf::RenderTarget &t, sf::RenderStates s) const {
		ClosedShapeView::draw(t, s);

		t.draw(mPolygon, mTranslation * mRotation);
		t.draw(mBonus, mTranslation * mRotation);
	}
}
