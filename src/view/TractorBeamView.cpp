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
#include "TractorBeamView.hpp"
#include "utils/Utils.hpp"


namespace gvt {
	const sf::Color TractorBeamView::BEAM_COLOR = sf::Color::Magenta;

	void TractorBeamView::draw (sf::RenderTarget &t, sf::RenderStates s) const {
		Shape2DView::draw(t, s);

		t.draw(mTriangle, mTranslation * mRotation);
	}

	TractorBeamView::TractorBeamView (shared_ptr<TractorBeam> const &beam):
			Shape2DView(beam) {
		mTriangle = sf::VertexArray(sf::LineStrip, 4);

		for (size_t i = 0; i < mTriangle.getVertexCount(); i++)
			mTriangle[i].color = BEAM_COLOR;

		mTriangle[0].position = {0, (float) beam->height()};
		mTriangle[1].position = {(float) (beam->width() / 2.0), 0};
		mTriangle[2].position = {(float) beam->width(), (float) beam->height()};
		mTriangle[3].position = {0, (float) beam->height()};
	}
}
