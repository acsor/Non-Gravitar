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
//
#include "MountainView.hpp"


namespace gvt {
	// TODO Improve color
	const sf::Color MountainView::sColor = sf::Color::Yellow;

	void MountainView::updatePosition() {
		std::shared_ptr<Mountain> shape = std::dynamic_pointer_cast<Mountain>(
			mShape.lock()
		);

		if (shape) {
			mVertices[0] = {
					sf::Vector2f(shape->left().x, shape->left().y), sColor
			};
			mVertices[1] = {
					sf::Vector2f(shape->top().x, shape->top().y), sColor
			};
			mVertices[2] = {
					sf::Vector2f(shape->right().x, shape->right().y), sColor
			};
			mVertices[3] = {
					sf::Vector2f(shape->left().x, shape->left().y), sColor
			};
		}
	}

	MountainView::MountainView(shared_ptr<Mountain> const &m): ShapeView(m) {
        mVertices = sf::VertexArray(sf::LineStrip, 4);

		updatePosition();
	}

	void MountainView::onMoved() {
		updatePosition();
	}

	void MountainView::draw(RenderTarget &target, RenderStates state) const {
		ShapeView::draw(target, state);

		if (!mShape.expired())
            target.draw(mVertices, mRotation);
	}
}
