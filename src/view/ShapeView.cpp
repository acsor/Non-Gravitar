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
#include "ShapeView.hpp"

using namespace std::placeholders;


namespace gvt {
	void ShapeView::shapeChangeCallback (shared_ptr<Event> e) {
		auto event = std::dynamic_pointer_cast<ShapeEvent>(e);

		if (event) {
			switch (event->type) {
				case (ShapeEvent::Type::moved):
					onShapeMoved();
					break;
				case (ShapeEvent::Type::rotated):
					onShapeRotated();
					break;
				case (ShapeEvent::Type::destroyed):
					onShapeDestroyed();
					mShape.reset();
					event->shape->removeCallback(mCallback);
					break;
				default:
					break;
			}
		}
	}

	void ShapeView::updateTranslation() {
		auto const pos = mShape->position();

		mTranslation = sf::Transform::Identity;
		mTranslation.translate(pos.x, pos.y);
	}

	ShapeView::ShapeView(shared_ptr<Shape> const &shape): mShape(shape) {
		mRotation = sf::Transform::Identity;

		mCallback = shape->addCallback(
			std::bind(&ShapeView::shapeChangeCallback, this, _1)
		);
		updateTranslation();
	}

	void ShapeView::onShapeMoved() {
		updateTranslation();
	}

	void ShapeView::onShapeRotated() {
		updateRotation();
	}

	ShapeView::~ShapeView() {
		mShape->removeCallback(mCallback);
	}
}
