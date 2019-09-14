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
#include <utility>
#include "Scene.hpp"


namespace gvt {
	Scene::Scene(Vectord size, shared_ptr<ShapeGroup> shapes):
			mSize{size}, mShapes{std::move(shapes)} {
		mShapesView.reset(new ShapeGroupView(mShapes));
	}

	void Scene::onUpdateGame (double seconds) {
		// Remove outlived shapes
		mShapes->removeIf(
				[] (shared_ptr<Shape> const &s) -> bool { return s->destroyed (); }
		);
		auto shapesCopy = std::vector<shared_ptr<Shape>>(
				mShapes->begin(), mShapes->end()
		);

		// TODO Is there another more performing way of safely iterating
		//  through the list without making a copy of it?
		for (auto &shape: shapesCopy) {
			shape->velocity(
					shape->velocity() + seconds * shape->acceleration()
			);
			shape->position(
					shape->position() + seconds * shape->velocity()
			);
		}
	}

	void Scene::draw (sf::RenderTarget &t, sf::RenderStates s) const {
		t.draw(*mShapesView, s);
	}
}
