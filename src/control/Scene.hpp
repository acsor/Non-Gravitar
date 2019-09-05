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
#ifndef NON_GRAVITAR_SCENE_HPP
#define NON_GRAVITAR_SCENE_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "shape-group/ShapeGroup.hpp"
#include "utils/Event.hpp"
#include "view/ShapeGroupView.hpp"


namespace gvt {
	/**
	 * A @c Scene represent the notion of contextual shapes to be rendered on
	 * screen. It encapsulates shape groups and manages their lifetimes,
	 * adding semantic and event-handling operations.
	 */
	class Scene: public sf::Drawable {
		protected:
			shared_ptr<ShapeGroup> mShapes;
			shared_ptr<ShapeGroupView> mShapesView;

			explicit Scene(shared_ptr<ShapeGroup> shapes);
			void moveShapes (double seconds);
		public:
			friend class Game;
			
			/**
			 * @param seconds Seconds elapsed since the last scene computation
			 */
			virtual void onUpdateGame (double seconds);
			void draw (sf::RenderTarget &t, sf::RenderStates s) const override;
	};
}

#endif