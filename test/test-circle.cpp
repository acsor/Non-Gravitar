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
#include "catch.hpp"
#include "cmath"
#include "shape/Circle.hpp"

using Circle = gvt::Circle;


TEST_CASE("Circle::clashes(Circle&)", "[Circle]") {
	Circle main{{0, 0}, 1};
	Circle clashing[] = {
		{{-.5, 0}, 1}, {{0, .5}, 1}, {{.5, 0}, 1}, {{0, -.5}, 1},
		{{-1, 0}, 1}, {{0, 1}, 1}, {{1, 0}, 1}, {{0, -1}, 1},
		{{-2, 0}, 1}, {{0, 2}, 1}, {{2, 0}, 1}, {{0, -2}, 1},
	};
	Circle nonClashing[] = {
		{{-5.5, 0}, 1}, {{-5, .5}, 1}, {{-4.5, 0}, 1}, {{-5, -.5}, 1}
	};
	size_t const clashingNo = sizeof(clashing) / sizeof(Circle),
		   nonClashingNo = sizeof(nonClashing) / sizeof(Circle);

	SECTION("Testing with origin == (0, 0)") {
		for (size_t i = 0; i < clashingNo; i++)
			REQUIRE(main.clashes(clashing[i]));

		for (size_t i = 0; i < nonClashingNo; i++)
			REQUIRE(!main.clashes(nonClashing[i]));
	}
}

TEST_CASE("Circle::area()", "[Circle]") {
	float const radius = 4;
	Circle c{{1, 1}, radius};

	REQUIRE(abs(c.area() - M_PI * (pow(radius, 2))) <= 0.001);
}
