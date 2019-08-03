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
#include "shape/Shape.hpp"
#include "utils/Event.hpp"

template<typename T> using shared_ptr = std::shared_ptr<T>;


namespace gvt {
	class Shape;
	class ShapeBundle;

	// TODO Convert to lambda function
	class DestroyedListener: public GVTEventHandler {
        private:
	        ShapeBundle &mBundle;
        public:
			DestroyedListener(ShapeBundle &bundle);
	        void handle (Event *e) override;
	};

	class ShapeBundle: public GVTEventDispatcher {
	    friend class DestroyedListener;

        private:
            DestroyedListener mListener{*this};
        protected:
            std::list<shared_ptr<Shape>> mShapes;

            ShapeBundle() = default;
		public:
			using iterator = std::list<shared_ptr<Shape>>::iterator;

			virtual ~ShapeBundle();
			virtual void insert(shared_ptr<Shape> shape);

			inline iterator begin();
			inline iterator end();
	};

    struct ShapeBundleEvent: public Event {
        enum class Type {
            unspecified = 0, attached, detached, destroyed
        };

        Type type{Type::unspecified};
        ShapeBundle *bundle{nullptr};
        shared_ptr<Shape> shape;

        ShapeBundleEvent() = default;
        inline ShapeBundleEvent(
                Type type, ShapeBundle *bundle, shared_ptr<Shape> shape
        );
    };
}


// Implementation of inline functions
namespace gvt {
	ShapeBundle::iterator ShapeBundle::begin() {
		return mShapes.begin();
	}

	ShapeBundle::iterator ShapeBundle::end() {
		return mShapes.end();
	}

	ShapeBundleEvent::ShapeBundleEvent(
		ShapeBundleEvent::Type t, ShapeBundle *b, shared_ptr<Shape> s
	): type{t}, bundle{b}, shape{s} {
	}
}


#endif
