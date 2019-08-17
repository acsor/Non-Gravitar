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
template<typename T> using weak_ptr = std::weak_ptr<T>;


namespace gvt {
	class ShapeGroup: public GVTEventDispatcher {
        protected:
            std::list<shared_ptr<Shape>> mShapes;

            /**
             * Defined by @c ShapeGroup subclasses to define additional
             * actions to be performed when adding a @c Shape.
             */
            virtual void onInsertShape (shared_ptr<Shape> shape) {};
			/**
			 * Like @c onInsertShape, but when removing a @c Shape.
			 */
			virtual void onRemoveShape (shared_ptr<Shape> shape) {};

            ShapeGroup() = default;
		public:
			using iterator = std::list<shared_ptr<Shape>>::iterator;

			virtual ~ShapeGroup();
			void insert(shared_ptr<Shape> shape);
			void remove(shared_ptr<Shape> shape);
			inline size_t size () const;

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
        inline ShapeGroupEvent(Type t, ShapeGroup *g, shared_ptr<Shape> s);
    };
}


// Implementation of inline functions
namespace gvt {
	size_t ShapeGroup::size() const {
        return mShapes.size();
	}

	ShapeGroup::iterator ShapeGroup::begin() {
		return mShapes.begin();
	}

	ShapeGroup::iterator ShapeGroup::end() {
		return mShapes.end();
	}

	ShapeGroupEvent::ShapeGroupEvent(
		ShapeGroupEvent::Type t, ShapeGroup *g, shared_ptr<Shape> s
	): type{t}, group{g}, shape{s} {
	}
}


#endif
