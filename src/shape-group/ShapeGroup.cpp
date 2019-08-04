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
#include "ShapeGroup.hpp"

using Event = gvt::Event;
using ShapeGroup = gvt::ShapeGroup;
using ShapeGroupEvent = gvt::ShapeGroupEvent;
using Shape = gvt::Shape;


gvt::DestroyedListener::DestroyedListener(ShapeGroup &group):
	mGroup{group} {
}

void gvt::DestroyedListener::handle (Event *e) {
    auto groupEvent = dynamic_cast<ShapeGroupEvent *>(e);

    if (groupEvent) {
        switch (groupEvent->type) {
            case (ShapeGroupEvent::Type::destroyed):
                mGroup.mShapes.remove(groupEvent->shape);
                break;
            default:
                break;
        }
    }
}


ShapeGroup::~ShapeGroup() {
	ShapeGroupEvent e{ShapeGroupEvent::Type::destroyed, this, nullptr};

	notify(&e);
}

void ShapeGroup::insert(shared_ptr<Shape> shape) {
	ShapeGroupEvent e{ShapeGroupEvent::Type::attached, this, shape};
	// Not checking for null-pointer arguments is intended behavior, as code
	// feeding in null-pointer values should not exist in the first place: a
	// segmentation fault acts as a proper signaling mechanism
	mShapes.push_front(shape);
	shape->addHandler(mListener);

	notify(&e);
}
