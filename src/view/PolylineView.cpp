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
	sf::Color const PolylineView::DEFAULT_COLOR = sf::Color::Yellow;

	void PolylineView::updateView() {
		auto polyline = std::dynamic_pointer_cast<Polyline>(mShape.lock());

		if (polyline) {
			mVertices = sf::VertexArray(sf::LineStrip, polyline->size());
			auto vertex = polyline->begin();

			for (size_t i = 0; i < polyline->size(); i++, vertex++) {
				mVertices[i] = sf::Vertex(
						sf::Vector2f(vertex->x, vertex->y), mColor
				);
			}
		}
	}

	void PolylineView::updateDebugView() {
		mColor = mDebug ? mDebugColor: DEFAULT_COLOR;
		updateView();
	}

	void PolylineView::updateRotation() {
		// TODO Implement, if necessary
	}

	void PolylineView::onDraw(
			shared_ptr<Shape> shape, RenderTarget &t, RenderStates s
	) const {
		t.draw(mVertices, mTranslation * mRotation);
	}

	PolylineView::PolylineView(shared_ptr<Polyline> shape): ShapeView(shape) {
		updateView();
	}

	void PolylineView::setDebug (bool debug) {
		// Contrary to other ShapeView subclasses, PolylineView directly uses
		// its own normal view for debug too
        DebuggableView::setDebug(debug);

        updateDebugView();
	}
}
