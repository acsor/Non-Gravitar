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
#include <unordered_set>
#include "catch.hpp"
#include "model/Rectangle.hpp"

using namespace std;
using namespace gvt;


TEST_CASE("Rectangle::clashes()", "[Rectangle]") {
	Rectangle const center{{-1, 2}, {1, 6}};
	unordered_set<Rectangle> const colliding = unordered_set<Rectangle> {
		// Left extreme and left very near
		{{-3, 2}, {-1, 6}}, {{-2.9, 2}, {-0.9, 6}},
		// Top extreme and top very near
		{{-1, 6}, {1, 10}}, {{-1, 5.9}, {1, 9.9}},
		// Right extreme and bottom very near
		{{1, 2}, {3, 6}}, {{0.9, 2}, {2.9, 6}},
		// Bottom extreme and bottom very near
		{{-1, -2}, {1, 2}}, {{-1, -1.9}, {1, 2.1}}
	};
	unordered_set<Rectangle> const nonColliding = unordered_set<Rectangle> {
		// From left in clockwise direction
		{{-3.2, 2}, {-1.2, 6}}, {{-1, 6.2}, {1, 10.1}},
		{{1.005, 2}, {3.005, 6}}, {{-1, -2.005}, {1, 1.995}}
	};

	REQUIRE(center.clashes(center));

	for (auto i = colliding.begin(); i != colliding.end(); i++) {
		INFO("Center " << center << " should clash with " << *i);
		REQUIRE(center.clashes(*i));
	}

	for (auto i = nonColliding.begin(); i != nonColliding.end(); i++) {
		INFO("Center " << center << " should not clash with " << *i);
		REQUIRE(!center.clashes(*i));
	}
}
