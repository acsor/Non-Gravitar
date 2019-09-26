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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "shape-group/GridShapeLayout.hpp"
#include "control/Game.hpp"
#include "control/SolarSystemScene.hpp"

using sf_callback = gvt::Callback<sf::Event>;


void closeWindow (sf::RenderWindow &w, sf::Event e);


int main () {
	sf::VideoMode const mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow w{mode, "Non-Gravitar"};
	sf::Event e;

	gvt::Game *game = gvt::Game::getInstance();
	auto rootScene = std::make_shared<gvt::SolarSystemScene>(
			game->solarSystemFactory()()
	);

	w.setFramerateLimit(60);

	game->pushScene(rootScene);
	game->viewEventsDispatcher().addCallback(
			[&w] (sf::Event const &e) -> void { closeWindow(w, e); }
	);

	game->spaceship()->position({500, 500});
	rootScene->shapes()->insert(game->acquireSpaceship());

	while (w.isOpen()) {
		while (w.pollEvent(e))
			game->viewEventsDispatcher().raiseEvent(e);

		game->updateGameLoop();

		w.clear(sf::Color(10, 10, 10));
		w.draw(*game);
		w.display();
	}

	return EXIT_SUCCESS;
}


void closeWindow (sf::RenderWindow &w, sf::Event e) {
	if (e.type == sf::Event::Closed)
		w.close();
}
