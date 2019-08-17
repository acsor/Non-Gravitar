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
#include <SFML/Window/Event.hpp>
#include "GameViewController.hpp"


namespace gvt {
	GameViewController::GameViewController (
			sf::View &view, std::shared_ptr<Spaceship> ship
	): mView{view}, mSpaceship{ship} {
		mCallback = ship->addCallback(
			std::bind(&GameViewController::centerView, this, std::placeholders::_1)
		);
	}

	GameViewController::~GameViewController() {
		if (auto shared = mSpaceship.lock())
			shared->removeCallback(mCallback);
	}

	void GameViewController::centerView (std::shared_ptr<gvt::Event> e) {
        auto shapeEvent = std::dynamic_pointer_cast<ShapeEvent>(e);
        auto ship = mSpaceship.lock();

        if (ship && shapeEvent && shapeEvent->type == ShapeEvent::Type::moved) {
        	auto position = ship->position();

            mView.setCenter(position.x, position.y);
        }
	}

	void GameViewController::resizeView (std::shared_ptr<sf::Event> e) {
        if (e->type == sf::Event::Resized) {
        	mView.setSize(e->size.width, e->size.height);
        }
	}
}
