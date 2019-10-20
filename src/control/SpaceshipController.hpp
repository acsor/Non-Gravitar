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
#ifndef NON_GRAVITAR_SPACESHIP_CONTROLLER_HPP
#define NON_GRAVITAR_SPACESHIP_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include "shape/Spaceship.hpp"
#include "Scene.hpp"


namespace gvt {
	class Game;

	/**
	 * Moves the given @c Spaceship instance as key events from the view
	 * library arise.
	 */
	class SpaceshipController {
		private:
			Game *mGame;
			shared_ptr<Spaceship> mShip;
			/**
			 * @c mLastScene holds a pointer to the last scene where the
			 * spaceship tractor beam was inserted. It acts as a boolean
			 * variable indicating whether the tractor beam is already on,
			 * and permits the tractor beam removal when transitioning from an
			 * old scene to a newer one, where the user command to power it off
			 * is issued.
			 */
			shared_ptr<Scene> mLastScene;

			double mAngleStep, mAccelStep;
		public:
			SpaceshipController (
					Game *game, shared_ptr<Spaceship> ship, double accel,
					double angle
			);

			void operator() (sf::Event e);
	};
}


#endif