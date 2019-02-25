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


template<typename T> gvt::Vector<T>::Vector(): Vector(0, 0) {
}

template<typename T> gvt::Vector<T>::Vector(T x, T y) {
	this->x = x;
	this->y = y;
}

template<typename T> gvt::Vector<T>::Vector(T degrees) {
	x = cos(degrees);
	y = sin(degrees);
}

template<typename T> void gvt::Vector<T>::normalize() {
	float length = norm();

	if (length != 0) {
		x /= length;
		y /= length;
	}
}

template<typename T> double gvt::Vector<T>::norm() const {
	return sqrt(pow(x, 2) + pow(y, 2));
}

template<typename T> double gvt::Vector<T>::degrees() const {
	return acos(x / norm());
}

template<typename T> gvt::Vector<T> gvt::Vector<T>::operator+ (
	gvt::Vector<T> const &o
) const {
	gvt::Vector<T> out = *this;

	out.x += o.x;
	out.y += o.y;
	out.normalize();
	
	return out;
}

template<typename T> gvt::Vector<T>& gvt::Vector<T>::operator+= (
	gvt::Vector<T> const &o
) {
	x += o.x;
	y += o.y;
	normalize();

	return *this;
}
