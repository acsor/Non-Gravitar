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
#include <iostream>
#include "ShapeView.hpp"
#include "shape/Rectangle.hpp"
#include "utils/Utils.hpp"

using Shape = gvt::Shape;
using ShapeView = gvt::ShapeView;


void ShapeView::updateDebugBounds() {
    if (auto shape = mShape.lock()) {
    	// Reallocating mBounds each time is not efficient, but this computation
    	// is only performed when mDebug == true, so this is not a real concern
		vector<BoundingPolygon::Vertex>
		        vertices = shape->collisionPolygon().vertices();
		mBounds = sf::VertexArray(sf::LineStrip, vertices.size());

        for (size_t i = 0; i < vertices.size(); i++) {
			mBounds[i] = sf::Vector2f(vertices[i].x, vertices[i].y);
			mBounds[i].color = sf::Color::Green;
		}
    } else {
    	mBounds.clear();
    }
}

ShapeView::ShapeView(shared_ptr<Shape> shape, bool debug):
	Debuggable(debug), mShape{shape} {
	updateDebugBounds();

	shape->addHandler(*this);
}

ShapeView::~ShapeView() {
	if (auto p = mShape.lock())
		p->removeHandler(*this);
}

void ShapeView::draw(RenderTarget &target, RenderStates s) const {
	if (mDebug && !mShape.expired())
		target.draw(mBounds);
}

void ShapeView::handle(Event *e) {
	Rectangle box{{0, 0}, {0, 0}};
	auto event = dynamic_cast<ShapeEvent*>(e);

	if (event) {
		if (auto shape = mShape.lock()) {
			if (
					mDebug &&
					(event->type == ShapeEvent::Type::moved ||
					event->type == ShapeEvent::Type::rotated)
			) {
				updateDebugBounds();
			}
		}
		if (event->type == ShapeEvent::Type::destroyed) {
			mShape.reset();
			event->shape->removeHandler(*this);
		}
	}
}
