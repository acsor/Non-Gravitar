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
#ifndef NON_GRAVITAR_SCENE_FRAME_HPP
#define NON_GRAVITAR_SCENE_FRAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "shape/Spaceship.hpp"
#include "utils/Event.hpp"
#include "utils/Vector.hpp"


namespace gvt {
	class Game;
	class SceneChangeEvent;

	/**
	 * Wrapper class responsible for managing the sf::View instance into
	 * which the current Game scene is shown, performing operations like
	 * resizing and recentering.
	 */
	class SceneFrame: public sf::View {
		private:
			Game *mGame;
			// Variables representing the min and max values mView center
			// point can assume
			Vectord mMin, mMax;
			shared_ptr<Spaceship> mShip;

			shared_ptr<Callback<sf::Event>> mResizeCbk;
			shared_ptr<Callback<SceneChangeEvent>> mSceneCbk;
			shared_ptr<Callback<PositionEvent>> mShipCbk;

			void onWindowResized(sf::Event e);
			void onSceneChanged(SceneChangeEvent e);
			void onShipMoved (PositionEvent e);
		public:
			SceneFrame(Game *game, shared_ptr<Spaceship> ship);
			~SceneFrame ();
	};
}


#endif