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

#include <memory>
#include <unordered_map>
#include <shape/Spaceship.hpp>

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

					notify(std::make_shared<CollisionEvent>(*first, *second));
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
		using namespace std::placeholders;

		mCallback = std::make_shared<gvt_callback>(
			std::bind(&CollisionGroup::shapeChangeCallback, this, _1)
		);
	}


	CollisionEvent::CollisionEvent(
			shared_ptr<Shape> _first, shared_ptr<Shape> _second
	): first{std::move(_first)}, second{std::move(_second)} {
	}
}
