namespace gvt {
	template<typename E> EventDispatcher<E>::~EventDispatcher () {
		mCallbacks.clear();
	}

	template<typename E>
	void EventDispatcher<E>::addCallback(shared_ptr<Callback < E>> c) {
        mCallbacks.push_back(c);
	}

	template<typename E>
	shared_ptr<Callback < E>> EventDispatcher<E>::addCallback(Callback<E> c) {
		auto sharedCallback = std::make_shared<Callback < E>>(std::move(c));

		mCallbacks.push_back(sharedCallback);

		return sharedCallback;
	}

	template<typename E>
	void EventDispatcher<E>::removeCallback(shared_ptr<Callback < E>> &c) {
		mCallbacks.remove(c);
	}

	template<typename E>
	void EventDispatcher<E>::clearCallbacks() {
		mCallbacks.clear();
	}

	template<typename E>
	void EventDispatcher<E>::raiseEvent(shared_ptr<E> event) {
		auto callbacksCopy = mCallbacks;

		for (auto const &callback: callbacksCopy)
			callback->operator()(event);
	}

	template<typename E> size_t EventDispatcher<E>::callbacksCount() const {
		return mCallbacks.size();
	}
}
