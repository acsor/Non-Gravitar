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
#ifndef NON_GRAVITAR_GAME_INFO_HPP
#define NON_GRAVITAR_GAME_INFO_HPP

#include "utils/Event.hpp"


namespace gvt {
	struct SpaceshipCountEvent: public gvt::Event {
			unsigned oldValue, newValue;

			SpaceshipCountEvent(unsigned old, unsigned _new);
	};

	struct ScoreEvent: public gvt::Event {
			unsigned oldValue, newValue;

			ScoreEvent(unsigned old, unsigned _new);
	};

	class GameInfo {
		private:
			unsigned mSpaceships;
			unsigned mScore;

			EventDispatcher<SpaceshipCountEvent> mShipDisp;
			EventDispatcher<ScoreEvent> mScoreDisp;
		public:
			GameInfo (unsigned score, unsigned spaceships);

			/**
			 * Decrements the spaceships count of @c 1.
			 */
			void decrementSpaceships();
			/**
			 * Brings the spaceships count down to @c 0.
			 */
			void resetSpaceships();
			inline unsigned spaceships() const;

			void upgradeScore (unsigned deltaScore);
			inline unsigned score() const;

			EventDispatcher<SpaceshipCountEvent>& shipCountDispatcher();
			EventDispatcher<ScoreEvent>& scoreDispatcher();
	};
}


namespace gvt {
	unsigned GameInfo::spaceships() const {
		return mSpaceships;
	}

	inline unsigned GameInfo::score() const {
		return mScore;
	}
}


#endif