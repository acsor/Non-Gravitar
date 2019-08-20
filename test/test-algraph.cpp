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
#include "utils/ALGraph.hpp"


TEST_CASE(
		"ALGraph::insertVertex, removeVertex and containsVertex", "[ALGraph]"
) {
    gvt::ALGraph<void> graph;

	REQUIRE(graph.insertVertex(0) == true);
	REQUIRE(graph.containsVertex(0) == true);
	REQUIRE(graph.insertVertex(0) == false);

    REQUIRE(graph.removeVertex(0) == true);
	REQUIRE(graph.containsVertex(0) == false);
	REQUIRE(graph.removeVertex(0) == false);
}

TEST_CASE(
	"ALGraph::insertEdge, removeEdge and containsEdge", "[ALGraph]"
) {
	gvt::ALGraph<void> graph;

	graph.insertVertex(0);
	graph.insertVertex(1);

	REQUIRE(graph.insertEdge(0, 1) == true);
	REQUIRE(graph.containsEdge(0, 1) == true);
	REQUIRE(graph.insertEdge(0, 1) == false);

	REQUIRE(graph.removeEdge(0, 1) == true);
	REQUIRE(graph.containsEdge(0, 1) == false);
	REQUIRE(graph.removeEdge(0, 1) == false);
}

TEST_CASE("ALGraph::adjacents", "[ALGraph]") {
	gvt::ALGraph<void> graph;
	std::list<gvt::Vertex<void>> expected;

    for (unsigned i = 0; i < 9; i++)
    	graph.insertVertex(i);

    for (unsigned i = 1; i < 9; i++) {
    	graph.insertEdge(0, i);
    	expected.emplace_back(i);
    }

    REQUIRE(graph.adjacents(0) == expected);
}

TEST_CASE("ALGraph::vertices", "[ALGraph]") {
	gvt::ALGraph<void> graph;
	std::list<gvt::Vertex<void>> expected;

	for (unsigned i = 0; i < 49; i++) {
		graph.insertVertex(i);
		expected.emplace_back(i);
	}

	REQUIRE(graph.vertices() == expected);
}
