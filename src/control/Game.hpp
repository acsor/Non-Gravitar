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
#include <set>
#include <stack>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include "GameInfo.hpp"
#include "Scene.hpp"
#include "SceneFrame.hpp"
#include "SolarSystemSceneBuilder.hpp"
#include "shape/Spaceship.hpp"
#include "shape-group/ShapeGroup.hpp"
#include "view/GameInfoView.hpp"
#include "view/ShapeGroupView.hpp"


namespace gvt {
	/**
	 * Event issued when a new @c Scene is pushed/popped out of the game.
	 */
	struct SceneChangeEvent: public gvt::Event {
			shared_ptr<Scene> oldScene, newScene;

			SceneChangeEvent(
					shared_ptr<Scene> old, shared_ptr<Scene> _new
			);
	};

	/**
	 * A singleton class controlling the game and user logic. A @c Game
	 * instance will manage an unique instance of @c Spaceship, making it
	 * available for subsequent scenes via appropriate accessor functions.
	 */
	class Game: public sf::Drawable, public EventDispatcher<SceneChangeEvent> {
		private:
			static Game* sInstance;

			shared_ptr<GameInfo> mInfo;
			shared_ptr<GameInfoView> mInfoView;

			// By virtue of the fact that Game is a singleton instance, mShip
			// is too
			shared_ptr<Spaceship> mShip;

			shared_ptr<Scene> mCurrScene;
			std::stack<shared_ptr<Scene>> mSceneStack;
			shared_ptr<SceneFrame> mSceneFrame;

			sf::Clock mClock;
			EventDispatcher<sf::Event> mViewEvents;

			void onShipMoved(PositionEvent e);
			void toggleDebug(sf::Event e);

			Game();
		public:
			~Game() override;

			/**
			 * @return The singleton @c Game instance.
			 */
			static Game* getInstance();
			inline shared_ptr<GameInfo> gameInfo();

			/**
			 * @return The unique @c Spaceship instance, detaching it from
			 * the current scene and making it eventually available for
			 * another one.
			 */
			shared_ptr<Spaceship> acquireSpaceship();
			/**
			 * @return A pointer to the singleton spaceship instance.
			 */
			shared_ptr<Spaceship> spaceship();

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
			/**
			 * @return Thew @c Scene that should be currently displayed.
			 */
			inline shared_ptr<Scene> currentScene();

			EventDispatcher<sf::Event>& viewEventsDispatcher();

			/**
			 * Renders the scene at the top of the stack.
			 */
			void draw(
				sf::RenderTarget &target, sf::RenderStates states
			) const override;
	};
}


namespace gvt {
	shared_ptr<GameInfo> Game::gameInfo() {
		return mInfo;
	}

	shared_ptr<Scene> Game::currentScene() {
		return mCurrScene;
	}
}


#endif