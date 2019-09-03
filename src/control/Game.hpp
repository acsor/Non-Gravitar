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
#ifndef NON_GRAVITAR_GAME_HPP
#define NON_GRAVITAR_GAME_HPP

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "shape-group/ShapeGroup.hpp"
#include "shape/Spaceship.hpp"
#include "view/ShapeGroupView.hpp"


namespace gvt {
	/**
	 * TODO Document
	 */
	class Game: public sf::Drawable {
		private:
			// TODO Might turn mShip into a singleton instance, through
			//  SpaceshipHandle, for example
			shared_ptr<Spaceship> mShip;
			shared_ptr<Scene> mCurrScene;
			std::stack<shared_ptr<Scene>> mSceneStack;

			sf::View mSceneView;
			sf::Clock mClock;
			shared_ptr<EventDispatcher<sf::Event>> mViewEvents;
		protected:
			/**
			 * Centers the scene view around the spaceship as a move event
			 * arises from it.
			 */
			void centerSceneView (std::shared_ptr<gvt::Event> e);
			/**
			 * Resizes the scene view as a resize event from the window arises.
			 */
			void resizeSceneView (std::shared_ptr<sf::Event> const &e);
			void toggleDebug (std::shared_ptr<sf::Event> const &e);
		public:
			Game();
			~Game() override;

			void updateGameLoop ();

			/**
			 * Pushes a scene into the game, making it the active one.
			 */
			void pushScene (shared_ptr<Scene> scene);
			/**
			 * Eliminates and returns the top-most scene from the stack.
			 * @return The @c Scene object which was being shown prior to this
			 * call.
			 */
			shared_ptr<Scene> popScene ();
			shared_ptr<Spaceship> spaceship() const;

			shared_ptr<EventDispatcher<sf::Event>> viewEventsDispatcher() const;
			void handleViewEvent (shared_ptr<sf::Event> event);

			/**
			 * Renders the scene at the top of the stack.
			 */
			void draw(
				sf::RenderTarget &target, sf::RenderStates states
			) const override;
	};

	/**
	 * Moves the given @c Spaceship instance as key events from the view
	 * library arise.
	 */
	class MoveShipCallback {
		private:
			double mAngleStep, mAccelStep;
			shared_ptr<Spaceship> mShip;
		public:
			MoveShipCallback (
				shared_ptr<Spaceship> ship, double accel, double angle
			);

			void operator() (shared_ptr<sf::Event> e);
	};
}


#endif