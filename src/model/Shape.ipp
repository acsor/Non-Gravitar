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
#include <cmath>
#include "Shape.hpp"


namespace gvt {
	ShapeEvent::ShapeEvent():
			ShapeEvent::ShapeEvent(ShapeEvent::Type::unspecified, nullptr) {
	}

	ShapeEvent::ShapeEvent(ShapeEvent::Type type, Shape *shape) {
		this->type = type;
		this->shape = shape;
	}


	void Shape::x(float xcoord) {
		ShapeEvent e {ShapeEvent::Type::moved, this};

		mX = xcoord;
		notify(&e);
	}

	void Shape::y(float ycoord) {
		ShapeEvent e {ShapeEvent::Type::moved, this};

		mY = ycoord;
		notify(&e);
	}

	float Shape::x() const {
		return mX;
	}

	float Shape::y() const {
		return mY;
	}

	float Shape::originX() const {
		return mOriginX;
	}

	float Shape::originY() const {
		return mOriginY;
	}

	float Shape::rotation() const {
		return mRotation;
	}

	void Shape::rotation(float r) {
		ShapeEvent e {ShapeEvent::Type::rotated, this};

		// TO-DO Shorten, if at all possible, this code that I have produced, which
		// at first sight looks orribly bigger than it ought to be
		if (r >= 0)
			mRotation = r - (2.0 * M_PI) * floor(r / (2.0 * M_PI));
		else
			mRotation = r - (2.0 * M_PI) * ceil(r / (2.0 * M_PI));

		notify(&e);
	}

	void Shape::rotate(float r) {
		rotation(mRotation + r);
	}
}
