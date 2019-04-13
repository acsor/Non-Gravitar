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
#include <algorithm>
#include <cstdlib>

#include "BoundingPolygon.hpp"


namespace gvt {
	using float_type = BoundingPolygon::float_type;

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

	AxialProjection BoundingPolygon::projectAlong(Vector<float_type> axis)
	const {
		auto vs = vertices();
		float_type tempProj = vs[0].get().projectAlong(axis);
		AxialProjection p {tempProj, tempProj};

		for (size_t i = 1; i < vs.size(); i++) {
			tempProj = vs[i].get().projectAlong(axis);
			p.start = std::min<float_type>(p.start, tempProj);
			p.end = std::max<float_type>(p.start, tempProj);
		}

		return p;
	}

	bool BoundingPolygon::intersects(BoundingPolygon const &o) const {
		return false;
	}


	bool AxialProjection::intersects(AxialProjection const &o) const {
		return o.start <= end && start <= o.end;
	}
}
