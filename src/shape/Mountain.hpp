#ifndef NON_GRAVITAR_MOUNTAIN_HPP
#define NON_GRAVITAR_MOUNTAIN_HPP

#include "Shape.hpp"
#include "ShapeVisitor.hpp"
#include "Vector.hpp"


namespace gvt {
	class Mountain: public Shape {
		private:
			Vectorf mLeft, mTop, mRight;
		public:
			Mountain(Vectorf left, Vectorf top, Vectorf right);

			void accept (ShapeVisitor &visitor) override;
	};
}


#endif
