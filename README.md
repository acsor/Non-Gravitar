# Project Non-Gravitar
!["Gravitar cover"](./gravitar.jpg "Gravitar cover")

University of Bologna 2018/19 Programming project (CS course), aiming to
produce a reduced C++ implementation of the Atari 1982 game
[Gravitar](https://en.wikipedia.org/wiki/Gravitar).

## Running
In order to compile this project, first ensure you have all the needed
dependencies:
	* The [SFML library](https://www.sfml-dev.org/)

Once you have completed your setup, simply issue the following commands

```
mkdir build
cd build
cmake ..
make NonGravitar # (1)
./NonGravitar # (2)
```

## Testing
This project possesses a reasonable unit-testing suite, written according to
[Catch2](https://github.com/catchorg/Catch2). In order to run it, simply
substitute commands `(1)` and `(2)` above with

```
make test-all
./test-all
```
