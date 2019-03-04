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
#include <cmath>
#include <stdexcept>
#include "Utils.hpp"

using string = std::string;


string gvt::collapsePath(string const &path) {
	throw std::runtime_error("Not implemented");
}

string gvt::dirpath(string const &path, bool collapse) {
	int length = path.size();
	auto i = path.crbegin();

	while (i != path.crend() && *i != '/') {
		i++;
		length--;
	}

	if (length > 0) {
		return path.substr(0, length);
	} else {
		throw std::domain_error{
			"String " + path + " does not contain any valid path value"
		};
	}
}

string gvt::staticsGet(string const &localPath) {
	return gvt::dirpath(__FILE__, false) + "../" + GVT_STATICS_DIR + localPath;
}


double gvt::rad2deg(double r) {
	return r * 180 / M_PI;
}

double deg2rad(double deg) {
	return deg * M_PI / 180.0;
}
