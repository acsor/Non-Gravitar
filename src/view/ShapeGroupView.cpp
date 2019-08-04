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
#include "ShapeGroupView.hpp"

#include <stdexcept>
#include "../view/SpaceshipView.hpp"
#include "../view/BunkerView.hpp"

using ShapeGroupEvent = gvt::ShapeGroupEvent;
using ShapeGroupView = gvt::ShapeGroupView;


ShapeGroupView::ShapeGroupView(shared_ptr<ShapeGroup> group, bool debug):
	Debuggable(debug), mFactory{debug}, mGroup{group} {
	group->addHandler(*this);
}

ShapeGroupView::~ShapeGroupView() {
	if (auto p = mGroup.lock())
		p->removeHandler(*this);
}

void ShapeGroupView::debug(bool state) {
	Debuggable::debug(state);

	for (auto i = mViews.begin(); i != mViews.end(); i++) {
		i->second->debug(state);
	}
}

void ShapeGroupView::draw(
	sf::RenderTarget &target, sf::RenderStates state
) const {
	for (auto i = mViews.begin(); i != mViews.end(); i++) {
		i->second->draw(target, state);
	}
}

void ShapeGroupView::handle(Event *e) {
	auto event = dynamic_cast<ShapeGroupEvent*>(e);

	if (event) {
		if (event->type == ShapeGroupEvent::Type::attached) {
			mViews[event->shape.get()] = shared_ptr<ShapeView>(
				mFactory.makeView(event->shape)
			);
		} else if (event->type == ShapeGroupEvent::Type::detached) {
			mViews.erase(event->shape.get());
		} else if (event->type == ShapeGroupEvent::Type::destroyed) {
			mViews.clear();
			mGroup.reset();
		}
	}
}
