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
#ifndef NON_GRAVITAR_SPAWN_AREA_HPP
#define NON_GRAVITAR_SPAWN_AREA_HPP

#include "CRPolygon.hpp"


namespace gvt {
	/**
	 * @c SpawnArea represents an area in the game (typically in a solar
	 * system) where the spaceship can be regenerated after a loss.
	 */
	class SpawnArea: public CRPolygon {
		public:
			explicit SpawnArea(Vectord position, double radius);

			/**
			 * Aligns @c shape within this SpawnArea, in such a way as to
			 * (possibly) wrap it entirely.
			 */
			void centerShape(Shape &shape) const;
			void centerShape(shared_ptr<Shape> shape) const;
			void accept(ShapeVisitor &v) override;
	};

}


#endif