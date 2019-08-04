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
#include "ShapeBundleView.hpp"

#include <stdexcept>
#include "../view/SpaceshipView.hpp"
#include "../view/BunkerView.hpp"

using ShapeBundleEvent = gvt::ShapeBundleEvent;
using ShapeBundleView = gvt::ShapeBundleView;


ShapeBundleView::ShapeBundleView(shared_ptr<ShapeBundle> bundle, bool debug):
	Debuggable(debug), mFactory{debug}, mBundle{bundle} {
	bundle->addHandler(*this);
}

ShapeBundleView::~ShapeBundleView() {
	if (auto p = mBundle.lock())
		p->removeHandler(*this);
}

void ShapeBundleView::debug(bool state) {
	Debuggable::debug(state);

	for (auto i = mViews.begin(); i != mViews.end(); i++) {
		i->second->debug(state);
	}
}

void ShapeBundleView::draw(
	sf::RenderTarget &target, sf::RenderStates state
) const {
	for (auto i = mViews.begin(); i != mViews.end(); i++) {
		i->second->draw(target, state);
	}
}

void ShapeBundleView::handle(Event *e) {
	auto event = dynamic_cast<ShapeBundleEvent*>(e);

	if (event) {
		if (event->type == ShapeBundleEvent::Type::attached) {
			mViews[event->shape.get()] = shared_ptr<ShapeView>(
				mFactory.makeView(event->shape)
			);
		} else if (event->type == ShapeBundleEvent::Type::detached) {
			mViews.erase(event->shape.get());
		} else if (event->type == ShapeBundleEvent::Type::destroyed) {
			mViews.clear();
			mBundle.reset();
		}
	}
}
