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
#include <set>
#include <utility>
#include "catch.hpp"
#include "../src/Vector.hpp"

template <typename T> using Vector = gvt::Vector<T>;


TEST_CASE("gvt::Vector::Vector(float)", "[Vector]") {
	double degrees;

	for (unsigned i = 0; i < 360; i++) {
		degrees = Vector<float>(i).norm();

		REQUIRE(abs(degrees - 1.0) <= 0.01);
	}
}

TEST_CASE("gvt::Vector::normalize()", "[Vector]") {
	Vector<float> v, u;
	std::set<std::pair<float, float>> inputs = {
		{4, 5}, {10, 9}, {1, 1}, {0, 1}, {-10, 4}, {4, -10}
	};

	for (auto i = inputs.cbegin(); i != inputs.cend(); i++) {
		v = Vector<float>(i->first, i->second);
		u = v;
		u.normalize();

		REQUIRE(abs(v.degrees() - u.degrees()) <= 0.001);
	}
}
