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

#ifndef EDOGINE_TIME_HPP
#define EDOGINE_TIME_HPP

#include <Edogine/Config.hpp>

namespace ed {

class EDOGINE_API Time {
public:
    Time();

    float asSeconds() const;
    int32_t asMilliseconds() const;
    int64_t asMicroseconds() const;
    int64_t asNanoseconds() const;

    // Comparison operators
    bool operator ==(const Time& other) const;
    bool operator !=(const Time& other) const;
    bool operator <(const Time& other) const;
    bool operator >(const Time& other) const;
    bool operator <=(const Time& other) const;
    bool operator >=(const Time& other) const;

    // Assignment operators
    Time& operator +=(const Time& right);
    Time& operator -=(const Time& right);
    Time& operator *=(float right);
    Time& operator *=(int64_t right);
    Time& operator /=(float right);
    Time& operator /=(int64_t right);

    // Right Arithmetic operators
    Time operator -() const;
    Time operator +(const Time& right) const;
    Time operator -(const Time& right) const;
    Time operator *(float right) const;
    Time operator *(int64_t right) const;
    Time operator /(float right) const;
    Time operator /(int64_t right) const;

private:
    explicit Time(int64_t nanoseconds);

    friend EDOGINE_API Time nanoseconds(int64_t value);
    friend EDOGINE_API Time microseconds(int64_t value);
    friend EDOGINE_API Time milliseconds(int32_t value);
    friend EDOGINE_API Time seconds(float value);

    friend EDOGINE_API Time operator *(float left, const Time& right);
    friend EDOGINE_API Time operator *(int64_t left, const Time& right);

public:
    static const Time Zero;

private:
    int64_t m_nanoseconds;
};

EDOGINE_API Time nanoseconds(int64_t value);
EDOGINE_API Time microseconds(int64_t value);
EDOGINE_API Time milliseconds(int32_t value);
EDOGINE_API Time seconds(float value);

// Left Arithmetic operators
EDOGINE_API Time operator *(float left, const Time& right);
EDOGINE_API Time operator *(int64_t left, const Time& right);

}  // namespace ed

#endif  // EDOGINE_TIME_HPP