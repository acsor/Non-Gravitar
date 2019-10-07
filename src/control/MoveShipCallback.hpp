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
#ifndef NON_GRAVITAR_MOVE_SHIP_CALLBACK_HPP
#define NON_GRAVITAR_MOVE_SHIP_CALLBACK_HPP

#include <SFML/Graphics.hpp>
#include "shape/Spaceship.hpp"


namespace gvt {
	class Game;

	/**
	 * Moves the given @c Spaceship instance as key events from the view
	 * library arise.
	 */
	class MoveShipCallback {
		private:
			Game *mGame;
			shared_ptr<Spaceship> mShip;
			/**
			 * @c true if the spaceship is currently emitting its tractor
			 * beam, @c false otherwise.
			 */
			bool mBeamOn{false};

			double mAngleStep, mAccelStep;
		public:
			MoveShipCallback (
					Game *game, shared_ptr<Spaceship> ship, double accel,
					double angle
			);

			void operator() (sf::Event e);
	};
}


#endif