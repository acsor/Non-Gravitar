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
	template<typename T> Vector<T>::Vector(): Vector(0, 0) {
	}

	template<typename T> Vector<T>::Vector(T x, T y) {
		this->x = x;
		this->y = y;
	}

	template<typename T> Vector<T>::Vector(T r) {
		x = cos(r);
		y = sin(r);
	}

	template<typename T> void Vector<T>::normalize() {
		float length = norm();

		if (length != 0) {
			x /= length;
			y /= length;
		}
	}

	template<typename T> void Vector<T>::rotate(float rad) {
		auto n = norm();
		auto theta = angle();

		x = n * cos(theta + rad);
		y = n * sin(theta + rad);
	}

	template<typename T> void Vector<T>::rotate(float rad, Vector center) {
		// partial represents the `(v - c)' vector rotated by `rad' radians
		// around the center
		Vector<T> partial = (*this - center);

		partial.rotate(rad);

		x = partial.x + center.x;
		y = partial.y + center.y;
	}

	template<typename T> double Vector<T>::norm() const {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	template<typename T> double Vector<T>::angle() const {
		return (y >= 0) ? acos(x / norm()): M_PI + acos(-x / norm());
	}

	template<typename T> Vector<T> Vector<T>::operator* (
			double l
			) const {
		return Vector(l * x, l * y);
	}

	template<typename T> Vector<T> Vector<T>::operator+ (Vector<T> const &o)
	const {
		return {x + o.x, y + o.y};
	}

	template<typename T> Vector<T> Vector<T>::operator- (Vector const &o) const
	{
		return {x - o.x, y - o.y};
	}

	template<typename T> Vector<T>& Vector<T>::operator+= (Vector<T> const &o)
	{
		x += o.x;
		y += o.y;

		return *this;
	}

	template<typename T> bool Vector<T>::operator==(Vector const &o) const {
		return x == o.x && y == o.y;
	}

	template<typename T> bool Vector<T>::operator!=(Vector const &o) const {
		return x != o.x || y != o.y;
	}
}
