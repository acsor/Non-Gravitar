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
#ifndef NON_GRAVITAR_SHAPE_BUNDLE_HPP
#define NON_GRAVITAR_SHAPE_BUNDLE_HPP

#include <list>
#include <memory>
#include "Shape.hpp"
#include "../Event.hpp"

template<typename T> using shared_ptr = std::shared_ptr<T>;


namespace gvt {
	class Shape;

	class ShapeBundle: public EventListener, public EventDispatcher {
		protected:
			std::list<shared_ptr<Shape>> mObjects;

			ShapeBundle();
		public:
			using iterator = std::list<shared_ptr<Shape>>::iterator;

			static const Event SHAPE_ATTACHED;
			static const Event SHAPE_DETACHED;
			static const Event DESTROIED;

			virtual ~ShapeBundle();
			void insert(shared_ptr<Shape> shape);

			inline iterator begin();
			inline iterator end();
	};
}


// Implementation of inline functions
gvt::ShapeBundle::iterator gvt::ShapeBundle::begin() {
	return mObjects.begin();
}

gvt::ShapeBundle::iterator gvt::ShapeBundle::end() {
	return mObjects.end();
}


#endif
