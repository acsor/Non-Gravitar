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
#include <functional>
#include <memory>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "shape-group/SolarSystem.hpp"
#include "shape/Spaceship.hpp"
#include "shape/MountainChain.hpp"
#include "shape-group/ShapeGroup.hpp"
#include "shape-group/CollisionGroup.hpp"
#include "utils/Vector.hpp"
#include "view/ShapeGroupView.hpp"
#include "control/CollisionController.hpp"
#include "control/GameViewController.hpp"
#include "control/MotionController.hpp"

// While I know using-declarations are considered bad practice, setting up
// aliases was generating too much code
using namespace gvt;
using namespace sf;
using namespace std::placeholders;

using sf_callback = callback<sf::Event>;


#define ACCEL_INCREMENT 100.0
#define ANGLE_SIZE (10 * M_PI / 180.0)


void closeWindowCallback (RenderWindow &w, shared_ptr<sf::Event> e);
void moveShipCallback (shared_ptr<Spaceship> ship, shared_ptr<sf::Event> e);
/**
 * Toggles @c rootView debug state depending on the event @c e.
 */
void toggleDebugCallback (
		shared_ptr<ShapeGroupView> rootView, shared_ptr<sf::Event> e
);


int main () {
	VideoMode const mode = VideoMode::getDesktopMode();
	RenderWindow w{mode, "Non-Gravitar"};
	sf::View gameView = w.getDefaultView();

	shared_ptr<ShapeGroup> solarSystem{
		SolarSystem::makeRandom(8, 30, 50, {0, 0}, {1920, 1080})
	};
	shared_ptr<Spaceship> ship {new Spaceship({0, 0}, 1000)};
	shared_ptr<ShapeGroupView> rootView {new ShapeGroupView(solarSystem)};

	CollisionController collisionControl{solarSystem, rootView};
	GameViewController viewControl{gameView, ship};
	MotionController motionControl{solarSystem};

	EventDispatcher<sf::Event> loopDispatcher;
	sf::Event e;

	w.setFramerateLimit(45);

	solarSystem->insert(ship);
	ship->move({600, 500});

	loopDispatcher.addCallback(
		[&w] (shared_ptr<sf::Event> e) -> void { closeWindowCallback(w, e); }
	);
	loopDispatcher.addCallback(std::bind(moveShipCallback, ship, _1));
	loopDispatcher.addCallback(std::bind(toggleDebugCallback, rootView, _1));
	loopDispatcher.addCallback(std::bind(
		&GameViewController::resizeView, &viewControl, _1
	));

	motionControl.start();

	while (w.isOpen()) {
		while (w.pollEvent(e))
			loopDispatcher.notify(std::make_shared<sf::Event>(e));

		motionControl.nextCycle();

		w.clear();
		w.setView(gameView);
		w.draw(*rootView);
		w.display();
	}

	return EXIT_SUCCESS;
}


void closeWindowCallback (RenderWindow &w, shared_ptr<sf::Event> e) {
	if (e->type == sf::Event::Closed)
		w.close();
}

void moveShipCallback (shared_ptr<Spaceship> ship, shared_ptr<sf::Event> e) {
	auto accelIncrement = ACCEL_INCREMENT * Vectord(ship->rotation());
	accelIncrement.rotate(M_PI / -2.0);

	if (e->type == sf::Event::KeyPressed) {
		switch (e->key.code) {
			case (Keyboard::Key::A):
				ship->rotate(-ANGLE_SIZE);
				break;
			case (Keyboard::Key::W):
				ship->acceleration(accelIncrement);
				break;
			case (Keyboard::Key::D):
				ship->rotate(ANGLE_SIZE);
				break;
			case (Keyboard::Key::S):
				// Should activate the shields in a future version
				// of the program
				break;
			default:
				break;
		}
	} else if (e->type == sf::Event::KeyReleased) {
		if (e->key.code == Keyboard::Key::W) {
			ship->acceleration(Vectord{0, 0});
		}
	}
}

void toggleDebugCallback(
		shared_ptr<ShapeGroupView> rootView, shared_ptr<sf::Event> e
) {
	if (e->type == sf::Event::KeyPressed && e->key.code == Keyboard::Key::B && e->key.control) {
		rootView->setDebug(!rootView->isDebug());
	}
}
