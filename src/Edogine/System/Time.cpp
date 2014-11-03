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

#include <Edogine/System/Time.hpp>

namespace ed {

const Time Time::Zero;

Time::Time() : m_nanoseconds(0) {
}

Time::Time(int64_t nanoseconds) : m_nanoseconds(nanoseconds) {
}

float Time::asSeconds() const {
    return m_nanoseconds / 1000000000.f;
}

int32_t Time::asMilliseconds() const {
    return static_cast<int32_t>(m_nanoseconds / 1000000);
}

int64_t Time::asMicroseconds() const {
    return m_nanoseconds / 1000;
}

int64_t Time::asNanoseconds() const {
    return m_nanoseconds;
}

Time nanoseconds(int64_t value) {
    return Time(value);
}

Time microseconds(int64_t value) {
    return Time(value * 1000);
}

Time milliseconds(int32_t value) {
    return Time(static_cast<int64_t>(value) * 1000000);
}

Time seconds(float value) {
    return Time(static_cast<int64_t>(value * 1000000000));
}

// Comparison operators
bool Time::operator ==(const Time& other) const {
    return m_nanoseconds == other.m_nanoseconds;
}

bool Time::operator !=(const Time& other) const {
    return m_nanoseconds != other.m_nanoseconds;
}

bool Time::operator <(const Time& other) const {
    return m_nanoseconds < other.m_nanoseconds;
}

bool Time::operator >(const Time& other) const {
    return m_nanoseconds > other.m_nanoseconds;
}

bool Time::operator <=(const Time& other) const {
    return m_nanoseconds <= other.m_nanoseconds;
}

bool Time::operator >=(const Time& other) const {
    return m_nanoseconds >= other.m_nanoseconds;
}

// Right Arithmetic operators
Time Time::operator -() const {
    return Time(-m_nanoseconds);
}

Time Time::operator +(const Time& right) const {
    return Time(m_nanoseconds + right.m_nanoseconds);
}

Time Time::operator -(const Time& right) const {
    return Time(m_nanoseconds - right.m_nanoseconds);
}

Time Time::operator *(float right) const {
    return Time(static_cast<int64_t>(m_nanoseconds * right));
}

Time Time::operator *(int64_t right) const {
    return Time(m_nanoseconds * right);
}

Time Time::operator /(float right) const {
    return Time(static_cast<int64_t>(m_nanoseconds / right));
}

Time Time::operator /(int64_t right) const {
    return Time(m_nanoseconds / right);  
}

// Left Arithmetic operators
Time operator *(float left, const Time& right) {
    return Time(static_cast<int64_t>(left * right.m_nanoseconds));
}

Time operator *(int64_t left, const Time& right) {
    return Time(left * right.m_nanoseconds);
}

// Assignment operators
Time& Time::operator +=(const Time& other) {
    m_nanoseconds += other.m_nanoseconds;
    return *this;
}

Time& Time::operator -=(const Time& other) {
    m_nanoseconds = m_nanoseconds - other.m_nanoseconds;
    return *this;
}

Time& Time::operator *=(float other) {
    m_nanoseconds = static_cast<int64_t>(m_nanoseconds * other);
    return *this;
}

Time& Time::operator *=(int64_t other) {
    m_nanoseconds *= other;
    return *this;
}

Time& Time::operator /=(float other) {
    m_nanoseconds = static_cast<int64_t>(m_nanoseconds / other);
    return *this;
}

Time& Time::operator /=(int64_t other) {
    m_nanoseconds /= other;
    return *this;
}

}  // namespace ed