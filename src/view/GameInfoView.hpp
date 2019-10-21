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
#ifndef NON_GRAVITAR_GAME_INFO_VIEW_HPP
#define NON_GRAVITAR_GAME_INFO_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <utils/Utils.hpp>
#include "control/GameInfo.hpp"
#include "shape/Spaceship.hpp"
#include "GraphicAssets.hpp"


namespace gvt {
	class Game;

	class GameInfoView: public sf::Drawable {
		private:
			static constexpr const unsigned SHIP_MARGIN = 10;

			Game *mGame;
			shared_ptr<GameInfo> mInfo;
			shared_ptr<Spaceship> mShip;
			GraphicAssets *mAssets;
			
			shared_ptr<Callback<FuelEvent>> mFuelCbk;
			shared_ptr<Callback<SpaceshipCountEvent>> mShipCbk;
			shared_ptr<Callback<ScoreEvent>> mScoreCbk;

			std::list<sf::Sprite> mShipSprites;
			mutable sf::Text mText;

			static const sf::Color TEXT_COLOR;

			void updateText();

			/**
			 * @return A text signaling the destruction of all bunkers in a
			 * given planet if they have been effectively destroyed, or an empty
			 * string otherwise.
			 */
			string missionCompleteText();
			/**
			 * @return A text signaling a state of game over, if that is the
			 * case, or an empty string otherwise.
			 */
			string gameOverText();
			void updateShips();

			void onFuelChanged (FuelEvent e);
			void onScoreChanged (ScoreEvent e);
			void onShipsChanged (SpaceshipCountEvent e);
		protected:
			void draw (sf::RenderTarget &t, sf::RenderStates s) const override;
		public:
			GameInfoView (Game *game, shared_ptr<Spaceship> ship);
			~GameInfoView () override;
	};
}


#endif