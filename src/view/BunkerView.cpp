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
#include "shape/Shape.hpp"
#include "utils/Utils.hpp"
#include "BunkerView.hpp"

using BunkerView = gvt::BunkerView;


const std::string BunkerView::BUNKER2D_GRAPHICS = "graphics/bunker-2.png";
const std::string BunkerView::BUNKER3D_GRAPHICS = "graphics/bunker-3.png";


void BunkerView::draw(RenderTarget &target, RenderStates state) const {
	Shape2DView::draw(target, state);

	target.draw(mSprite, mTranslation * mRotation);
}

BunkerView::BunkerView(const shared_ptr<Bunker>& bunker):
	Shape2DView(bunker) {
	std::string texturePath;

	// TODO Add a further texture for bunkers having 4 or more directions
	if (bunker->directions() == 2)
		texturePath = gvt::staticsGet(BUNKER2D_GRAPHICS);
	else
		texturePath = gvt::staticsGet(BUNKER3D_GRAPHICS);

	if (!mTexture.loadFromFile(texturePath))
		throw std::runtime_error("Could not load Bunker texture from disk");

	mSprite.setTexture(mTexture);
}

