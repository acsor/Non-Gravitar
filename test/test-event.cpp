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
#include "../src/Event.hpp"
#include "catch.hpp"

using Event = gvt::Event;
using EventDispatcher = gvt::EventDispatcher;
using EventListener = gvt::EventListener;


class SimpleDispatcher: public EventDispatcher {
	public:
		static const Event EVENT_A;
		static const Event EVENT_B;
};

class SimpleListener: public EventListener {
	public:
		size_t eventA{0}, eventB{0};

		void handle(Event e) override {
			if (e == SimpleDispatcher::EVENT_A)
				eventA++;
			else if (e == SimpleDispatcher::EVENT_B)
				eventB++;
		}
};


const Event SimpleDispatcher::EVENT_A = Event::create();
const Event SimpleDispatcher::EVENT_B = Event::create();


TEST_CASE("EventListener::handle(), EventDispatcher::notify()", "[Event]") {
	SimpleDispatcher s;
	SimpleListener l;
	size_t repeatA = 43, repeatB = 55;

	s.attachListener(l);

	for (size_t i = 0; i < repeatA; i++)
		s.notify(SimpleDispatcher::EVENT_A);

	for (size_t i = 0; i < repeatB; i++)
		s.notify(SimpleDispatcher::EVENT_B);

	REQUIRE(l.eventA == repeatA);
	REQUIRE(l.eventB == repeatB);

	s.detachListener(l);
}

TEST_CASE("Event::operator==", "[Event]") {
	auto ids = Event::ID_COUNTER;
	Event a = Event::create(), b = Event::create();
	Event c{a}, d = a;

	REQUIRE(a == c);
	REQUIRE(a == d);
	REQUIRE(a != b);
	REQUIRE(c != b);
	REQUIRE(d != b);

	REQUIRE(Event::ID_COUNTER - ids == 2);
}
