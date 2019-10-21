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
#include "GraphicAssets.hpp"
#include "utils/Utils.hpp"


namespace gvt {
	GraphicAssets* GraphicAssets::sInstance = nullptr;

	GraphicAssets::GraphicAssets() {
		auto s = gvt::staticsGet;

		if (!defaultFont.loadFromFile(s("fonts/Hyperspace.otf")))
			throw std::runtime_error("Could not load Hyperspace.otf");

		if (!spaceshipTexture.loadFromFile(s("graphics/spaceship.png")))
			throw std::runtime_error("Could not load spaceship.png texture");
		if (!spaceshipTextureAccel.loadFromFile(s("graphics/spaceship-accelerating.png")))
			throw std::runtime_error("Could not load spaceship-accelerating.png texture");
		if (!fuelTexture.loadFromFile(s("graphics/fuel.png")))
			throw std::runtime_error("Could not load fuel.png texture");
		if (!bunker2Texture.loadFromFile(s("graphics/bunker-2.png")))
			throw std::runtime_error("Could not load bunker-2.png texture");
		if (!bunker3Texture.loadFromFile(s("graphics/bunker-3.png")))
			throw std::runtime_error("Could not load bunker-3.png texture");

		spaceshipTexture.setSmooth(true);
		spaceshipTextureAccel.setSmooth(true);
	}

	GraphicAssets* GraphicAssets::getInstance() {
		if (sInstance == nullptr) {
			sInstance = new GraphicAssets();
		}

		return sInstance;
	}
}
