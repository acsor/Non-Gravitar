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
#include <iostream>
#include <cmath>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "shape/Spaceship.hpp"
#include "shape-bundle/ShapeBundle.hpp"
#include "shape-bundle/DummyBundle.hpp"
#include "shape/Bunker.hpp"
#include "utils/Vector.hpp"
#include "view/BunkerView.hpp"
#include "view/ShapeBundleView.hpp"
#include "view/SpaceshipView.hpp"

template<typename T> using shared_ptr = std::shared_ptr<T>;

using Event = sf::Event;
using Keyboard = sf::Keyboard;
using RenderWindow = sf::RenderWindow;

using ShapeBundle = gvt::ShapeBundle;
using Spaceship = gvt::Spaceship;
using SpaceshipView = gvt::SpaceshipView;

using Bunker = gvt::Bunker;
using BunkerView = gvt::BunkerView;


#define STEP_SIZE 5
#define ANGLE_SIZE (10 * M_PI / 180.0)


// TODO Replace with exceedingly succint lambda
class CloseWindowHandler: public gvt::EventHandler<sf::Event> {
	private:
		sf::Window &mWindow;
	public:
		explicit CloseWindowHandler(sf::Window &window): mWindow{window} {};
		void handle (sf::Event *e) override {
			if (e->type == sf::Event::Closed)
				mWindow.close();
		}
};

// TODO Replace with lambda
class MoveShipHandler: public gvt::EventHandler<sf::Event> {
	private:
		shared_ptr<Spaceship> mShip;
	public:
		explicit MoveShipHandler(shared_ptr<Spaceship> spaceship):
				mShip{spaceship} {};

		void handle (sf::Event *e) override {
			switch (e->type) {
				case (Event::KeyPressed):
					switch (e->key.code) {
						case (Keyboard::Key::A):
							mShip->rotate(-ANGLE_SIZE);
							break;
						case (Keyboard::Key::W):
							mShip->moveAlong(
									gvt::Vectorf(mShip->rotation()) * STEP_SIZE
							);
							break;
						case (Keyboard::Key::D):
							mShip->rotate(ANGLE_SIZE);
							break;
						case (Keyboard::Key::S):
							// Should activate the shields in a future version
							// of the program
							break;
						default:
							break;
					}
				default:
					break;
			}
		}
};


int main () {
	sf::VideoMode const mode = sf::VideoMode::getDesktopMode();
	RenderWindow w{mode, "Non-Gravitar"};

	shared_ptr<ShapeBundle> bundle{new gvt::DummyBundle()};
	shared_ptr<Spaceship> ship{new Spaceship(22, 23, 1000)};
	gvt::ShapeBundleView view(bundle);

	gvt::EventDispatcher<sf::Event> loopDispatcher;
	Event e;

	w.setFramerateLimit(45);

	bundle->insert(ship);
	bundle->insert(shared_ptr<Bunker>(new gvt::Bunker2D(600, 500)));
	bundle->insert(shared_ptr<Bunker>(new gvt::Bunker3D(500, 500)));

	loopDispatcher.addHandler(new CloseWindowHandler(w));
	loopDispatcher.addHandler(new MoveShipHandler(ship));

	while (w.isOpen()) {
		while (w.pollEvent(e))
			loopDispatcher.notify(&e);

		w.clear();
		w.draw(view);
		w.display();
	}

	return EXIT_SUCCESS;
}
