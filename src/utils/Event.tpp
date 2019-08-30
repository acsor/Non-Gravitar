namespace gvt {
	template<typename E> EventDispatcher<E>::~EventDispatcher () {
		mCallbacks.clear();
	}

	template<typename E>
	void EventDispatcher<E>::addCallback(shared_ptr<callback<E>> c) {
        mCallbacks.push_back(c);
	}

	template<typename E>
	shared_ptr<callback<E>> EventDispatcher<E>::addCallback(callback<E> c) {
		auto sharedCallback = std::make_shared<callback<E>>(std::move(c));

		mCallbacks.push_back(sharedCallback);

		return sharedCallback;
	}

	template<typename E>
	void EventDispatcher<E>::removeCallback(shared_ptr<callback<E>> c) {
		mCallbacks.remove(c);
	}

	template<typename E>
	void EventDispatcher<E>::clearCallbacks() {
		mCallbacks.clear();
	}

	template<typename E>
	void EventDispatcher<E>::notify(shared_ptr<E> event) {
		for (shared_ptr<callback<E>> callback: mCallbacks)
			callback->operator()(event);
	}

	template<typename E> size_t EventDispatcher<E>::callbacks() const {
		return mCallbacks.size();
	}
}
