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
#ifndef NON_GRAVITAR_SHAPE_GROUP_VIEW
#define NON_GRAVITAR_SHAPE_GROUP_VIEW

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "utils/Event.hpp"
#include "shape-group/ShapeGroup.hpp"
#include "view/ClosedShapeView.hpp"
#include "ShapeViewFactory.hpp"
#include "DebuggableView.hpp"


namespace gvt {
	class ShapeGroupView: public sf::Drawable, public DebuggableView {
		private:
			template<typename T> using sp = std::shared_ptr<T>;

			ShapeViewFactory mFactory;

			shared_ptr<Callback<ShapeInsertionEvent>> mAttachCbk;
			shared_ptr<Callback<ShapeRemovalEvent>> mRemovalCbk;
			shared_ptr<Callback<ShapeGroupDestructionEvent>> mDestrCbk;

			void onShapeInserted (ShapeInsertionEvent e);
			void onShapeRemoved (ShapeRemovalEvent e);
			void onShapeGroupDestroyed (ShapeGroupDestructionEvent e);
		protected:
			shared_ptr<ShapeGroup> mGroup;
			mutable std::unordered_map<sp<Shape>, sp<ShapeView>> mViews;

			void onCreateDebugView() override;
			void onUpdateDebugColor () override;

			void draw(sf::RenderTarget &t, sf::RenderStates s) const override;
		public:
			explicit ShapeGroupView(sp<ShapeGroup> const &group);
			~ShapeGroupView() override;

			void setDebug(bool debug) override;
			/**
			 * @return The view object associated to the given @c Shape
			 * instance.
			 */
			shared_ptr<ShapeView> viewFor (shared_ptr<Shape> shape);
	};
}


#endif
