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
#ifndef NON_GRAVITAR_MOTION_CONTROLLER_HPP
#define NON_GRAVITAR_MOTION_CONTROLLER_HPP

#include <SFML/System/Clock.hpp>
#include "shape-group/ShapeGroup.hpp"


namespace gvt {
	/**
	 * Controller class managing the movement of accelerated objects. Much of
	 * the code herein is lent from classical physics, with vectorial
	 * measures as absolute position, velocity and acceleration.
	 */
	class MotionController {
		private:
			sf::Clock mClock;
			weak_ptr<ShapeGroup> mShapes;
		public:
			explicit MotionController (shared_ptr<ShapeGroup> shapes);

			/**
			 * The starts the internal clock, used the regulate time events.
			 */
			void start();
			/**
			 * Signals the beginning of a new cycle, where the motion of the
			 * referenced shapes is updated according to the elapsed time.
			 */
			void nextCycle();
	};
}


#endif