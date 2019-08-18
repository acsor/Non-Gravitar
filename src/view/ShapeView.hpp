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
			shared_ptr<gvt_callback> mCallback;

			void shapeChangeCallback (shared_ptr<Event> e);
		protected:
			sf::Transform mTranslation, mRotation;
			weak_ptr<Shape> mShape;

			explicit ShapeView(shared_ptr<Shape> const &shape);

			/**
			 * Updates the rotation sf::Transform, to be efficiently
			 * exploited by subclasses when rotating the drawn object.
			 */
			virtual void updateRotation() = 0;
			/**
			 * Updates the translation sf::Transform, to be efficiently
			 * exploited by subclasses when moving the drawn object.
			 */
			virtual void updateTranslation();

			/**
			 * Called during the drawing phase, only when the shape referenced
			 * to by this @c ShapeView can be accessed, in which case it is
			 * passed as a parameter.
			 *
			 * @param shape @c Shape to draw
			 */
			virtual void onDraw(
				shared_ptr<Shape> shape, RenderTarget &t, RenderStates s
			) const = 0;
			virtual void onShapeMoved();
			virtual void onShapeRotated();
			virtual void onShapeDestroyed() {};
		public:
			~ShapeView() override;

			void draw(RenderTarget &target, RenderStates states) const override;

			/**
			 * @return @c true if the shape visualized by this @c ShapeView
			 * terminated its lifetime, @c false otherwise. If this view
			 * expired, references to it may be freed up.
			 */
			bool expired() const;
	};
}


#endif