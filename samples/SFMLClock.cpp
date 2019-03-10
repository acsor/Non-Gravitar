#include <iostream>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;


int main (int argc, char *argv[]) {
	Clock c;
	string input;

	cout << "Enter <enter> to count the elapsed time, 'r' to restart or `q' to"
		"quit." << endl;

	do {
		input = cin.get();

		if (input == '\n') {
			cout << c.getElapsedTime().asSeconds();
		} else if (input == 'r') {
			c.restart();
		}
	} while(input != 'q');

	return EXIT_SUCCESS;
}
