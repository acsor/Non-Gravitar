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
#include <exception>
#include <list>
#include <string>
#include "catch.hpp"
#include "../src/Utils.hpp"

template<typename T> using list = std::list<T>;
using string = std::string;


TEST_CASE("gvt::dirpath()", "[Utils]") {
	list<string> inputs = {
		"/", "/a/b/c/d", "/a/b/c/d/", "/alpha/beta", "/alpha/beta/gamma.theta",
		"/alpha", "alpha/", "a/b/c/d/"
	}, expOutputs = {
		"/", "/a/b/c/", "/a/b/c/d/", "/alpha/", "/alpha/beta/", "/", "alpha/",
		"a/b/c/d/"
	}, exceptions = {
		"", "a", "alpha",
	};
	auto j = expOutputs.cbegin();

	for (auto i = inputs.cbegin(); i != inputs.cend(); i++, j++) {
		REQUIRE(*j == gvt::dirpath(*i));
	}

	for (auto i = exceptions.cbegin(); i != exceptions.cend(); i++) {
		INFO("Expecting to raise with " + *i);
		REQUIRE_THROWS_AS(gvt::dirpath(*i), std::domain_error);
	}
}

// TEST_CASE("gvt::staticsGet()", "[Utils]") {
// 	list<string> inputs = {
// 		"graphics/spaceship.png", "sound/start.mp4"
// 	};
// 	string const basePath = gvt::dirpath(__FILE__) + "../" + GVT_STATICS_DIR;
// 
// 	for (auto i = inputs.cbegin(); i != inputs.cend(); i++) {
// 		REQUIRE(collapsePath(basePath + *i) == gvt::staticsGet(*i));
// 	}
// }
