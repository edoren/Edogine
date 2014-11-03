///////////////////////////////////////////////////////////////////////////////
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Manuel Sabogal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef EDOGINE_CONFIG_HPP
#define EDOGINE_CONFIG_HPP

#include <cstdint>

#ifndef EDOGINE_STATIC
	#ifdef _WIN32
	    #ifdef EDOGINE_EXPORTS
	        #define EDOGINE_API __declspec(dllexport)
	    #else
	        #define EDOGINE_API __declspec(dllimport)
	    #endif  // EDOGINE_EXPORTS

	    #ifdef _MSC_VER
	        #pragma warning(disable : 4251)
	    #endif  // _MSC_VER
	#else
	    #define EDOGINE_API
	#endif  // _WIN32
#else
	#define EDOGINE_API
#endif  // EDOGINE_STATIC

#endif  // EDOGINE_CONFIG_HPP