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
#include <utility>


namespace gvt {
	void ShapeView::updateTranslationTransform() {
		auto const pos = mShape->position();

		mTranslation = sf::Transform::Identity;
		mTranslation.translate(pos.x, pos.y);
	}

	ShapeView::ShapeView(shared_ptr<Shape> shape): mShape(std::move(shape)) {
		auto _1 = std::placeholders::_1;
		mRotation = sf::Transform::Identity;

		mPosCbk = mShape->positionDispatcher().addCallback(
			std::bind(&ShapeView::onShapeMoved, this, _1)
		);
		mRotCbk = mShape->rotationDispatcher().addCallback(
			std::bind(&ShapeView::onShapeRotated, this, _1)
		);
		mColCbk = mShape->collisionDispatcher().addCallback(
			std::bind(&ShapeView::onShapeCollided, this, _1)
		);

		updateTranslationTransform();
	}

	void ShapeView::onShapeMoved(shared_ptr<PositionEvent> e) {
		updateTranslationTransform();
	}

	void ShapeView::onShapeRotated(shared_ptr<RotationEvent> e) {
		updateRotationTransform();
	}

	ShapeView::~ShapeView() {
		mShape->positionDispatcher().removeCallback(mPosCbk);
		mShape->rotationDispatcher().removeCallback(mRotCbk);
		mShape->collisionDispatcher().removeCallback(mColCbk);
	}
}
