// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#include <functional>
#include <stdexcept>
#include "utils/Event.hpp"
#include "catch.hpp"


namespace gvt {
	struct SimpleEvent: public Event {
		enum class Type {unspecified = 0, a, b};

		SimpleEvent::Type type;

		explicit SimpleEvent(SimpleEvent::Type type) {
			this->type = type;
		}
	};

	class SimpleCallback {
		public:
			unsigned eventA{0}, eventB{0};

			void operator() (SimpleEvent e) {
				if (e.type == SimpleEvent::Type::a) {
					eventA++;
				} else if (e.type == SimpleEvent::Type::b) {
					eventB++;
				} else {
					throw std::domain_error(
							"Unrecognized type of SimpleEvent"
					);
				}
			}
	};
}


TEST_CASE("EventHandler::handle(), EventDispatcher::raiseEvent()", "[Event]") {
	using SE = gvt::SimpleEvent;

	gvt::EventDispatcher<gvt::SimpleEvent> s;
    gvt::SimpleCallback l;
	unsigned const repeatA = 43, repeatB = 55;
    auto callback = s.addCallback(
		std::bind(&gvt::SimpleCallback::operator(), &l, std::placeholders::_1)
	);

	REQUIRE(s.callbacksCount() == 1);

	for (unsigned i = 0; i < repeatA; i++)
		s.raiseEvent(gvt::SimpleEvent(SE::Type::a));

	for (unsigned i = 0; i < repeatB; i++)
		s.raiseEvent(gvt::SimpleEvent(SE::Type::b));

	REQUIRE(l.eventA == repeatA);
	REQUIRE(l.eventB == repeatB);

	REQUIRE(s.callbacksCount() == 1);
	s.removeCallback(callback);
	REQUIRE(s.callbacksCount() == 0);
}
