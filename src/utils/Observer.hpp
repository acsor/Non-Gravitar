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
#ifndef NON_GRAVITAR_OBSERVER_HPP
#define NON_GRAVITAR_OBSERVER_HPP

#include <set>


namespace gvt {
	class Observer;

	/**
	 * @brief A Subject base class as defined in the Observer pattern of the
	 * GOF book <i>Design Patterns</i>. This popular framework is utilized to
	 * transmit a state change from an Observable class (formally termed
	 * Subject) * to one or multiple Observer classes, that can accordingly
	 * update their own * status. A common use of the Observer pattern is in
	 * the relationship between * model and view classes in the MVC pattern.
	 * @see <a href="https://en.wikipedia.org/wiki/Observer_pattern">Observer
	 * pattern<a/>, <a href="https://en.wikipedia.org/wiki/MVC_Pattern">MVC
	 * pattern<a/>
	 */
	class Observable {
		private:
			std::set<Observer*> watchers {};
			int toggleNotify {0};
		public:
			virtual ~Observable();

			/**
			 * @brief Attaches a new Observer instance to the queue of
			 * notifiable watchers.
			 */
			void virtual attach(Observer *o) final;
			/**
			 * @brief Removes a given Observer instance from the queue, if
			 * found.
			 */
			void virtual detach(Observer *o) final;
			/**
			 * @brief Notifies all the registered observer in the queue. Note
			 * that memory management is up to the user to the library, and
			 * that the Observable class is not liable for any dangling
			 * pointer.
			 */
			void virtual notify() const final;
			/**
			 * @brief Suspends notification to Observer instances. That is,
			 * upon * a call to Observable::notify(), if a call to
			 * Observable::pauseNotify() hasn't yet been matched by a call to
			 * Observable::resumeNotify(), none of the observers are notified.
			 * Calls can be nested.
			 * @throw std::logic_error if pauseNotify() was overused.
			 * @see Observable::resumeNotify()
			 */
			void pauseNotify();
			/**
			 * @breif Dual of Observable::pauseNotify(). Since the calls of
			 * these * two methods can nest and interleave, a single call to
			 * Observable::resumeNotify() doesn't undo all the previous ones to
			 * Observable::pauseNotify().
			 */
			void resumeNotify();
	};

	/**
	 * @brief Class receiving change updates from a linked Observer instance.
	 * @see <a href="https://en.wikipedia.org/wiki/Observer_pattern">Observer
	 * pattern<a/>
	 */
	class Observer {
		public:
			virtual ~Observer();
			/**
			 * @brief Called when an Observable instance to which the current
			 * Observer instance is bound fires a notification event.
			 * @param o Observable instance notying an internal change.
			 */
			void virtual onChange(Observable const *o) = 0;
	};
}


#endif
