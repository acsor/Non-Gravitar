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
#include <typeinfo>
#include "../shape/Shape.hpp"
#include "../Utils.hpp"
#include "BunkerView.hpp"

using BunkerView = gvt::BunkerView;


const std::string BunkerView::BUNKER2D_GRAPHICS = "graphics/bunker-2.png";
const std::string BunkerView::BUNKER3D_GRAPHICS = "graphics/bunker-3.png";


BunkerView::BunkerView(shared_ptr<Bunker> bunker, bool debug):
	ShapeView(bunker, debug), mBunker{bunker} {
	std::string texturePath;

	if (typeid(*bunker) == typeid(gvt::Bunker2D))
		texturePath = gvt::staticsGet(BUNKER2D_GRAPHICS);
	else if (typeid(*bunker) == typeid(gvt::Bunker3D))
		texturePath = gvt::staticsGet(BUNKER3D_GRAPHICS);
	else
		throw std::domain_error("Unrecognized type of Bunker received");

	if (!mTexture.loadFromFile(texturePath))
		throw std::runtime_error("Could not load Bunker texture from disk");

	mSprite.setPosition(bunker->x(), bunker->y());
	mSprite.setOrigin(bunker->originX(), bunker->originY());
	mSprite.setRotation(bunker->rotation());
	mSprite.setTexture(mTexture);
}

void BunkerView::draw(RenderTarget &target, RenderStates state) const {
	ShapeView::draw(target, state);

	target.draw(mSprite);
}

void BunkerView::handle(Event *e) {
	ShapeView::handle(e);
	auto event = dynamic_cast<ShapeEvent*>(e);

	if (event) {
		if (auto p = mBunker.lock()) {
			if (event->type == ShapeEvent::Type::moved) {
				mSprite.setPosition(p->x(), p->y());
			} else if (event->type == ShapeEvent::Type::origin) {
				mSprite.setOrigin(p->originX(), p->originY());
			} else if (event->type == ShapeEvent::Type::rotated) {
				mSprite.setRotation(gvt::rad2deg(p->rotation()));
			}
		} else if (event->type == ShapeEvent::Type::destroyed) {
			mSprite = sf::Sprite();
		}
	}
}
