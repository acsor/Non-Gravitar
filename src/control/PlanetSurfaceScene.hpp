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
#ifndef NON_GRAVITAR_PLANET_SURFACE_SCENE_HPP
#define NON_GRAVITAR_PLANET_SURFACE_SCENE_HPP

#include <list>
#include <SFML/Window/Event.hpp>
#include "shape/Planet.hpp"
#include "shape-group/PlanetSurface.hpp"
#include "Scene.hpp"


namespace gvt {
	class PlanetSurfaceScene: public Scene {
		private:
			shared_ptr<Planet> mPlanet;

			// New missiles' lifetime, given in seconds
			static long const constexpr MISSILE_LIFESPAN = 1000;
			static double const constexpr MISSILE_SPEED = 600.0;
			static double const constexpr MISSILE_RADIUS = 6.0;
			// Time to wait before a new missile is shot, in seconds
			static double const constexpr MISSILE_DELAY = 4.0;

			/**
			 * Invokes code responsible for popping out the current @c
			 * PlanetSurfaceScene and returning back to the previous game scene.
			 */
			void exitPlanet();
			void onExitBoundaries(shared_ptr<Spaceship> ship) override;

			explicit PlanetSurfaceScene(shared_ptr<PlanetSurface> const &s);
		public:
			explicit PlanetSurfaceScene(shared_ptr<Planet> const &planet);

			void onUpdateGame (double seconds) override;
	};
}


#endif