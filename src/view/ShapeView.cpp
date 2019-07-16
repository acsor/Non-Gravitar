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
#include "../model/Rectangle.hpp"
#include "../Utils.hpp"

using Shape = gvt::Shape;
using ShapeView = gvt::ShapeView;


ShapeView::ShapeView(shared_ptr<Shape> shape, bool debug): mShape{shape} {
	gvt::Rectangle bounds = shape->globalBounds();

	mDebug = debug;

	mBounds = sf::RectangleShape({bounds.width(), bounds.height()});
	mBounds.setPosition(bounds.x(), bounds.y());
	mBounds.setOrigin(bounds.originX(), bounds.originY());
	mBounds.setRotation(gvt::rad2deg(bounds.rotation()));
	mBounds.setFillColor(sf::Color::Green);

	shape->attachListener(*this);
}

ShapeView::~ShapeView() {
	if (auto p = mShape.lock())
		p->detachListener(*this);
}

bool ShapeView::debug() const {
	return mDebug;
}

void ShapeView::debug(bool debug) {
	mDebug = debug;
}

void ShapeView::draw(RenderTarget &target, RenderStates s) const {
	if (mDebug && !mShape.expired())
		target.draw(mBounds);
}

void ShapeView::handle(Event *e) {
	Rectangle box{{0, 0}, {0, 0}};
	auto event = dynamic_cast<ShapeEvent*>(e);

	if (event) {
		if (auto p = mShape.lock()) {
			box = p->globalBounds();

			if (event->type == ShapeEvent::Type::moved) {
				mBounds.setPosition(box.x(), box.y());
			} else if (event->type == ShapeEvent::Type::origin) {
				mBounds.setOrigin(box.originX(), box.originY());
			} else if (event->type == ShapeEvent::Type::rotated) {
				mBounds.setRotation(gvt::rad2deg(box.rotation()));
			}
		} else if (event->type == ShapeEvent::Type::destroyed) {
			mShape.reset();
			event->shape->detachListener(*this);
		}
	}
}
