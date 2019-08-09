#include "Mountain.hpp"


gvt::Mountain::Mountain(Vectorf left, Vectorf top, Vectorf right):
		Shape(gvt::Vectord()) {
    mLeft = left;
	mTop = top;
    mRight = right;
}

void gvt::Mountain::accept (ShapeVisitor &visitor) {
	visitor.visitMountain(*this);
}
