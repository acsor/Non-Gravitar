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
#include "ShapeBundle.hpp"

using Event = gvt::Event;
using ShapeBundle = gvt::ShapeBundle;
using ShapeBundleEvent = gvt::ShapeBundleEvent;
using Shape = gvt::Shape;


ShapeBundle::~ShapeBundle() {
	ShapeBundleEvent e{ShapeBundleEvent::Type::destroied, this, nullptr};

	notify(&e);
}

void ShapeBundle::insert(shared_ptr<Shape> shape) {
	ShapeBundleEvent e{ShapeBundleEvent::Type::attached, this, shape};
	// Not checking for null-pointer arguments is intended behavior, as code
	// feeding in null-pointer values should not exist in the first place: a
	// segmentation fault acts as a proper signaling mechanism
	mObjects.push_front(shape);
	shape->attachListener(*this);

	notify(&e);
}
