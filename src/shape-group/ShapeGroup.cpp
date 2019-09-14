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
#include <algorithm>
#include <utility>
#include "ShapeGroup.hpp"


namespace gvt {
	ShapeGroup::~ShapeGroup() {
		notify(std::make_shared<ShapeGroupEvent>(
				ShapeGroupEvent::Type::destroyed, this, nullptr
		));
	}

	void ShapeGroup::insert(shared_ptr<Shape> shape) {
		// Not checking for null-pointer arguments is intended behavior, as code
		// feeding in null-pointer values should not exist in the first place: a
		// segmentation fault acts as a proper signaling mechanism
		mShapes.push_front(shape);
		onInsertShape(shape);

		notify(std::make_shared<ShapeGroupEvent>(
			ShapeGroupEvent::Type::attached, this, shape
		));
	}

	void ShapeGroup::remove(shared_ptr<Shape> shape) {
		auto toRemove = std::find(mShapes.begin(), mShapes.end(), shape);

		if (toRemove != mShapes.end()) {
			onRemoveShape(*toRemove);
			mShapes.erase(toRemove);

			notify(std::make_shared<ShapeGroupEvent>(
					ShapeGroupEvent::Type::detached, this, *toRemove
			));
		}
	}

	 void ShapeGroup::removeIf(
	 	std::function<bool (shared_ptr<Shape>)> predicate
	 ) {
	 	for (auto i = mShapes.begin(); i != mShapes.end(); i++) {
	 		if (predicate(*i)) {
	 			auto e = std::make_shared<ShapeGroupEvent>(
						ShapeGroupEvent::Type::detached, this, *i
				);

	 			onRemoveShape(*i);
	 			i = mShapes.erase(i);

	 			notify(e);
	 		}
	 	}
	 }
}
