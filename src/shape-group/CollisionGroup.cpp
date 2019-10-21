// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#include "CollisionGroup.hpp"

#include <memory>
#include <unordered_map>
#include <shape/Spaceship.hpp>

namespace gvt {
	void CollisionGroup::onInsertShape (shared_ptr<Shape> shape) {
		shape->positionDispatcher().addCallback(mPosCallback);
		shape->rotationDispatcher().addCallback(mRotCallback);

		updateCollisions();
	}

	void CollisionGroup::onRemoveShape (shared_ptr<Shape> shape) {
		shape->positionDispatcher().removeCallback(mPosCallback);
		shape->rotationDispatcher().removeCallback(mRotCallback);
	}

	void CollisionGroup::onShapeMoved (ShapeEvent e) {
		updateCollisions();
	}

	void CollisionGroup::onShapeRotated (RotationEvent e) {
		updateCollisions();
	}

	void CollisionGroup::updateCollisions() {
		auto shapes = mShapes;
		std::unordered_map<shared_ptr<Shape>, bool> collided{shapes.size()};

		for (auto const &e: shapes)
			collided[e] = false;

		// This is deliberately a brute-force algorithm. A simple
		// optimization technique, which we have no time for, consists of
		// managing a neighbourhood of shapes and checking collisions against
		// them only
		for (auto first = shapes.begin(); first != shapes.end(); first++) {
			auto second = first;

			second++;

			while (second != shapes.end()) {
				if (first->get()->clashes(**second)) {
					collided[*first] = true;
					collided[*second] = true;

					first->get()->collided(true);
					second->get()->collided(true);

					mCollisionDisp.raiseEvent({*first, *second});
				}

				second++;
			}
		}

		for (auto const &pair: collided) {
			if (!pair.second)
				pair.first->collided(false);
		}
	}

	CollisionGroup::CollisionGroup() {
		mPosCallback = std::make_shared<Callback<PositionEvent>>(
			[this] (PositionEvent e) -> void { onShapeMoved(e); }
		);
		mRotCallback = std::make_shared<Callback<RotationEvent>>(
			[this] (RotationEvent e) -> void { onShapeRotated(e); }
		);
	}

	EventDispatcher<PairCollisionEvent>& CollisionGroup::collisionDispatcher() {
		return mCollisionDisp;
	}

	PairCollisionEvent::PairCollisionEvent(
			shared_ptr<Shape> _first, shared_ptr<Shape> _second
	): first{std::move(_first)}, second{std::move(_second)} {
	}
}
