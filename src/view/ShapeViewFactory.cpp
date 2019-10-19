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
#include "ShapeViewFactory.hpp"
#include "FuelView.hpp"
#include "PolylineView.hpp"
#include "PlanetView.hpp"
#include "RoundMissileView.hpp"
#include "SpaceshipView.hpp"
#include "SpawnAreaView.hpp"
#include "TractorBeamView.hpp"


namespace gvt {
	ShapeView* ShapeViewFactory::operator()(shared_ptr<Shape> shape) const {
		if (auto b = std::dynamic_pointer_cast<Bunker>(shape)) {
			return new BunkerView(b);
		} else if (auto f = std::dynamic_pointer_cast<Fuel>(shape)) {
			return new FuelView(f);
		} else if (auto pl = std::dynamic_pointer_cast<Planet>(shape)) {
			return new PlanetView(pl);
		} else if (auto p = std::dynamic_pointer_cast<Polyline>(shape)) {
			return new PolylineView(p);
		} else if (auto m = std::dynamic_pointer_cast<RoundMissile>(shape)) {
			return new RoundMissileView(m);
		} else if (auto ship = std::dynamic_pointer_cast<Spaceship>(shape)) {
			return new SpaceshipView(ship);
		} else if (auto spawn = std::dynamic_pointer_cast<SpawnArea>(shape)) {
			return new SpawnAreaView(spawn);
		} else if (auto t = std::dynamic_pointer_cast<TractorBeam>(shape)) {
			return new TractorBeamView(t);
		} else {
			throw std::domain_error("Unrecognized type of shape");
		}
	}
}

