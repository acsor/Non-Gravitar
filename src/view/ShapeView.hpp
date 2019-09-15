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
#ifndef NON_GRAVITAR_SHAPEVIEW_HPP
#define NON_GRAVITAR_SHAPEVIEW_HPP

#include <memory>
#include <SFML/Graphics.hpp>
#include "shape/Shape.hpp"
#include "DebuggableView.hpp"

template<typename T> using weak_ptr = std::weak_ptr<T>;
template<typename T> using shared_ptr = std::shared_ptr<T>;
using RenderStates = sf::RenderStates;
using RenderTarget = sf::RenderTarget;


namespace gvt {
	class ShapeView: public sf::Drawable, public DebuggableView {
		private:
			shared_ptr<Callback<PositionEvent>> mPosCbk;
			shared_ptr<Callback<RotationEvent>> mRotCbk;
			shared_ptr<Callback<CollisionEvent>> mColCbk;
		protected:
			sf::Transform mTranslation, mRotation;
			shared_ptr<Shape> mShape;

			explicit ShapeView(shared_ptr<Shape> shape);

			/**
			 * Updates the rotation sf::Transform, to be efficiently
			 * exploited by subclasses when rotating the drawn object.
			 */
			virtual void updateRotationTransform() = 0;
			/**
			 * Updates the translation sf::Transform, to be efficiently
			 * exploited by subclasses when moving the drawn object.
			 */
			virtual void updateTranslationTransform();

			virtual void onShapeMoved(shared_ptr<PositionEvent> e);
			virtual void onShapeRotated(shared_ptr<RotationEvent> e);
			virtual void onShapeCollided(shared_ptr<CollisionEvent> e) {};
		public:
			friend class ShapeGroupView;

			~ShapeView() override;
	};
}


#endif