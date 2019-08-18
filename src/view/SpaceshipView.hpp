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
#ifndef NON_GRAVITAR_SPACESHIP_VIEW_HPP
#define NON_GRAVITAR_SPACESHIP_VIEW_HPP

#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Shape2DView.hpp"
#include "shape/Spaceship.hpp"
#include "utils/Event.hpp"

template<typename T> using weak_ptr = std::weak_ptr<T>;
template<typename T> using shared_ptr = std::shared_ptr<T>;
using RenderStates = sf::RenderStates;
using RenderTarget = sf::RenderTarget;
using Texture = sf::Texture;


namespace gvt {
	class SpaceshipView: public Shape2DView {
		private:
			weak_ptr<Spaceship> mSpaceship;
			bool mAccel{false};

			sf::Sprite mutable mSprite;
			/**
			 * Three @c Texture attributes that correspond to, respectively, an
			 * unalterated @c Spaceship, an accelerating @c Spaceship and a @c
			 * Spaceship whose shield is momentarily activated.
			 */
			Texture mTexture, mAccelTexture, mShieldTexture;
		protected:
			void onDraw(
					shared_ptr<Shape> shape, RenderTarget &t, RenderStates s
			) const override;
			void onShapeMoved() override;
			void onShapeDestroyed() override;
		public:
			static const std::string SPACESHIP_TEXTURE;
			static const std::string ACCEL_SPACESHIP_TEXTURE;

			explicit SpaceshipView(const shared_ptr<Spaceship>& spaceship);
	};
}


#endif
