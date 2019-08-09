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
#include "utils/Vector.hpp"

using Vectord = gvt::Vectord;
template <typename T> using Vector = gvt::Vector<T>;


TEST_CASE("gvt::Vector::Vector(float)", "[Vector]") {
	double degrees;

	for (unsigned i = 0; i < 360; i++) {
		degrees = Vectord(i).norm();

		REQUIRE(abs(degrees - 1.0) <= 0.01);
	}
}

TEST_CASE("gvt::Vector::normalize()", "[Vector]") {
	Vectord v, u;
	std::set<std::pair<float, float>> inputs = {
		{4, 5}, {10, 9}, {1, 1}, {0, 1}, {-10, 4}, {4, -10}
	};

	for (auto i = inputs.cbegin(); i != inputs.cend(); i++) {
		v = Vectord(i->first, i->second);
		u = v;
		u.normalize();

		REQUIRE(abs(v.angle() - u.angle()) < 0.001);
	}
}

TEST_CASE("gvt::Vector::angle()", "[Vector]") {
	Vectord const inputs[] = {
			{0, 0},
			// First quarter
			{sqrtf(3) / 2.0, 0.5}, {sqrtf(2) / 2.0, sqrtf(2) / 2.0},
			{0.5, sqrtf(3) / 2.0}, {0, 1},
			// Second quarter
			{-0.5, sqrtf(3) / 2.0}, {-sqrtf(2) / 2.0, sqrtf(2) / 2.0},
			{-sqrtf(3) / 2.0, 0.5}, {-1, 0},
			// Third quarter
			{-sqrtf(3) / 2.0, -0.5}, {-sqrtf(2) / 2.0, -sqrtf(2) / 2.0},
			{-0.5, -sqrtf(3) / 2.0}, {0, -1},
			// Fourth quarter
			{0.5, -sqrtf(3) / 2.0}, {sqrtf(2) / 2.0, -sqrtf(2) / 2.0},
			{sqrtf(3) / 2.0, -0.5}, {1, 0}
	};
	float const expOutputs[] = {
			0,
			// First quarter
			M_PI / 6.0, M_PI / 4.0, M_PI / 3.0, M_PI / 2.0,
			// Second quarter
			2.0 * M_PI / 3.0, 3.0 * M_PI / 4.0, 5.0 * M_PI / 6.0, M_PI,
			// Third quarter
            M_PI + M_PI / 6.0, M_PI + M_PI / 4.0, M_PI + M_PI / 3.0,
            M_PI + M_PI / 2.0,
			// Fourth quarter
			5.0 * M_PI / 3.0, 7.0 * M_PI / 4.0, 11.0 * M_PI / 6.0, 0
	};
	size_t const n = sizeof(expOutputs) / sizeof(float);

	for (size_t i = 0; i < n; i++) {
		INFO(
			"[" << i << "] Expecting " << expOutputs[i] << ", got " <<
			inputs[i].angle()
		);
		REQUIRE(abs(inputs[i].angle() - expOutputs[i]) < 0.0001);
	}
}

TEST_CASE("gvt::Vector::rotate()", "[Vector]") {
	Vectord v{1, 0}, temp;
	float radians[] = {
		// Main coordinates
		0, M_PI / 2, M_PI, 1.5 * M_PI, 2 * M_PI,
		// Handpicked coordinates to ensure correctness
		M_PI / 6, M_PI / 4, M_PI / 3
	};
	Vectord expected[] = {
		v, {0, 1}, {-1, 0}, {0, -1}, v,
		{sqrt(3) / 2.0, 0.5}, {sqrt(2) / 2.0, sqrt(2) / 2.0},
		{0.5, sqrt(3) / 2.0}
	};
	size_t const n = sizeof(radians) / sizeof(float);

	for (size_t i = 0; i < n; i++) {
		temp = v;
		temp.rotate(radians[i]);

		INFO(
			"[" << i << "] " << "Expected {" << expected[i].x << ", " <<
			expected[i].y << "}, got {" << temp.x << ", " << temp.y << "}"
		);
		REQUIRE(abs(temp.x - expected[i].x) <= 0.0001);
		REQUIRE(abs(temp.y - expected[i].y) <= 0.0001);
	}
}

TEST_CASE("gvt::Vector::distance()", "[Vector]") {
	REQUIRE(Vectord{4, 0}.distance(Vectord{10, 0}) == 6);
}

TEST_CASE("gvt::Vector::operator==", "[Vector]") {
	Vector<double> a{1, 2}, b{1.0, 2.0}, c{4.59, 49};

	REQUIRE(a == b);
	REQUIRE(a != c);
	REQUIRE(b != c);
}
