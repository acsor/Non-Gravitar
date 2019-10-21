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
#ifndef NON_GRAVITAR_DEBUGGABLE_VIEW_HPP
#define NON_GRAVITAR_DEBUGGABLE_VIEW_HPP

#include <SFML/Graphics.hpp>


namespace gvt {
	class DebuggableView {
		friend class ShapeGroupView;

		protected:
			bool mDebug {false};
			sf::Color mDebugColor {DEFAULT_DEBUG_COLOR};

			virtual void onCreateDebugView () = 0;
			virtual void onUpdateDebugColor () = 0;

			DebuggableView() = default;
		public:
			static sf::Color const DEFAULT_DEBUG_COLOR;
			static sf::Color const COLLISION_DEBUG_COLOR;

			inline bool isDebug() const;
			inline virtual void setDebug(bool debug);

			inline void debugColor (sf::Color color);
	};
}


namespace gvt {
	bool DebuggableView::isDebug() const {
		return mDebug;
	}

	void DebuggableView::setDebug(bool debug) {
		mDebug = debug;
	}

	void DebuggableView::debugColor (sf::Color color) {
		mDebugColor = color;

        onUpdateDebugColor();
	}
}


#endif
