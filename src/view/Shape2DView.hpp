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

#include "view/ShapeView.hpp"
#include "shape/Shape2D.hpp"


namespace gvt {
	class Shape2DView: public ShapeView {
		private:
			// Debugs bounds used for the 'debug view'
			sf::VertexArray mBounds;
			sf::Color mDebugColor = DEBUG_COLOR;

			static sf::Color const DEBUG_COLOR, HIGHLIGHT_COLOR;

			void updateDebugBounds();
		protected:
			explicit Shape2DView(std::shared_ptr<Shape2D> const &shape);

			void updateRotation() override;

			void onDraw(
				shared_ptr<Shape> shape, RenderTarget &t, RenderStates s
			) const override;
			void onMoved() override;
			void onRotated() override;
			void onDestroyed() override;
		public:
			void debug(bool debug) override;

			void hightlight (bool highlighted) override;
	};
}


#endif
