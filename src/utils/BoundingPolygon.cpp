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
#include <stdexcept>
#include <unordered_set>

#include "BoundingPolygon.hpp"


namespace gvt {
	using float_type = BoundingPolygon::float_type;
	using Vertex = gvt::BoundingPolygon::Vertex;

	std::vector<Vector<float_type>> BoundingPolygon::normalAxes() const {
		Vector<float_type> diff;

		// How many normal axes does a "polygon" hold? If it is a line, just
		// one, which we can compute quickly.
		if (mVertices.size() == 2) {
            diff = mVertices[1] - mVertices[0];
            diff.normalize();
            diff.rotate(M_PI / -2.0);

            return {diff};
		} else {
			std::vector<Vector<float_type>> axes(mVertices.size());
			size_t i = 1;

			// Add the normal axes, from the first to the second to last
			while (i < mVertices.size()) {
				diff = mVertices[i] - mVertices[i - 1];
				axes[i - 1] = Vector<float_type>(diff.angle() - M_PI / 2.0);

				i++;
			}

			// Add last axis
			diff = mVertices[0] - mVertices[i - 1];
			axes[i - 1] = Vector<float_type>(diff.angle() - M_PI / 2.0);

			return axes;
		}
	}

	AxialProjection BoundingPolygon::projectAlong(Vector<float_type> axis)
	const {
		// The algorithm works by expanding the extremes of the projection as
		// the vertices are explored
		float_type tempProj = (mPosition + mVertices[0]).projectAlong(axis);
		AxialProjection p {tempProj, tempProj};

		for (size_t i = 1; i < mVertices.size(); i++) {
			tempProj = (mPosition + mVertices[i]).projectAlong(axis);

			p.start = std::min<float_type>(p.start, tempProj);
			p.end = std::max<float_type>(p.end, tempProj);
		}

		return p;
	}

	BoundingPolygon::BoundingPolygon(std::initializer_list<Vertex> vertices) {
		if (vertices.size() < 2)
			throw std::domain_error(
				"Unable to instantiate a BoundingPolygon with fewer than 2 vertices"
			);

		mVertices.assign(vertices);
	}

	BoundingPolygon::BoundingPolygon (unsigned vertices) {
		mVertices.resize(vertices);
	}

	void BoundingPolygon::rotate(float_type rad) {
		for (auto &v: mVertices)
			v.rotate(rad);
	}

	void BoundingPolygon::rotate(float_type rad, Vertex center) {
		for (auto &v: mVertices)
			v.rotate(rad, center);
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

	Vertex& BoundingPolygon::operator[] (unsigned i) {
		return mVertices[i];
	}

	std::vector<Vertex> BoundingPolygon::vertices () const {
		return mVertices;
	}

	unsigned BoundingPolygon::size() const {
		return mVertices.size();
	}

	BoundingPolygon::Vertex BoundingPolygon::center () const {
		auto center = mVertices[0];

		for (size_t i = 1; i < mVertices.size(); i++)
            center += mVertices[i];

		center = center / static_cast<float_type>(mVertices.size());

		return center;
	}

	BoundingPolygon BoundingPolygon::triangle (
			Vectord first, Vectord second, Vectord third
	) {
		return BoundingPolygon{first, second, third};
	}

	BoundingPolygon BoundingPolygon::rectangle (
			Vectord topLeft, Vectord bottomRight
	) {
		return BoundingPolygon{
			topLeft, {bottomRight.x, topLeft.y}, bottomRight,
			{topLeft.x, bottomRight.y}
		};
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
