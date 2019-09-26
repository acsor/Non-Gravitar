#ifndef NON_GRAVITAR_SHAPEVISITOR_HPP
#define NON_GRAVITAR_SHAPEVISITOR_HPP


namespace gvt {
	class Bunker;
	class Circle;
	class Fuel;
	class Planet;
	class Polyline;
	class Rectangle;
	class RoundMissile;
	class ClosedShape;
	class Spaceship;
	class SpawnArea;
	class TractorBeam;

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
			virtual void visitPlanet(Planet &planet) {};
			virtual void visitPolyline(Polyline &polyline) {};
			virtual void visitRectangle(Rectangle &rectangle) {};
			virtual void visitRoundMissile(RoundMissile &missile) {};
			virtual void visitClosedShape(ClosedShape &shape) {};
			virtual void visitSpaceship(Spaceship &spaceship) {};
			virtual void visitSpawnArea(SpawnArea &area) {};
			virtual void visitTractorBeam(TractorBeam &beam) {};
	};
}


#endif
