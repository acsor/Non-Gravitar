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
#include "catch.hpp"
#include "shape/RoundMissile.hpp"
#include "shape/Bunker.hpp"

using Bunker = gvt::Bunker;
using RoundMissile = gvt::RoundMissile;


TEST_CASE("Bunker::shoot() missiles have to be cyclic", "[Bunker]") {
	auto b = gvt::Bunker({0, 0}, 3);
	auto m1 = b.shoot(0, 0, 0), m2 = b.shoot(0, 0, 0), m3 = b.shoot(0, 0, 0);

	REQUIRE(*m1 == *b.shoot(0, 0, 0));
	REQUIRE(*m2 == *b.shoot(0, 0, 0));
	REQUIRE(*m3 == *b.shoot(0, 0, 0));
}

TEST_CASE(
	"Bunker::shoot() missiles velocity must have norm equal to 1", "[Bunker]"
) {
	size_t const samples = 100;

	for (size_t i = 0; i < samples; i++) {
		auto b = gvt::Bunker({0, 0}, 3);

		REQUIRE(b.shoot(0, 0, 0)->velocity().norm() == 1.0);
	}
}

TEST_CASE(
	"Bunker::shoot() missiles have to be oriented within 180 and 360 deg. of "
	"the shooting Bunker", "[Bunker]"
) {
	size_t samples = 300;

	while (samples-- > 0) {
		auto b = gvt::Bunker({0, 0}, 3);
		auto m = b.shoot(0, 0, 0);

		// If we fix the rotation at 0, we need only test that the velocity
		// angle is comprised in the [180, 360) range
		b.rotation(0);

		INFO(
			"m.velocity() = " << "{" << m->velocity().x << ", " <<
			m->velocity().y << "}"
		);
		INFO("angle = " << m->velocity().angle());
		REQUIRE(M_PI <= m->velocity().angle());
		REQUIRE(m->velocity().angle() < 2 * M_PI);
	}
}
