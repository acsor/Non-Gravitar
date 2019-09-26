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
#include "SpawnAreaView.hpp"


namespace gvt {
	sf::Color const SpawnAreaView::OUTER_COLOR = sf::Color(205, 205, 205);
	sf::Color const SpawnAreaView::INNER_COLOR = sf::Color(80, 0, 232);

	void SpawnAreaView::draw(sf::RenderTarget& s, sf::RenderStates t) const {
		ClosedShapeView::draw(s, t);

		s.draw(mOuter, mTranslation * mRotation);
		s.draw(mInner, mTranslation * mRotation);
	}

	SpawnAreaView::SpawnAreaView(shared_ptr<SpawnArea> area):
			ClosedShapeView(area) {
		auto cPolygon = area->collisionPolygon();
		unsigned i;

		mOuter = sf::VertexArray(sf::LineStrip, area->vertices() + 1);
		mInner = sf::VertexArray(sf::LineStrip, area->vertices() + 1);

		for (i = 0; i < area->vertices(); i++) {
			auto v = cPolygon[i];

			mOuter[i].position = {(float) v.x, (float) v.y};
			mInner[i].position = 0.8f * mOuter[i].position;

			mOuter[i].color = OUTER_COLOR;
			mInner[i].color = INNER_COLOR;
		}

		mOuter[i].position = {(float) cPolygon[0].x, (float) cPolygon[0].y};
		mInner[i].position = 0.8f * mOuter[i].position;

		mOuter[i].color = OUTER_COLOR;
		mInner[i].color = INNER_COLOR;
	}
}
