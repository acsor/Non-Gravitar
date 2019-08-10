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
#include "Shape2DView.hpp"
#include "shape/Rectangle.hpp"
#include "utils/Utils.hpp"


namespace gvt {
	void Shape2DView::updateTransforms() {
		if (auto shape = mShape.lock()) {
			auto pos = shape->position();
			auto center = shape->center();

			mTranslation = sf::Transform::Identity;
			mRotation = sf::Transform::Identity;

			mTranslation.translate(pos.x, pos.y);
			mRotation.rotate(gvt::rad2deg(shape->rotation()), center.x,
							 center.y);
		}
	}

	void Shape2DView::updateDebugBounds() {
		auto shape = mShape.lock();

		if (mDebug && shape != nullptr) {
			// Reallocating mBounds each time is not efficient, but this
			// computation is only performed when mDebug == true, so this is not
			// a real concern
			vector<BoundingPolygon::Vertex>
					vertices = shape->collisionPolygon().vertices();
			mBounds = sf::VertexArray(sf::Quads, vertices.size() + 1);
			size_t i = 0;

			for (i = 0; i < vertices.size(); i++) {
				mBounds[i] = sf::Vector2f(vertices[i].x, vertices[i].y);
				mBounds[i].color = sf::Color::Green;
			}

			mBounds[i] = sf::Vector2f(vertices[0].x, vertices[0].y);
			mBounds[i].color = sf::Color::Green;
		}
	}

	Shape2DView::Shape2DView(shared_ptr<Shape2D> const &shape):
			Debuggable(false), mShape{shape} {
		updateTransforms();

		shape->addHandler(*this);
	}

	void Shape2DView::onMoved() {
		if (!mShape.expired()) {
			updateTransforms();
			updateDebugBounds();
		}
	}

	void Shape2DView::onRotated() {
		if (!mShape.expired()) {
			updateTransforms();
			updateDebugBounds();
		}
	}

	void Shape2DView::onDestroyed() {
		mBounds.clear();
	}

	Shape2DView::~Shape2DView() {
		if (auto p = mShape.lock())
			p->removeHandler(*this);
	}

	void Shape2DView::debug(bool debug) {
		Debuggable::debug(debug);
		updateDebugBounds();
	}

	void Shape2DView::draw(RenderTarget &target, RenderStates s) const {
		if (mDebug && !mShape.expired())
			target.draw(mBounds);
	}

	void Shape2DView::handle(Event *e) {
		auto event = dynamic_cast<ShapeEvent *>(e);

		if (event) {
			switch (event->type) {
				case (ShapeEvent::Type::moved):
					onMoved();
					break;
				case (ShapeEvent::Type::rotated):
					onRotated();
					break;
				case (ShapeEvent::Type::destroyed):
					onDestroyed();
					mShape.reset();
					event->shape->removeHandler(*this);
					break;
				default:
					break;
			}
		}
	}
}
