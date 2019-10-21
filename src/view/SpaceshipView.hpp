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
#ifndef NON_GRAVITAR_SPACESHIP_VIEW_HPP
#define NON_GRAVITAR_SPACESHIP_VIEW_HPP

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "shape/Spaceship.hpp"
#include "utils/Event.hpp"
#include "ClosedShapeView.hpp"
#include "GraphicAssets.hpp"


namespace gvt {
	class SpaceshipView: public ClosedShapeView {
		private:
			shared_ptr<Spaceship> mShip;
			sf::Sprite mutable mSprite;
			GraphicAssets *mAssets;

			bool mAccel{false};

			// TODO Amongst the most absurd bugs I ever had! If I remove this
			//  field (completely invisible, completely unused), I get a
			//  segfault at a certain execution point of the program.
			sf::Texture mTexture;
		protected:
			void draw(sf::RenderTarget &t, sf::RenderStates s) const override;
			void onShapeMoved(PositionEvent e) override;
		public:
			explicit SpaceshipView(const shared_ptr<Spaceship>& spaceship);
	};
}


#endif
