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
#ifndef NON_GRAVITAR_UTILS_HPP
#define NON_GRAVITAR_UTILS_HPP

#include <string>


#define IN_CLOSED_INTERVAL(x, a, b)	((a) <= (x) && (x) <= (b))
#define IN_OPEN_INTERVAL(x, a, b)	((a) < (x) && (x) < (b))

#define	GVT_STATICS_DIR	"static/"


namespace gvt {
	using string = std::string;

	/**
	 * @brief Given a fullpath string, returns the portion representing a
	 * directory entry with a trailing @c / character.
	 * @param collapse Whether to collapse (i.e. remove) relative references
	 * like @c ../
	 * @throws std::domain_error If @c path contains no slashes
	 */
	string dirpath(string const &path, bool collapse = true);
	/**
	 * @brief Returns the full path of a static element referenced to by the
	 * local path value @c localPath.
	 * @param localPath Path value like @c graphics/spaceship.png, referring to
	 * an element found in the @c static/ project directory
	 *
	 * NOTE that this function relies on the preprocessor macro @c __FILE__
	 * being set to the full path of the current file.
	 *
	 * @todo Test
	 */
	string staticsGet(string const &localPath);
}


#endif
