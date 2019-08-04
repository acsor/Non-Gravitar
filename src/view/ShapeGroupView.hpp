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
#ifndef NON_GRAVITAR_SHAPE_GROUP_VIEW
#define NON_GRAVITAR_SHAPE_GROUP_VIEW

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "utils/Event.hpp"
#include "shape-group/ShapeGroup.hpp"
#include "view/ShapeView.hpp"
#include "ShapeViewFactory.hpp"
#include "Debuggable.hpp"

template<typename T> using weak_ptr = std::weak_ptr<T>;
template<typename T> using shared_ptr = std::shared_ptr<T>;
template<typename T> using unique_ptr = std::unique_ptr<T>;


namespace gvt {
	class ShapeGroupView: public sf::Drawable, public GVTEventHandler,
			public Debuggable {
		private:
			ShapeViewFactory mFactory;
		protected:
			weak_ptr<ShapeGroup> mGroup;
			std::map<Shape*, shared_ptr<ShapeView>> mViews;

		public:
			explicit ShapeGroupView(
				shared_ptr<ShapeGroup> group, bool debug=false
			);
			virtual ~ShapeGroupView();

			void debug (bool debug) override;

			void draw(
				sf::RenderTarget &target, sf::RenderStates state
			) const override;
			void handle(Event *e) override;
	};
}


#endif
