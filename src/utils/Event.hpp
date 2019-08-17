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
#ifndef NON_GRAVITAR_EVENT_LISTENER
#define NON_GRAVITAR_EVENT_LISTENER

#include <functional>
#include <list>
#include <memory>

template<typename T> using shared_ptr = std::shared_ptr<T>;


namespace gvt {
    struct Event {
    	protected:
    		Event() = default;
    	public:
			virtual ~Event() = default;
    };

	template<typename E> using callback = std::function<void (shared_ptr<E>)>;
	using gvt_callback = callback<Event>;

	/**
	 * Class transmitting events to registered objects. Such events will be 
	 * handled by "callbacks", which can be functions, function objects, 
	 * lambdas and more (e.g. std::bind() expressions).
	 * 
	 * The template parameter @c E is there for permitting multiple event 
	 * hierarchies to operate with this (and related) classes.
	 * 
	 * @tparam E Event type to be transmitted.
	 */
	template<typename E> class EventDispatcher {
		public:
			virtual ~EventDispatcher();

			void addCallback(shared_ptr<callback<E>> c);
			/**
			 * Stores @c c as a callback to be invoked during a call to @c
			 * notify().
			 * @param c Callback to store
			 * @return A pointer to the stored data so that the
			 * callback can be removed at a later time.
			 */
			shared_ptr<callback<E>> addCallback(callback<E> c);
			/**
			 * Removes a callback, wrapped by a @c shared_ptr<callback<E>>
			 * usually returned by @c addCallback().
			 * @param c Callback to remove from this dispatcher.
			 */
			void removeCallback(shared_ptr<callback<E>> c);
			/**
			 * Notify registered callbacks the rising of @c event.
			 */
			void notify(shared_ptr<E> event);

			size_t callbacks() const;
		private:
			std::list<shared_ptr<callback<E>>> mCallbacks;
	};

	using gvt_callback = callback<gvt::Event>;
	using GVTEventDispatcher = EventDispatcher<gvt::Event>;
}


#include "Event.tpp"


#endif
