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
#include "control/GameInfo.hpp"
#include "shape/Spaceship.hpp"


namespace gvt {
	class Game;

	class GameInfoView: public sf::Drawable {
		private:
			static constexpr const unsigned SHIP_MARGIN = 10;

			shared_ptr<GameInfo> mInfo;
			shared_ptr<Spaceship> mShip;
			shared_ptr<gvt_callback> mFuelCallback, mScoreCallback, mShipCallback;

			sf::Font mFont;
			sf::Texture mShipTexture;
			std::list<sf::Sprite> mShipSprites;
			mutable sf::Text mText;

			static const sf::Color TEXT_COLOR;
			static const std::string DEFAULT_FONT;

			void updateText();
			void updateShips();

			void onFuelChanged (shared_ptr<gvt::Event> const &e);
			void onScoreChanged (shared_ptr<gvt::Event> const &e);
			void onShipsChanged (shared_ptr<gvt::Event> const &e);
		protected:
			void draw (sf::RenderTarget &t, sf::RenderStates s) const override;
		public:
			GameInfoView (
					shared_ptr<GameInfo> gameInfo, shared_ptr<Spaceship> ship
			);
			~GameInfoView () override;
	};
}


#endif