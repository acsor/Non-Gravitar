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
#include <cmath>
#include <list>
#include "catch.hpp"
#include "model/Point.hpp"
#include "Vector.hpp"

using Point = gvt::Point;
template<typename T> using list = std::list<T>;
using Trajectory = gvt::Trajectory;


TEST_CASE("Shape::moveAlong()", "[Shape][Point]") {
	Point p{0, 0};
	list<Point> expected{
		{1, 0}, {sqrt(2) / 2.0, sqrt(2) / 2.0}, {0, 1},
		{-sqrt(2) / 2.0, sqrt(2) / 2.0}, {-1, 0},
		{-sqrt(2) / 2.0, -sqrt(2) / 2.0}, {0, -1},
		{sqrt(2) / 2.0, -sqrt(2) / 2.0}, {1, 0}
	};
	list<Trajectory> ts = {
		0, M_PI / 4.0, M_PI / 2.0, M_PI * 3.0 / 4.0, M_PI, M_PI * 5.0 / 4.0,
		M_PI * 3.0 / 2.0, M_PI * 7.0 / 4.0, 2 * M_PI
	};

	auto t = ts.cbegin();

	for (auto e = expected.cbegin(); e != expected.cend(); e++, t++) {
		p.moveAlong(*t);

		INFO(
			"Expected (" << e->x() << ", " << e->y() << "), got (" << p.x() <<
			", " << p.y() << ")"
		);
		REQUIRE(abs(p.x() - e->x()) <= 1E-6);
		REQUIRE(abs(p.y() - e->y()) <= 1E-6);

		p = {0, 0};
	}
}

TEST_CASE("gvt::Point::operator==", "[Point]") {
	Point p{1, 2}, q{1, 2};

	REQUIRE(p == q);
}

TEST_CASE("gvt::Point::operator+", "[Point]") {
	Point p{1, 2}, q{1, 2};

	REQUIRE(p + q == Point{2, 4});
}

TEST_CASE("gvt::Point::operator-", "[Point]") {
	Point p{1, 2}, q{1, 2};

	REQUIRE(p - q == Point{0, 0});
}

TEST_CASE("gvt::Point::operator*", "[Point]") {
	Point p{1, 2};

	REQUIRE(4 * p == Point{4, 8});
}

TEST_CASE("gvt::Point::distance()", "[Point]") {
	Point p{1, 1}, q{2, 1};

	REQUIRE(p.distance(q) == 1);
}
