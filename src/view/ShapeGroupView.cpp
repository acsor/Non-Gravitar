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


namespace gvt {
	void ShapeGroupView::onShapeInserted (shared_ptr<ShapeInsertionEvent> e) {
		mViews[e->shape] = shared_ptr<ShapeView>(mFactory(e->shape));
	}

	void ShapeGroupView::onShapeRemoved (shared_ptr<ShapeRemovalEvent> e) {
		mViews.erase(e->shape);
	}

	void ShapeGroupView::onShapeGroupDestroyed (
			shared_ptr<ShapeGroupDestructionEvent> e
	) {
		mViews.clear();
		mGroup.reset();
	}

	void ShapeGroupView::onCreateDebugView() {
	}

	void ShapeGroupView::onUpdateDebugColor () {
        for (auto &mView: mViews)
        	mView.second->onUpdateDebugColor();
	}

	ShapeGroupView::ShapeGroupView(const shared_ptr<ShapeGroup> &group):
			mGroup{group} {
		auto _1 = std::placeholders::_1;

		mAttachCbk = group->insertionDispatcher().addCallback(
				std::bind(&ShapeGroupView::onShapeInserted, this, _1)
		);
		mRemovalCbk = group->removalDispatcher().addCallback(
				std::bind(&ShapeGroupView::onShapeRemoved, this, _1)
		);
		mDestrCbk = group->destructionDispatcher().addCallback(
			std::bind(&ShapeGroupView::onShapeGroupDestroyed, this, _1)
		);

		for (auto const &shape: *group)
			mViews[shape] = shared_ptr<ShapeView>(mFactory(shape));
	}

	ShapeGroupView::~ShapeGroupView() {
		mGroup->insertionDispatcher().removeCallback(mAttachCbk);
		mGroup->removalDispatcher().removeCallback(mRemovalCbk);
		mGroup->destructionDispatcher().removeCallback(mDestrCbk);
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
