#ifndef NON_GRAVITAR_SHAPEVISITOR_HPP
#define NON_GRAVITAR_SHAPEVISITOR_HPP


namespace gvt {
	class Shape2D;
	class Spaceship;
	class Rectangle;
	class Bunker;
	class RoundMissile;
	class Fuel;
	class Circle;
	class Mountain;

	/**
	 * An implementation of the design pattern Visitor as described in the
	 * GOF book <i>Design patterns</i>, based on the object hierarchy @c Shape.
	 *
	 * @see https://en.wikipedia.org/wiki/Visitor_pattern
	 */
	class ShapeVisitor {
		protected:
			ShapeVisitor() = default;
		public:
			virtual void visitShape2D(Shape2D &shape) {};
			virtual void visitBunker(Bunker &bunker) {};
			virtual void visitCircle(Circle &circle) {};
			virtual void visitFuel(Fuel &fuel) {};
			virtual void visitMissile(RoundMissile &missile) {};
			virtual void visitMountain(Mountain &mountain) {};
			virtual void visitRectangle(Rectangle &rectangle) {};
			virtual void visitSpaceship(Spaceship &spaceship) {};
	};
}




#endif
