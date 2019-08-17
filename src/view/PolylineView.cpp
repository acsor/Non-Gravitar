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
#include "PolylineView.hpp"


namespace gvt {
	PolylineView::PolylineView(shared_ptr<Polyline> shape): ShapeView(shape) {
		mVertices = sf::VertexArray(sf::LineStrip, shape->size() + 1);

        for (size_t i = 0; i < shape->size(); i++) {
        	mVertices[i] = sf::Vertex(
				sf::Vector2f((*shape)[i].x, (*shape)[i] .y), mColor
			);
		}

		mVertices[shape->size()] = sf::Vertex(
			sf::Vector2f((*shape)[0].x, (*shape)[0] .y), mColor
		);
	}

	void PolylineView::draw(RenderTarget &target, RenderStates state) const {
		ShapeView::draw(target, state);

		target.draw(mVertices, mTranslation * mRotation);
	}
}
