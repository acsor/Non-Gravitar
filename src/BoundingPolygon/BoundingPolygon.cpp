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
#include <cstdlib>
#include "BoundingPolygon.hpp"

template<typename T> using Vector = gvt::Vector<T>;

using BoundingPolygon = gvt::BoundingPolygon;
using float_type = gvt::BoundingPolygon::float_type;
using Vertex = gvt::BoundingPolygon::Vertex;


std::vector<Vector<float_type>> BoundingPolygon::normalAxes() const {
	auto vs = vertices();
	Vector<float_type> diff;
	std::vector<Vector<float_type>> axes(vs.size());

	for (size_t i = 1; i < vs.size(); i++) {
		diff = vs[i].get() - vs[i - 1].get();
		axes[i - 1] = Vector<float_type>(diff.angle() - M_PI / 2.0);
	}

	return axes;
}

void BoundingPolygon::shift(Vector<float_type> translation) {
	for (Vector<float_type>& v: vertices()) {
		v += translation;
	}
}

void BoundingPolygon::rotate(float deg) {
	for (Vector<float_type>& v: vertices()) {
		v.rotate(deg);
	}
}

void BoundingPolygon::rotate(float deg, Vertex center) {
	for (Vertex& v: vertices()) {
		v.rotate(deg, center);
	}
}
