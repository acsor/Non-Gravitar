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
#include <stdexcept>
#include <unordered_set>

#include "BoundingPolygon.hpp"


namespace gvt {
	using float_type = BoundingPolygon::float_type;

	std::vector<Vector<float_type>> BoundingPolygon::normalAxes() const {
		Vector<float_type> diff;
		std::vector<Vector<float_type>> axes(mVertices.size());

		for (size_t i = 1; i < mVertices.size(); i++) {
			diff = mVertices[i] - mVertices[i - 1];
			axes[i - 1] = Vector<float_type>(diff.angle() - M_PI / 2.0);
		}

		return axes;
	}

	BoundingPolygon::BoundingPolygon(std::initializer_list<Vertex> vertices) {
		if (vertices.size() < 3)
			throw std::domain_error(
				"No known 2D polygon has fewer than 3 vertices!"
			);

		mVertices.assign(vertices);
	}

	void BoundingPolygon::shift(Vector<float_type> translation) {
		for (Vector<float_type>& v: mVertices)
			v += translation;
	}

	void BoundingPolygon::rotate(float rad) {
		for (Vector<float_type>& v: mVertices)
			v.rotate(rad);
	}

	void BoundingPolygon::rotate(float rad, Vertex center) {
		for (Vertex& v: mVertices)
			v.rotate(rad, center);
	}

	AxialProjection BoundingPolygon::projectAlong(Vector<float_type> axis)
	const {
		float_type tempProj = mVertices[0].projectAlong(axis);
		AxialProjection p {tempProj, tempProj};

		for (size_t i = 1; i < mVertices.size(); i++) {
			tempProj = mVertices[i].projectAlong(axis);
			p.start = std::min<float_type>(p.start, tempProj);
			p.end = std::max<float_type>(p.start, tempProj);
		}

		return p;
	}

	bool BoundingPolygon::intersects(BoundingPolygon const &o) const {
		std::unordered_set<Vector<float_type>> axes;
		auto ax1 = normalAxes(), ax2 = o.normalAxes();

		axes.insert(ax1.begin(), ax1.end());
		axes.insert(ax2.begin(), ax2.end());

		for (auto axis: axes) {
			if (!projectAlong(axis).intersects(o.projectAlong(axis)))
				return false;
		}

		return true;
	}

	bool BoundingPolygon::operator== (BoundingPolygon const &o) const {
		return mVertices == o.mVertices;
	}

	bool BoundingPolygon::operator!= (BoundingPolygon const &o) const {
		return !operator==(o);
	}


	bool AxialProjection::intersects(AxialProjection const &o) const {
		return o.start <= end && start <= o.end;
	}
}
