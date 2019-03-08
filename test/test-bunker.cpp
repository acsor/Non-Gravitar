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
#include "../src/model/RoundMissile.hpp"
#include "../src/model/Bunker.hpp"

using Bunker = gvt::Bunker;
using RoundMissile = gvt::RoundMissile;


TEST_CASE("Bunker::shoot() missiles have to be cyclic", "[Bunker]") {
	Bunker b = gvt::Bunker3D(0, 0);
	RoundMissile m1 = b.shoot(), m2 = b.shoot(), m3 = b.shoot();

	REQUIRE(m1 == b.shoot());
	REQUIRE(m2 == b.shoot());
	REQUIRE(m3 == b.shoot());
}

TEST_CASE(
	"Bunker::shoot() missiles have to be oriented within 90 deg. of the"
	"shooting Bunker", "[Bunker]"
) {
	Bunker b = gvt::Bunker3D(0, 0);
	size_t const samples = 300;
	RoundMissile m{0, 0};

	for (size_t i = 0; i < samples; i++) {
		m = b.shoot();

		INFO(
			"m.velocity() = " << "{" << m.velocity().x << ", " <<
			m.velocity().y << "}"
		);
		INFO("degrees = " << m.velocity().degrees());
		REQUIRE(b.rotation() - M_PI / 2.0 <= m.velocity().degrees());
		REQUIRE(m.velocity().degrees() <= b.rotation() + M_PI / 2.0);

		b = gvt::Bunker3D(0, 0);
	}
}
