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
#include <utility>
#include "Polyline.hpp"
#include "Shape2D.hpp"


namespace gvt {
	void Polyline::accept (ShapeVisitor &visitor) {
		visitor.visitPolyline(*this);
	}

	bool Polyline::clashes (Shape2D const &other) const {
		auto polygon = other.collisionPolygon();

		for (size_t i = 0; i < mVertices.size() - 1; i++) {
			auto line = BoundingPolygon({mVertices[i], mVertices[i + 1]});
			line.shift(mPosition);

			if (line.intersects(polygon))
				return true;
		}

		return false;
	}

	bool Polyline::clashes (Polyline const &other) const {
		// TODO Test
		for (size_t i = 0; i < mVertices.size() - 1; i++) {
			auto const firstLine = BoundingPolygon(
					{mVertices[i], mVertices[i + 1]}
			);

			for (size_t j = 0; i < other.size() - 1; j++) {
				auto const secondLine = BoundingPolygon(
						{other.mVertices[j], other.mVertices[j + 1]}
				);

				if (firstLine.intersects(secondLine))
					return true;
			}
		}

		return false;
	}

	bool Polyline::clashes (Shape const &other) const {
		if (auto shape2d = dynamic_cast<Shape2D const *>(&other)) {
			return clashes(*shape2d);
		}  else if (auto polyline = dynamic_cast<Polyline const *>(&other)) {
			return clashes(*polyline);
		} else {
			throw std::domain_error(
				"Unrecognized type of shape to detect collisions with"
			);
		}
	}
}
