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
#ifndef NON_GRAVITAR_SHAPE_GROUP_HPP
#define NON_GRAVITAR_SHAPE_GROUP_HPP

#include <list>
#include <memory>
#include "shape/Shape.hpp"
#include "utils/Event.hpp"

template<typename T> using shared_ptr = std::shared_ptr<T>;


namespace gvt {
	class Shape;
	class ShapeGroup;

	// TODO Convert to lambda function
	class DestroyedListener: public GVTEventHandler {
        private:
	        ShapeGroup &mGroup;
        public:
			DestroyedListener(ShapeGroup &group);
	        void handle (Event *e) override;
	};

	class ShapeGroup: public GVTEventDispatcher {
	    friend class DestroyedListener;

        private:
            DestroyedListener mListener{*this};
        protected:
            std::list<shared_ptr<Shape>> mShapes;

            ShapeGroup() = default;
		public:
			using iterator = std::list<shared_ptr<Shape>>::iterator;

			virtual ~ShapeGroup();
			virtual void insert(shared_ptr<Shape> shape);

			inline iterator begin();
			inline iterator end();
	};

    struct ShapeGroupEvent: public Event {
        enum class Type {
            unspecified = 0, attached, detached, destroyed
        };

        Type type{Type::unspecified};
        ShapeGroup *group{nullptr};
        shared_ptr<Shape> shape;

        ShapeGroupEvent() = default;
        inline ShapeGroupEvent(
                Type type, ShapeGroup *group, shared_ptr<Shape> shape
        );
    };
}


// Implementation of inline functions
namespace gvt {
	ShapeGroup::iterator ShapeGroup::begin() {
		return mShapes.begin();
	}

	ShapeGroup::iterator ShapeGroup::end() {
		return mShapes.end();
	}

	ShapeGroupEvent::ShapeGroupEvent(
		ShapeGroupEvent::Type t, ShapeGroup *b, shared_ptr<Shape> s
	): type{t}, group{b}, shape{s} {
	}
}


#endif
