// MIT License
// 
// Copyright (c) 2018 Oscar B.
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
#include "control/SolarSystemSceneBuilder.hpp"


void closeWindow (sf::RenderWindow &w, sf::Event e);


int main () {
	auto const mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow w{mode, "Non-Gravitar"};
	sf::Event e;

	auto game = gvt::Game::getInstance();
	auto centerPos = gvt::Vectord({1000, 700});
	unsigned planetsNum = 5;
	auto ssBuilder = gvt::SolarSystemSceneBuilder().
			centerPosition(centerPos).
			planetsNumber(planetsNum).
			planetsLayout(std::make_shared<gvt::RoundShapeLayout>(
				centerPos, 400,	planetsNum
			)).
			planetBuilder(std::make_shared<gvt::RandomPlanetBuilder>(
				gvt::Vectord{30, 50}, 30, 5, 2
			));
	auto rootScene = ssBuilder();

	w.setFramerateLimit(60);

	rootScene->shapeGroup()->insert(game->spaceship());
	game->pushScene(rootScene);
	rootScene->solarSystem()->spawnArea()->centerShape(
			game->spaceship()
	);
	game->viewEventsDispatcher().addCallback(
		[&w] (sf::Event const &e) -> void { closeWindow(w, e); }
	);

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
