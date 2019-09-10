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
#ifndef NON_GRAVITAR_COLLISION_GROUP_HPP
#define NON_GRAVITAR_COLLISION_GROUP_HPP

#include <memory>
#include "ShapeGroup.hpp"
#include "utils/Event.hpp"


namespace gvt {
	class CollisionGroup;

	/**
	 * A subclass of @c ShapeGroup handling collision between objects.
	 */
	class CollisionGroup: public ShapeGroup {
        private:
			shared_ptr<gvt_callback> mCallback;

			void shapeChangeCallback (shared_ptr<Event> e);
			void updateCollisions();
		protected:
			void onInsertShape (shared_ptr<Shape> shape) override;
			void onRemoveShape (shared_ptr<Shape> shape) override;
		public:
			CollisionGroup();
	};

	struct CollisionEvent: public Event {
		shared_ptr<Shape> first, second;

		CollisionEvent(shared_ptr<Shape> _first, shared_ptr<Shape> _second);
	};
}


#endif
