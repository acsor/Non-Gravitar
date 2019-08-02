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
#ifndef NON_GRAVITAR_COLLISION_BUNDLE_HPP
#define NON_GRAVITAR_COLLISION_BUNDLE_HPP

#include "Event.hpp"
#include "ShapeBundle.hpp"
#include "shape/ShapeVisitor.hpp"


namespace gvt {
	class CollisionBundle;

	// TODO Replace by lambda
	class CollisionListener: public EventListener {
		private:
			CollisionBundle &mBundle;
		public:
			explicit CollisionListener(CollisionBundle &bundle);
			void handle (Event *e) override;
	};

	/**
	 * An implementation of @c ShapeVisitor taking action when two objects
	 * collide together. When such an event takes place, it is not always
	 * obvious what operation perform (e.g. a @c Missile colliding with a
	 * mountain, the @c Spaceship with another @c Missile etc.). @c
	 * CollisionVisitor is delegated this complex decision.
	 *
	 * TODO Improve documentation.
	 */
	class CollisionVisitor: public ShapeVisitor {
		private:
			CollisionBundle &mBundle;
		public:
			explicit CollisionVisitor(CollisionBundle &bundle);

			void visitSpaceship(Spaceship &spaceship) override;
			void visitBunker(Bunker &bunker) override;
			void visitMissile(RoundMissile &missile) override;
			void visitFuel(Fuel &fuel) override;
			void visitPoint(Point &point) override;
			void visitRectangle(Rectangle &rectangle) override;
			void visitLine(Line &line) override;
			void visitCircle(Circle &circle) override;
	};

	/**
	 * A subclass of @c ShapeBundle handling collision between objects.
	 */
	class CollisionBundle: public ShapeBundle {
		friend class CollisionListener;

        private:
			CollisionListener mCollisionListener{*this};
			CollisionVisitor mVisitor{*this};

			void updateCollisions();
		public:
			CollisionBundle() = default;
	};
}


#endif
