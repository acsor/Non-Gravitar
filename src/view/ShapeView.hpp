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
#ifndef NON_GRAVITAR_SHAPE_VIEW
#define NON_GRAVITAR_SHAPE_VIEW

#include <memory>
#include <SFML/Graphics.hpp>
#include "shape/Shape.hpp"
#include "Debuggable.hpp"

template<typename T> using weak_ptr = std::weak_ptr<T>;
template<typename T> using shared_ptr = std::shared_ptr<T>;
using RenderStates = sf::RenderStates;
using RenderTarget = sf::RenderTarget;


namespace gvt {
	class ShapeView: public sf::Drawable, public GVTEventHandler,
			public Debuggable {
		private:
			sf::VertexArray mBounds;

			void updateTransform();
			void updateDebugBounds();
		protected:
			sf::Transform mTransform;
			weak_ptr<Shape> mShape;

			explicit ShapeView(const shared_ptr<Shape>& shape);

			virtual void onMoved();
			virtual void onRotated();
			virtual void onDestroyed();
		public:
			virtual ~ShapeView();

			void debug(bool debug) override;

			void draw(RenderTarget &target, RenderStates s) const override;
			void handle(Event *e) override;
	};
}


#endif
