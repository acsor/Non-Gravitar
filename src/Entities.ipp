#include <stdexcept>


void gvt::PlaneObject::x(float xcoord) {
    mX = xcoord;

    if (mPlane != nullptr)
        mPlane->updateCollisions();
}

void gvt::PlaneObject::y(float ycoord) {
    mY = ycoord;

    if (mPlane != nullptr)
        mPlane->updateCollisions();
}

float gvt::PlaneObject::x() const {
    return mX;
}

float gvt::PlaneObject::y() const {
    return mY;
}


float gvt::WidthTrait::width() const {
	return mWidth;
}

void gvt::WidthTrait::width(float w) {
	if (w <= 0)
		throw std::domain_error("the width value is supposed to be > 0");

	mWidth = w;
}


float gvt::HeightTrait::height() const {
	return mHeight;
}

void gvt::HeightTrait::height(float h) {
	if (h <= 0)
		throw std::domain_error("the height value is supposed to be > 0");

	mHeight = h;
}
