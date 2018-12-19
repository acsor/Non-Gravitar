#MIT License
#
#Copyright (c) 2018 Oscar B. et al.
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all
#copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#SOFTWARE.
cc=g++
flags=-Wall
libs=-lsfml-graphics -lsfml-window -lsfml-system

.PHONY: clear


Observer.o: Observer.cpp Observer.hpp
	$(cc) $(flags) -c $(filter %.cpp, $^)

test.out: test-main.o test-observer.o Observer.o
	$(cc) $(flags) -o test.out $(filter %.cpp %.o, $^)

test-main.o: test/test-main.cpp
	$(cc) $(flags) -c $^

test-observer.o: test/test-observer.cpp
	$(cc) $(flags) -c $^


clear:
	rm -rf *.out *.o *.gch
