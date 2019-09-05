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
#include <functional>
#include "ShapeGroupView.hpp"
#include "view/SpaceshipView.hpp"

using namespace std::placeholders;


namespace gvt {
	void ShapeGroupView::onShapeChanged (shared_ptr<Event> e) {
		auto event = std::dynamic_pointer_cast<ShapeGroupEvent>(e);

		if (event) {
			if (event->type == ShapeGroupEvent::Type::attached) {
				mViews[event->shape] = shared_ptr<ShapeView>(
						mFactory.makeView(event->shape)
				);
			} else if (event->type == ShapeGroupEvent::Type::detached) {
				mViews.erase(event->shape);
			} else if (event->type == ShapeGroupEvent::Type::destroyed) {
				mViews.clear();
				mGroup.reset();
			}
		}
	}

	void ShapeGroupView::onCreateDebugView() {
	}

	void ShapeGroupView::onUpdateDebugColor () {
        for (auto &mView: mViews)
        	mView.second->onUpdateDebugColor();
	}

	ShapeGroupView::ShapeGroupView(const shared_ptr<ShapeGroup> &group):
			mGroup{group} {
		for (auto const &shape: *group)
			mViews[shape] = shared_ptr<ShapeView>(mFactory.makeView(shape));

		mCallback = group->addCallback(
			std::bind(&ShapeGroupView::onShapeChanged, this, _1)
		);
	}

	ShapeGroupView::~ShapeGroupView() {
		mGroup->removeCallback(mCallback);
	}

	void ShapeGroupView::setDebug(bool state) {
		DebuggableView::setDebug(state);

		for (auto &mView: mViews)
			mView.second->setDebug(state);
	}

	void ShapeGroupView::draw(
			sf::RenderTarget &target, sf::RenderStates state
	) const {
		for (auto &view: mViews)
			view.second->draw(target, state);
	}
}
