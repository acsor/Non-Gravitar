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
#include "../utils.hpp"
#include <catch2/catch.hpp>

using namespace gravit;


/**
 * @brief Simple `Observer' implementation incrementing a counter at each new
 * notification.
 */
class CounterObserver: public Observer {
	private:
		unsigned int c {0};
	public:
		void onChange(Observable const *o) override {
			c++;
		}
		unsigned int count() {
			return c;
		}
};


TEST_CASE("CounterObserver", "[Observer][Observable]") {
	Observable s;
	CounterObserver o;
	const size_t times = 1E3;

	s.attach(&o);
	for (size_t i = 0; i < times; i++)
		s.notify();
	REQUIRE(o.count() == times);

	s.detach(&o);
	for (size_t i = 0; i < times; i++)
		s.notify();
	// We detached `o' from `s' and expect to receive no more notifications
	// from it.
	REQUIRE(o.count() == times);
}
