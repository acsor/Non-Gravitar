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
#ifndef NON_GRAVITAR_ALGRAPH_HPP
#define NON_GRAVITAR_ALGRAPH_HPP

#include <list>
#include <map>
#include <memory>


namespace gvt {
	/**
	 * A graph vertex, optionally holding bound data.
	 * @tparam T
	 */
	template<typename T> class Vertex {
		protected:
			unsigned long mId;
			std::shared_ptr<T> mValue;
		public:
			Vertex (unsigned long id, std::shared_ptr<T> value=nullptr);

			std::shared_ptr<T> value() const;
			void value (std::shared_ptr<T> value);

			/**
			 * @return @c true if this object id matches @c other's. Vertices
			 * are compared by their id only -- associated data is irrelevant.
			 */
			bool operator== (Vertex const &other) const;
			bool operator<= (Vertex const &other) const;
			bool operator< (Vertex const &other) const;
	};

	/**
	 * An adjacency-list implementation of a graph.
	 */
	template<typename T> class ALGraph {
		private:
			std::map<Vertex<T>, std::list<Vertex<T>>> mEntries;
		public:
			ALGraph() = default;

			/**
			 * @param vertex Vertex to add into the graph.
			 * @return @c true if @c vertex was actually inserted, @c false
			 * otherwise (it was already into the graph).
			 */
			bool insertVertex(Vertex<T> const &vertex);
			/**
			 * @param vertex Vertex to add into the graph.
			 * @return @c true if @c vertex was actually removed, @c false
			 * otherwise (it was not inside the graph).
			 */
			bool removeVertex(Vertex<T> const &vertex);
			bool containsVertex (Vertex<T> const &v) const;

			/**
			 * Inserts the <code>(u, v)</code> edge into the graph, if at all
			 * possible.
			 *
			 * @returns @c true if the <code>(u, v)</code> edge was actually
			 * inserted, @c false otherwise (i.e. it was already present).
			 * @throw std::domain_error If either @c u or @c v aren't
			 * vertices of this graph.
			 */
			bool insertEdge(Vertex<T> const &u, Vertex<T> const &v);
			/**
			 * Removes the <code>(u, v)</code> edge into the graph, if at all
			 * possible.
			 *
			 * @returns @c true if the <code>(u, v)</code> edge was actually
			 * delete, @c false otherwise (i.e. it was already out of the
			 * graph).
			 * @throw std::domain_error If either @c u or @c v aren't
			 * vertices of this graph.
			 */
			bool removeEdge(Vertex <T> const &, Vertex <T> const &v);
			bool containsEdge (Vertex<T> const &u, Vertex<T> const &v);

			std::list<Vertex<T>> vertices() const;
			/**
			 * @return A list of vertices <i>adjacent</i> to @c u, i.e. for
			 * which an <code>(u, v)</code> edge exists (@c v is in the
			 * returned vertices list).
			 */
			std::list<Vertex<T>> adjacents (Vertex<T> const &u);

			bool operator== (ALGraph<T> const &other) const;
	};
}


#include "ALGraph.tpp"


#endif