#ifndef NON_GRAVITAR_DEBUGGABLE_HPP
#define NON_GRAVITAR_DEBUGGABLE_HPP


namespace gvt {
	class Debuggable {
		protected:
			bool mDebug;

			explicit Debuggable(bool debug): mDebug{debug} {};
		public:
			bool debug () const { return mDebug; }
			virtual void debug (bool debug) { mDebug = debug; }
	};
}


#endif
