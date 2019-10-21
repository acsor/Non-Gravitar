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
#include "ShapeGroupView.hpp"
#include "view/SpaceshipView.hpp"


namespace gvt {
	void ShapeGroupView::onShapeInserted (ShapeInsertionEvent e) {
		mViews[e.shape] = shared_ptr<ShapeView>(mFactory(e.shape));
	}

	void ShapeGroupView::onShapeRemoved (ShapeRemovalEvent e) {
		mViews.erase(e.shape);
	}

	void ShapeGroupView::onShapeGroupDestroyed (
			ShapeGroupDestructionEvent e
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
		mAttachCbk = group->insertionDispatcher().addCallback(
			[this] (ShapeInsertionEvent e) -> void { onShapeInserted (e); }
		);
		mRemovalCbk = group->removalDispatcher().addCallback(
			[this] (ShapeRemovalEvent e) -> void { onShapeRemoved(e); }
		);
		mDestrCbk = group->destructionDispatcher().addCallback(
			[this] (ShapeGroupDestructionEvent e) -> void { onShapeGroupDestroyed (e); }
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

	shared_ptr<ShapeView> ShapeGroupView::viewFor (shared_ptr<Shape> shape) {
		return mViews[shape];
	}

	void ShapeGroupView::draw(
			sf::RenderTarget &t, sf::RenderStates s
	) const {
		for (auto &view: mViews)
			view.second->draw(t, s);
	}
}
