#include <unordered_set>
#include "catch.hpp"
#include "../src/Entities.hpp"

using namespace std;
using namespace gvt;


TEST_CASE("gvt::Line", "[Entities][Line]") {
	Line l{1, 2, 4};

	l = l * 4;
	REQUIRE(l.width() == 16);
}


TEST_CASE("Rectangle::clashes()", "[Entities][Rectangle]") {
	Rectangle const center{-1, 2, 2, 4};
	unordered_set<Rectangle> const colliding = unordered_set<Rectangle> {
		// Left extreme and left very near
		{-3, 2, 2, 4}, {-2.9, 2, 2, 4},
		// Top extreme and top very near
		{-1, 6, 2, 4}, {-1, 5.9, 2, 4},
		// Right extreme and bottom very near
		{1, 2, 2, 4}, {0.9, 2, 2, 4},
		// Bottom extreme and bottom very near
		{-1, -2, 2, 4}, {-1, -1.9, 2, 4}
	};
	unordered_set<Rectangle> const nonColliding = unordered_set<Rectangle> {
		// From left in clockwise direction
		{-3.2, 2, 2, 4}, {-1, 6.2, 2, 4}, {1.005, 2, 2, 4}, {-1, -2.005, 2, 4}
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
