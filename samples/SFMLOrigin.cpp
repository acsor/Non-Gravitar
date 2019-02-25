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
#define ORIGIN_SIZE 1
#define ROTATE_SIZE 5

using namespace std;
using namespace sf;


/**
 * @brief SFML sample program demonstrating how the origin property of a
 * Drawable object is handle with respect to translation and rotation.
 * Commands are WASD to move the circle, and R to rotate it clockwise (keep
 * shift pressed to rotate anti-clockwise). To move the origin, rather edit the
 * code.
 */
int main (int argc, char *argv[]) {
	VideoMode const desktopMode = VideoMode::getDesktopMode();
	RenderWindow w{desktopMode, "SFML Origin Demo"};
	Event e;

	CircleShape circle{20}, origin{4};
	Rect<float> bounds;
	RectangleShape boundaries;

	// circle.setOrigin(5, 5);

	origin.setOrigin(4, 4);
	origin.setFillColor(Color::Green);

	boundaries.setFillColor(Color(0, 0, 0, 0));
	boundaries.setOutlineThickness(2);
	boundaries.setOutlineColor(Color::Red);

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
							circle.move(-STEP_SIZE, 0);
							break;
						case (Keyboard::Key::W):
							circle.move(0, -STEP_SIZE);
							break;
						case (Keyboard::Key::D):
							circle.move(STEP_SIZE, 0);
							break;
						case (Keyboard::Key::S):
							circle.move(0, STEP_SIZE);
							break;
						case (Keyboard::Key::R):
							if (e.key.shift)
								circle.rotate(-ROTATE_SIZE);
							else
								circle.rotate(ROTATE_SIZE);
						default:
							break;
					}
				default:
					break;
			}
		}

		origin.setPosition(circle.getPosition().x, circle.getPosition().y);

		bounds = circle.getGlobalBounds();
		boundaries.setPosition({bounds.left, bounds.top});
		boundaries.setSize({bounds.width, bounds.height});

		w.clear(Color::Black);
		w.draw(circle);
		w.draw(origin);
		w.draw(boundaries);
		w.display();
	}

	return EXIT_SUCCESS;
}

