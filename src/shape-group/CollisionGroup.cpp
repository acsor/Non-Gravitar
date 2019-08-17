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
#include "CollisionGroup.hpp"

namespace gvt {
	void CollisionGroup::onInsertShape (shared_ptr<Shape> shape) {
        shape->addCallback(mCallback);
        updateCollisions();
	}

	void CollisionGroup::onRemoveShape (shared_ptr<Shape> shape) {
        shape->removeCallback(mCallback);
	}

	void CollisionGroup::shapeChangeCallback (shared_ptr<Event> e) {
		auto shapeEvent = std::dynamic_pointer_cast<ShapeEvent>(e);

		if (shapeEvent) {
			switch (shapeEvent->type) {
				case ShapeEvent::Type::moved:
				case ShapeEvent::Type::rotated:
					updateCollisions();
					break;
				default:
					break;
			}
		}
	}

	void CollisionGroup::updateCollisions() {
		CollisionEvent *e;

		// This is deliberately a brute-force algorithm. A simple
		// optimization technique, which we have no time for, consists of
		// managing a neighbourhood of shapes and checking collisions against
		// them only
		for (auto &first: mShapes) {
			for (auto &second: mShapes) {
				if (*first != *second && first->clashes(*second)) {
					e = new CollisionEvent();
					e->first = first;
					e->second = second;

					notify(std::shared_ptr<CollisionEvent>(e));
				}
			}
		}
	}

	CollisionGroup::CollisionGroup() {
		using namespace std::placeholders;

		mCallback = std::make_shared<gvt_callback>(
			std::bind(&CollisionGroup::shapeChangeCallback, this, _1)
		);
	}
}
