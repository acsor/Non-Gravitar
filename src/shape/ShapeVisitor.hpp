#ifndef NON_GRAVITAR_SHAPEVISITOR_HPP
#define NON_GRAVITAR_SHAPEVISITOR_HPP


namespace gvt {
	class Spaceship;
	class Point;
	class Rectangle;
	class Bunker;
	class RoundMissile;
	class Fuel;
	class Line;
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
			virtual void visitBunker(Bunker &bunker) {};
			virtual void visitCircle(Circle &circle) {};
			virtual void visitFuel(Fuel &fuel) {};
			virtual void visitLine(Line &line) {};
			virtual void visitMissile(RoundMissile &missile) {};
			virtual void visitMountain(Mountain &mountain) {};
			virtual void visitPoint(Point &point) {};
			virtual void visitRectangle(Rectangle &rectangle) {};
			virtual void visitSpaceship(Spaceship &spaceship) {};
	};
}




#endif
