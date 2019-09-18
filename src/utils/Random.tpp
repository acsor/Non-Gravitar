namespace gvt {
	template<typename N>
	UniRandom<N>::UniRandom(N low, N high): mDist{low, high} {
		mEngine.seed(time(nullptr));
	}

	template<typename N>
	N UniRandom<N>::operator() () {
		return mDist(mEngine);
	}

	UniRandom<double>::UniRandom(double low, double high):
			mDist{low, high} {
		mEngine.seed(time(nullptr));
	}

	double UniRandom<double>::operator() () {
		return mDist(mEngine);
	}


	template<typename I> IteratorRandomizer<I>::IteratorRandomizer (I begin, I end):
			mBegin{begin}, mChoice(0, std::distance(begin, end) - 1) {
	}

	template<typename I> I IteratorRandomizer<I>::operator() () {
		auto copy = mBegin;
		std::advance(copy, mChoice());

		return copy;
	}
}