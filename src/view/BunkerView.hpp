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
#ifndef NON_GRAVITAR_BUNKER_VIEW
#define NON_GRAVITAR_BUNKER_VIEW

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ShapeView.hpp"
#include "../model/Bunker.hpp"

template<typename T> using weak_ptr = std::weak_ptr<T>;
template<typename T> using shared_ptr = std::shared_ptr<T>;
using RenderStates = sf::RenderStates;
using RenderTarget = sf::RenderTarget;
using Texture = sf::Texture;


namespace gvt {
	class BunkerView: public ShapeView {
		private:
			weak_ptr<Bunker> mBunker;

			sf::Sprite mSprite{};
			Texture mTexture;
		public:
			static const std::string BUNKER2D_GRAPHICS;
			static const std::string BUNKER3D_GRAPHICS;

			BunkerView(shared_ptr<Bunker> bunker, bool debug=false);

			void draw(RenderTarget &target, RenderStates state) const override;
			void handle(Event const &e) override;
	};
}

#endif
