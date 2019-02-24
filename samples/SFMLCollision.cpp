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
#include <SFML/Graphics.hpp>

#define STEP_SIZE 5

using namespace std;
using namespace sf;


/**
 * @brief Small representative program making use of SFML built-in
 * collision-detection features. As can be seen, they are pretty basic and
 * warrant a more advanced system for detecting them.
 */
int main (int argc, char *argv[]) {
	VideoMode const desktopMode = VideoMode::getDesktopMode();
	RenderWindow w{desktopMode, "Non-Gravitar"};
	Event e;

	CircleShape point{10};
	VertexArray line = VertexArray(sf::Lines, 2);

	w.setFramerateLimit(60);

	line[0].position = Vector2f(0, 0);
	line[1].position = Vector2f(100, 100);

	while (w.isOpen()) {
		while (w.pollEvent(e)) {
			switch (e.type) {
				case (Event::Closed):
					w.close();
					break;
				case (Event::KeyPressed):
					switch (e.key.code) {
						case (Keyboard::Key::A):
							point.move(-STEP_SIZE, 0);
							break;
						case (Keyboard::Key::W):
							point.move(0, -STEP_SIZE);
							break;
						case (Keyboard::Key::D):
							point.move(STEP_SIZE, 0);
							break;
						case (Keyboard::Key::S):
							point.move(0, STEP_SIZE);
							break;
						default:
							break;
					}
				default:
					break;
			}
		}

		if (point.getGlobalBounds().intersects(line.getBounds())) {
			point.setFillColor(Color::Red);
		} else {
			point.setFillColor(Color::Green);
		}

		w.clear(Color::Black);
		w.draw(line);
		w.draw(point);
		w.display();
	}

	return EXIT_SUCCESS;
}
