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
#include <algorithm>
#include <stdexcept>


namespace gvt {
	template<typename T>
	Vertex<T>::Vertex (unsigned long id, std::shared_ptr<T> value):
			mId{id}, mValue{value} {
	}

	template<typename T>
	std::shared_ptr<T> Vertex<T>::value() const {
		return mValue;
	}

	template<typename T>
	void Vertex<T>::value (std::shared_ptr<T> value) {
		mValue.reset(value);
	}

	template<typename T>
	bool Vertex<T>::operator== (Vertex const &other) const {
		return mId == other.mId;
	}

	template<typename T>
	bool Vertex<T>::operator<= (Vertex const &other) const {
		return mId <= other.mId;
	}

	template<typename T>
	bool Vertex<T>::operator< (Vertex const &other) const {
		return mId < other.mId;
	}


	template<typename T>
	bool ALGraph<T>::insertVertex(Vertex<T> const &vertex) {
		if (mEntries.find(vertex) == mEntries.end()) {
			mEntries[vertex] = std::list<Vertex<T>>();

			return true;
		}

		return false;
	}

	template<typename T>
	bool ALGraph<T>::containsVertex(Vertex<T> const &vertex) const {
		return mEntries.find(vertex) != mEntries.end();
	}

	template<typename T>
	bool ALGraph<T>::removeVertex(Vertex<T> const &vertex) {
		auto needle = mEntries.find(vertex);

        if (needle != mEntries.end()) {
        	mEntries.erase(needle);

        	return true;
        }

        return false;
	}

	template<typename T>
	bool ALGraph<T>::insertEdge(Vertex<T> const &u, Vertex<T> const &v) {
		if (containsVertex(u) && containsVertex(v)) {
			if (containsEdge(u, v)) {
				return false;
			} else {
				mEntries[u].push_back(v);

				return true;
			}
		} else {
			throw std::domain_error(
				"Either the u or v vertex was not in the graph"
		   );
		}
	}

	template<typename T>
	bool ALGraph<T>::removeEdge(Vertex<T> const &u, Vertex <T> const &v) {
		if (containsVertex(u) && containsVertex(v)) {
			if (containsEdge(u, v)) {
				mEntries[u].remove(v);

				return true;
			} else {
				return false;
			}
		} else {
			throw std::domain_error(
					"Either the u or v vertex was not in the graph"
			);
		}
	}

	template<typename T>
	bool ALGraph<T>::containsEdge (Vertex<T> const &u, Vertex<T> const &v) {
		if (containsVertex(u) && containsVertex(v)) {
			auto const &alist = mEntries[u];

			return std::find(alist.begin(), alist.end(), v) != alist.end();
		} else {
			throw std::domain_error(
					"Either the u or v vertex was not in the graph"
			);
		}
	}

	template<typename T>
	std::list<Vertex<T>> ALGraph<T>::vertices() const {
		std::list<Vertex<T>> vs;

		for (auto const &pair: mEntries)
			vs.push_back(pair.first);

		return vs;
	}

	template<typename T>
	std::list<Vertex<T>> ALGraph<T>::adjacents (Vertex<T> const &u) {
		if (mEntries.find(u) == mEntries.end()) {
			throw std::domain_error("The u vertex was not in the graph");
		} else {
			return mEntries[u];
		}
	}

	template<typename T>
	bool ALGraph<T>::operator== (ALGraph<T> const &other) const {
		return mEntries == other.mEntries;
	}
}
