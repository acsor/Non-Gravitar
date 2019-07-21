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

	/**
	 * An implementation of the design pattern Visitor as described in the
	 * GOF book <i>Design patterns</i>, based on the object hierarchy @c Shape.
	 *
	 * @see https://en.wikipedia.org/wiki/Visitor_pattern
	 */
	class ShapeVisitor {
		public:
			virtual void visitSpaceship(Spaceship &spaceship) = 0;
			virtual void visitPoint(Point &point) = 0;
			virtual void visitRectangle(Rectangle &rectangle) = 0;
			virtual void visitBunker(Bunker &bunker) = 0;
			virtual void visitMissile(RoundMissile &missile) = 0;
			virtual void visitFuel(Fuel &fuel) = 0;
			virtual void visitLine(Line &line) = 0;
			virtual void visitCircle(Circle &circle) = 0;
	};
}




#endif
