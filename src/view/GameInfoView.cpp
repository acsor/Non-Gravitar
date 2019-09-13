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
#include "GameInfoView.hpp"
#include "SpaceshipView.hpp"
#include "utils/Utils.hpp"


namespace gvt {
	const sf::Color GameInfoView::TEXT_COLOR = sf::Color(0, 111, 109);
	const std::string GameInfoView::DEFAULT_FONT = gvt::staticsGet("fonts/ERGOB.TTF");


	void GameInfoView::updateText() {
		mText.setString(
			"SCORE\t" + std::to_string(mInfo->score()) +
			"\nFUEL ?"
		);
		auto const bounds = mText.getLocalBounds();

		mText.setOrigin(bounds.width / 2.0f, 0);
	}

	void GameInfoView::updateShips() {
		int toDelete = static_cast<int> (
			mShipSprites.size() - mInfo->spaceships()
		);

		// We need to add spaceships, not remove them
		if (toDelete < 0) {
			while (toDelete < 0) {
				auto ship = sf::Sprite(mShipTexture);

				if (mShipSprites.empty()) {
					ship.setPosition(0, 0);
				} else {
					auto lastBounds = mShipSprites.back().getGlobalBounds();

					ship.setPosition(
							lastBounds.left + lastBounds.width + SHIP_MARGIN, 0
					);
				}

				mShipSprites.push_back(ship);

				toDelete++;
			}
		} else if (toDelete > 0) {
			while (toDelete > 0) {
				mShipSprites.pop_back();
				toDelete--;
			}
		}
	}

	void GameInfoView::draw (sf::RenderTarget &t, sf::RenderStates s) const {
		auto const size = t.getSize();

		mText.setPosition(size.x / 2.0f, 0);

		for (auto const &ship: mShipSprites)
			t.draw(ship, s);

		t.draw(mText, s);
	}

	GameInfoView::GameInfoView (shared_ptr<GameInfo> gameInfo):
			mInfo{std::move(gameInfo)} {
		auto shipTexturePath = gvt::staticsGet(SpaceshipView::SPACESHIP_TEXTURE);

		if (!mShipTexture.loadFromFile(shipTexturePath))
			throw std::runtime_error {
					"Could not load spaceship textures from disk"
			};
		if (!mFont.loadFromFile(DEFAULT_FONT))
			throw std::runtime_error ("Could not load font from disk");

		mShipTexture.setSmooth(true);

		mText = sf::Text("", mFont);
		mText.setFillColor(TEXT_COLOR);
		mText.setPosition(0, 0);

		updateShips();
		updateText();
	}
}
