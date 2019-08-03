namespace gvt {
	template<typename E> EventDispatcher<E>::~EventDispatcher () {
		mHandlers.clear();
	}
	
	template<typename E> void EventDispatcher<E>::addHandler(
		EventHandler<E> *h
	) {
		mHandlers.insert(h);
	}
	
	template<typename E> void EventDispatcher<E>::removeHandler(
		EventHandler<E> *h
	) {
		mHandlers.erase(h);
	}

	template<typename E> void EventDispatcher<E>::addHandler(
		EventHandler<E> &h
	) {
		mHandlers.insert(&h);
	}

	template<typename E> void EventDispatcher<E>::removeHandler(
		EventHandler<E> &h
	) {
		mHandlers.erase(&h);
	}

	template<typename E> void EventDispatcher<E>::notify(E *e) const {
		for (auto i = mHandlers.begin(); i != mHandlers.end(); i++)
			(*i)->handle(e);
	}
}
