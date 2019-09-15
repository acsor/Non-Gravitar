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
#ifndef NON_GRAVITAR_SCENE_HPP
#define NON_GRAVITAR_SCENE_HPP

#include <memory>
#include <typeindex>
#include <SFML/Graphics.hpp>
#include "shape-group/ShapeGroup.hpp"
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
		protected:
			static const constexpr double BUNKER_SCORE = 50;

			Game *mGame;

			Vectord mSize;
			shared_ptr<ShapeGroup> mShapes;
			shared_ptr<ShapeGroupView> mShapesView;

			gvt::ALGraph<std::type_index> mDestroyGraph;
			std::shared_ptr<gvt_callback> mDestroyCallback, mCollisionCallback;

			Scene(Vectord size, shared_ptr<ShapeGroup> shapes);
			~Scene() override;

			/**
			 * Initializes the "destroy graph". This graph instance is a graph
			 * containing type objects as its vertices, and edges such that,
			 * if (u, v) is contained in it, then an object of type u
			 * clashing with an object of type v destroys the latter.
			 */
			void initializeDestroyGraph();
			void onCollisionOccurred (shared_ptr<gvt::Event> const &e);
			void onShapeDestroyed (shared_ptr<gvt::Event> const &e);
		public:
			friend class Game;
			
			/**
			 * @param seconds Seconds elapsed since the last scene computation
			 */
			virtual void onUpdateGame (double seconds);
			void draw (sf::RenderTarget &t, sf::RenderStates s) const override;

			inline shared_ptr<ShapeGroup> shapes();
			inline Vectord size() const;
	};
}


namespace gvt {
	shared_ptr<ShapeGroup> Scene::shapes() {
		return mShapes;
	}

	Vectord Scene::size() const {
		return mSize;
	}
}


#endif