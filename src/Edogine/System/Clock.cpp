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

#include <Edogine/System/Clock.hpp>

#include <chrono>

namespace ed {

Clock::Clock() :
    m_running(true),
    m_startTime(this->getActualTime()),
    m_pauseTime(m_startTime),
    m_timeBuffer(ed::Time::Zero) {
}

Clock::Clock(bool running) :
    m_running(running),
    m_startTime(this->getActualTime()),
    m_pauseTime(m_startTime),
    m_timeBuffer(ed::Time::Zero) {
}

ed::Time Clock::getElapsed() const {
    if (m_running)
        return this->getActualTime() - m_startTime - m_timeBuffer;
    else
        return m_pauseTime - m_startTime - m_timeBuffer;
}

ed::Time Clock::getActualTime() const {
    auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto now_nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now);
    return ed::nanoseconds(now_nanoseconds.count());
}

void Clock::stop() {
    this->restart();
    m_running = false;
}

void Clock::pause() {
    if (m_running) {
        m_pauseTime = this->getActualTime();
        m_running = false;
    }
}

void Clock::resume() {
    if (!m_running) {
        m_timeBuffer += this->getActualTime() - m_pauseTime;
        m_running = true;
    }
}

void Clock::restart() {
    ed::Time now = this->getActualTime();
    m_startTime = now;
    m_pauseTime = now;
    m_timeBuffer = ed::Time::Zero;
}

}  // namespace ed