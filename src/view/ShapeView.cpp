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


namespace gvt {
	void ShapeView::updateTranslationTransform() {
		auto const pos = mShape->position();

		mTranslation = sf::Transform::Identity;
		mTranslation.translate(pos.x, pos.y);
	}

	ShapeView::ShapeView(shared_ptr<Shape> shape): mShape(std::move(shape)) {
		mRotation = sf::Transform::Identity;

		mPosCbk = mShape->positionDispatcher().addCallback(
			[this] (shared_ptr<PositionEvent> e) -> void { onShapeMoved(e); }
		);
		mRotCbk = mShape->rotationDispatcher().addCallback(
			[this] (shared_ptr<RotationEvent> e) -> void { onShapeRotated(e); }
		);
		mColCbk = mShape->collisionDispatcher().addCallback(
			[this] (shared_ptr<CollisionEvent> e) -> void { onShapeCollided(e); }
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
