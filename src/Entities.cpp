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
#include "Entities.hpp"
#include "Utils.hpp"


// TO-DO Watch out against such generalized using-declarations.
using namespace gvt;
// TO-DO Is this use of `using' caveat-free?
using string = std::string;


void Plane::updateCollisions() {

}


PlaneObject::PlaneObject(float x, float y): mX{x}, mY{y} {
}

bool PlaneObject::clashes(PlaneObject const &o) const {
    return collisionBox().clashes(o.collisionBox());
}

void PlaneObject::move(float xcoord, float ycoord) {
    mX += xcoord;
    mY += ycoord;

    if (mPlane != nullptr)
        mPlane->updateCollisions();
}


WidthTrait::WidthTrait(float width) {
    this->width(width);
}

float WidthTrait::width() const {
	return mWidth;
}

void WidthTrait::width(float w) {
	if (w <= 0)
		throw std::domain_error("the width value is supposed to be > 0");

	mWidth = w;
}

}

float HeightTrait::height() const {
	return mHeight;
}

void HeightTrait::height(float h) {
	if (h <= 0)
		throw std::domain_error("the height value is supposed to be > 0");

	mHeight = h;
}


Rectangle::Rectangle(float x, float y, float width, float height):
	PlaneObject(x, y), WidthTrait(width), HeightTrait(height) {
}

Rectangle Rectangle::collisionBox() const {
	return *this;
}

bool Rectangle::clashes(Rectangle const &o) const {
	return IN_CLOSED_INTERVAL(mX - o.mX, -mWidth, o.mWidth) &&
			IN_CLOSED_INTERVAL(mY - o.mY, -mHeight, o.mHeight);
}

bool Rectangle::operator==(PlaneObject const &o) const {
	auto *other = dynamic_cast<Rectangle const *>(&o);

	if (other) {
		return mX == other->mX && mY == other->mY && mWidth == other->mWidth &&
				mHeight == other->mHeight;
	}

	return false;
}


size_t std::hash<Rectangle>::operator()(Rectangle const &r) const {
	auto h = hash<float>{};

	return h(r.mX) ^ h(r.mY) ^ h(r.mWidth) ^ h(r.mHeight);
}

bool std::equal_to<Rectangle>::operator()(
	Rectangle const &r1, Rectangle const &r2
) const {
	return r1 == r2;
}

std::ostream& std::operator<< (std::ostream &out, Rectangle const &r) {
	// TO-DO Learn and eventually tweak the output conversion of your types.
	// Also learn to use manipulators
	out << "{" << r.mX << ", " << r.mY << ", " << r.mWidth << ", " <<
		r.mHeight << "}";

	return out;
}
