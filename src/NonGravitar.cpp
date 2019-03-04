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
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "model/Spaceship.hpp"
#include "view/SpaceshipView.hpp"

using Event = sf::Event;
using Keyboard = sf::Keyboard;
using RenderWindow = sf::RenderWindow;

using Spaceship = gvt::Spaceship;
using SpaceshipView = gvt::SpaceshipView;


#define STEP_SIZE 5
#define ANGLE_SIZE 10


int main () {
	sf::VideoMode const mode = sf::VideoMode::getDesktopMode();
	RenderWindow w{mode, "Non-Gravitar"};
	Event e;

	std::shared_ptr<Spaceship> ship{new Spaceship(0, 0, 1000)};
	SpaceshipView view{ship};

	ship->origin(ship->width() / 2, ship->height() / 2);
	w.setFramerateLimit(60);

	while (w.isOpen()) {
		while (w.pollEvent(e)) {
			switch (e.type) {
				case (Event::Closed):
					w.close();
					break;
				case (Event::KeyPressed):
					switch (e.key.code) {
						case (Keyboard::Key::A):
							ship->move(-STEP_SIZE, 0);
							break;
						case (Keyboard::Key::W):
							ship->move(0, -STEP_SIZE);
							break;
						case (Keyboard::Key::D):
							ship->move(STEP_SIZE, 0);
							break;
						case (Keyboard::Key::S):
							ship->move(0, STEP_SIZE);
							break;
						case (Keyboard::Key::R):
							if (e.key.shift)
								ship->rotation(ship->rotation() - ANGLE_SIZE);
							else
								ship->rotation(ship->rotation() + ANGLE_SIZE);
							break;
						default:
							break;
					}
				default:
					break;
			}
		}

		w.clear();
		w.draw(view);
		w.display();
	}

	return EXIT_SUCCESS;
}
