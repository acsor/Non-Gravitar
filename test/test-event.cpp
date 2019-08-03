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
#include <iostream>
#include <stdexcept>
#include "utils/Event.hpp"
#include "catch.hpp"

using Event = gvt::Event;
using EventDispatcher = gvt::EventDispatcher;
using EventListener = gvt::EventHandler;


namespace gvt {
	class SimpleDispatcher: public EventDispatcher {
		public:
			SimpleDispatcher() = default;
	};

	struct SimpleEvent: public Event {
		enum class Type {unspecified = 0, a, b};

		SimpleEvent::Type type;

		SimpleEvent(SimpleEvent::Type type) {
			this->type = type;
		}
	};

	class SimpleListener: public EventHandler {
		public:
			unsigned eventA{0}, eventB{0};

			void handle(Event *e) override {
                auto event = dynamic_cast<SimpleEvent*>(e);

                if (event) {
					if (event->type == SimpleEvent::Type::a) {
						eventA++;
					} else if (event->type == SimpleEvent::Type::b) {
						eventB++;
					} else {
						throw std::domain_error(
							"Unrecognized type of SimpleEvent"
						);
					}
				}
			}
	};
};


TEST_CASE("EventHandler::handle(), EventDispatcher::notify()", "[Event]") {
	using SE = gvt::SimpleEvent;

	gvt::SimpleDispatcher s;
	gvt::SimpleListener l;
	SE a{SE::Type::a}, b{SE::Type::b};
	unsigned const repeatA = 43, repeatB = 55;

	s.addHandler(l);

	for (unsigned i = 0; i < repeatA; i++)
		s.notify(&a);

	for (unsigned i = 0; i < repeatB; i++)
		s.notify(&b);

	REQUIRE(l.eventA == repeatA);
	REQUIRE(l.eventB == repeatB);

	s.removeHandler(l);
}
