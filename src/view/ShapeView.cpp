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
	gvt::Rectangle bounds = shape->collisionBox();

	mDebug = debug;

	mBounds = sf::RectangleShape({bounds.width(), bounds.height()});
	mBounds.setPosition(bounds.x(), bounds.y());
	mBounds.setOrigin(bounds.originX(), bounds.originY());
	mBounds.setRotation(gvt::rad2deg(bounds.rotation()));

	mBounds.setFillColor(sf::Color::Green);
	mBounds.setOutlineColor(sf::Color::Red);
	mBounds.setOutlineThickness(1.5);
}

void ShapeView::draw(RenderTarget &target, RenderStates s) const {
	if (mDebug && !mShape.expired())
		target.draw(mBounds);
}

void ShapeView::handle(Event const &e) {
	if (auto p = mShape.lock()) {
		if (e == Shape::MOVE) {
			mBounds.setPosition(p->collisionBox().x(), p->collisionBox().y());
		} else if (e == Shape::ORIGIN) {
			mBounds.setOrigin(
				p->collisionBox().originX(), p->collisionBox().originY()
			);
		} else if (e == Shape::ROTATION) {
			mBounds.setRotation(gvt::rad2deg(p->collisionBox().rotation()));
		}
	}
}
