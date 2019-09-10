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
#ifndef NON_GRAVITAR_SOLAR_SYSTEM_SCENE_HPP
#define NON_GRAVITAR_SOLAR_SYSTEM_SCENE_HPP

#include <typeindex>
#include "shape-group/SolarSystem.hpp"
#include "Scene.hpp"


namespace gvt {
	/**
	 * A @c SolarSystemScene features a solar system, giving the possibility
	 * to enter planets which the spaceship runs into.
	 */
	class SolarSystemScene: public Scene {
		private:
			shared_ptr<gvt_callback> mPlanetHandle;

			void onEnterPlanet (shared_ptr<gvt::Event> e);
		public:
			explicit SolarSystemScene (shared_ptr<SolarSystem> const &system);
			~SolarSystemScene () override;
	};
}

#endif