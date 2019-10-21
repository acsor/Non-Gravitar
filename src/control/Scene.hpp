// MIT License
//
// Copyright (c) 2018 Oscar B.
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
#ifndef NON_GRAVITAR_SCENE_HPP
#define NON_GRAVITAR_SCENE_HPP

#include <memory>
#include <typeindex>
#include <SFML/Graphics.hpp>
#include "shape-group/ShapeGroup.hpp"
#include "shape-group/CollisionGroup.hpp"
#include "view/ShapeGroupView.hpp"
#include "utils/Event.hpp"
#include "utils/ALGraph.hpp"


namespace gvt {
	class Game;

	// TODO Try to see whether template specialization can yield cleaner code
	//  than subclassing
	class TypeVertex: public Vertex<std::type_index> {
		public:
			TypeVertex (std::type_index type);

			bool operator== (TypeVertex const &other) const;
	};

	/**
	 * A @c Scene represents the notion of contextual shapes to be rendered on
	 * screen. It encapsulates shape groups and manages their lifetimes,
	 * adding semantic and event-handling operations.
	 */
	class Scene: public sf::Drawable {
		private:
			ALGraph<std::type_index> mDestroyGraph;

			shared_ptr<Callback<ShapeRemovalEvent>> mDestroyCbk;
			shared_ptr<Callback<FuelEvent>> mFuelCbk;
			shared_ptr<Callback<PairCollisionEvent>> mCollisionCbk;
		protected:
			static const constexpr double BUNKER_SCORE = 50;

			Game *mGame;

			Vectord mSize;
			shared_ptr<CollisionGroup> mShapes;
			shared_ptr<ShapeGroupView> mShapesView;

			Scene(Vectord size, shared_ptr<CollisionGroup> shapes);
			~Scene() override;

			/**
			 * Initializes the "destroy graph". This graph instance is a graph
			 * containing type objects as its vertices, and edges such that,
			 * if (u, v) is contained in it, then an object of type u
			 * clashing with an object of type v destroys the latter.
			 */
			void initializeDestroyGraph();
			virtual void onCollision (PairCollisionEvent e);
			void onFuelChanged (FuelEvent e);

			/**
			 * Invoked when a shape is removed, but not yet (logically)
			 * destroyed from the shape group this scene is related to.
			 */
			void onShapeRemoved (ShapeRemovalEvent e);
			/**
			 * Invoked when @c shape is both removed and destroyed from the
			 * respective shape group of this scene.
			 */
			virtual void onShapeDestroyed (shared_ptr<Shape> shape);
			/**
			 * Called when the game spaceship exits the active scene boundaries.
			 */
			virtual void onExitBoundaries(shared_ptr<Spaceship> ship);

			void draw (sf::RenderTarget &t, sf::RenderStates s) const override;
		public:
			friend class Game;
			
			/**
			 * @param seconds Seconds elapsed since the last scene computation
			 */
			virtual void onUpdateGame (double seconds);

			/**
			 * @return @c true if this scene has a next scene, to be
			 * displayed after this one has completed.
			 */
			virtual bool hasNextScene() const = 0;
			/**
			 *
			 * @return the next scene after this one, to be displayed when it
			 * has completed.
			 */
			virtual shared_ptr<Scene> nextScene() = 0;

			/**
			 * @return The r/w @c ShapeGroup instance associated to this scene.
			 */
			inline shared_ptr<ShapeGroup> shapeGroup();
			inline Vectord size() const;
	};
}


namespace gvt {
	shared_ptr<ShapeGroup> Scene::shapeGroup() {
		return mShapes;
	}

	Vectord Scene::size() const {
		return mSize;
	}
}


#endif