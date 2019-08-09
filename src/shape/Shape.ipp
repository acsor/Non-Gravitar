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


namespace gvt {
	ShapeEvent::ShapeEvent():
			ShapeEvent::ShapeEvent(ShapeEvent::Type::unspecified, nullptr) {
	}

	ShapeEvent::ShapeEvent(ShapeEvent::Type type, Shape *shape) {
		this->type = type;
		this->shape = shape;
	}

	Vectord Shape::position() const {
		return mPosition;
	}

	Vectord Shape::center() const {
		return mPosition + Vectord{width(), height()};
	}

	Vectord Shape::velocity() const {
		return mVelocity;
	}

	double Shape::speed() const {
		return mVelocity.norm();
	}

	void Shape::acceleration(const Vectord &a) {
		mAccel = a;
	}

	Vectord Shape::acceleration() const {
		return mAccel;
	}

	double Shape::rotation() const {
		return mRotation;
	}

	void Shape::rotate(double r) {
		rotation(mRotation + r);
	}

	bool Shape::destroyed() const {
		return mDestroyed;
	}

	void Shape::destroyed(bool state) {
		mDestroyed = state;
	}
}
