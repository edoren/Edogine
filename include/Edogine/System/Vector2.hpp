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

#ifndef EDOGINE_VECTOR2_HPP
#define EDOGINE_VECTOR2_HPP

#include <Edogine/Config.hpp>

#include <cmath>

namespace ed {

template <typename T>
class Vector2 {
public:
    Vector2();
    Vector2(T x, T y);

    template <typename T2>
    explicit Vector2(const Vector2<T2>& other);

    // Vector operations
    double dot(const Vector2<T>& other) const;
    double cross(const Vector2<T>& other) const;
    double length() const;
    Vector2<float> normalize() const;

    T x;
    T y;
};

// Arithmetic operators
template <typename T>
Vector2<T> operator-(const Vector2<T>& a);

template <typename T>
Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b);

template <typename T>
Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b);

template <typename T>
Vector2<T> operator*(const Vector2<T>& a, T b);

template <typename T>
Vector2<T> operator*(T a, const Vector2<T>& b);

template <typename T>
Vector2<T> operator/(const Vector2<T>& a, T b);

// Assignment operators
template <typename T>
Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b);

template <typename T>
Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b);

template <typename T>
Vector2<T>& operator*=(Vector2<T>& a, T b);

template <typename T>
Vector2<T>& operator/=(Vector2<T>& a, T b);

// Comparison operators
template <typename T>
bool operator ==(const Vector2<T>& a, const Vector2<T>& b);

template <typename T>
bool operator !=(const Vector2<T>& a, const Vector2<T>& b);

typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

}  // namespace ed

#include <Edogine/System/Vector2.inl>

#endif  // EDOGINE_VECTOR2_HPP