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

#include <Edogine/System/Vector2.hpp>

namespace ed {

template <typename T>
inline Vector2<T>::Vector2() : x(0), y(0) {
}

template <typename T>
inline Vector2<T>::Vector2(T x, T y) : x(x), y(y) {
}

template <typename T>
template <typename T2>
inline Vector2<T>::Vector2(const Vector2<T2>& other)
      : x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)) {
}

// Vector operations
template <typename T>
inline double Vector2<T>::dot(const Vector2<T>& other) const {
    return static_cast<double>(x * other.x + y * other.y);
}

template <typename T>
inline double Vector2<T>::cross(const Vector2<T>& other) const {
    return static_cast<double>(x * other.y - y * other.x);
}

template <typename T>
inline double Vector2<T>::length() const {
    return sqrt(static_cast<double>(x * x + y * y));
}

template <typename T>
inline Vector2<float> Vector2<T>::normalize() const {
    double length = this->length();
    return Vector2f(static_cast<float>(x / length), static_cast<float>(y / length));
}

// Arithmetic operators
template <typename T>
inline Vector2<T> operator-(const Vector2<T>& a) {
    return Vector2<T>(-a.x, -a.y);
}

template <typename T>
inline Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>(a.x + b.x, a.y + b.y);
}

template <typename T>
inline Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b) {
    return Vector2<T>(a.x - b.x, a.y - b.y);
}

template <typename T>
inline Vector2<T> operator*(const Vector2<T>& a, T b) {
    return Vector2<T>(a.x * b, a.y * b);
}

template <typename T>
inline Vector2<T> operator*(T a, const Vector2<T>& b) {
    return Vector2<T>(a * b.x, a * b.y);
}

template <typename T>
inline Vector2<T> operator/(const Vector2<T>& a, T b) {
    return Vector2<T>(a.x / b, a.y / b);
}

// Assignment operators
template <typename T>
inline Vector2<T>& operator+=(Vector2<T>& a, const Vector2<T>& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

template <typename T>
inline Vector2<T>& operator-=(Vector2<T>& a, const Vector2<T>& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

template <typename T>
inline Vector2<T>& operator*=(Vector2<T>& a, T b) {
    a.x *= b;
    a.y *= b;
    return a;
}

template <typename T>
inline Vector2<T>& operator/=(Vector2<T>& a, T b) {
    a.x /= b;
    a.y /= b;
    return a;
}

// Comparison operators
template <typename T>
inline bool operator ==(const Vector2<T>& a, const Vector2<T>& b) {
    return (a.x == b.x) && (a.y == b.y);
}

template <typename T>
inline bool operator !=(const Vector2<T>& a, const Vector2<T>& b) {
    return (a.x != b.x) || (a.y != b.y);
}

}  // namespace ed