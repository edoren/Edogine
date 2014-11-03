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

#include <Edogine/Graphics/Animator.hpp>

namespace ed {

Animator::Animator()
      : m_sprite(nullptr),
        m_frameindex(0),
        m_animation_hash(),
        m_currkey(nullptr),
        m_curranimation(nullptr) {
}

Animator::Animator(ed::Sprite* sprite)
      : m_sprite(sprite),
        m_frameindex(0),
        m_animation_hash(),
        m_currkey(nullptr),
        m_curranimation(nullptr) {
}

Animator::~Animator() {
}

void Animator::setSprite(ed::Sprite* sprite) {
    m_sprite = sprite;
}

void Animator::addAnimation(const std::string& name,
                            const std::vector<SDL_Rect>& frames,
                            const ed::Time& time) {
    std::vector<std::pair<SDL_Rect, ed::Time>> vec;
    vec.reserve(frames.size());
    for (auto frame : frames) {
        vec.push_back(std::make_pair(frame, time));
    }
    m_animation_hash.emplace(name, std::move(vec));
}

void Animator::addAnimation(const std::string& name,
                            const std::vector<SDL_Rect>& frames,
                            const std::vector<ed::Time>& times) {
    if (frames.size() != times.size()) return;

    std::vector<std::pair<SDL_Rect, ed::Time>> vec;
    vec.reserve(frames.size());
    for (std::size_t i = 0; i < frames.size(); i++) {
        vec.push_back(std::make_pair(frames[i], times[i]));
    }
    m_animation_hash.emplace(name, std::move(vec));
}

void Animator::setAnimation(const std::string& name) {
    if (m_sprite == nullptr) return;
    if (m_currkey != nullptr && *m_currkey == name) {
        //fprintf(stdout, "Key aready found\n");
        return;
    }

    auto it = m_animation_hash.find(name);
    if (it != m_animation_hash.end()) {
        m_currkey = &(it->first);
        m_curranimation = &(it->second);
    } else {
        m_currkey = nullptr;
        m_curranimation = nullptr;
    }

    m_frameindex = 0;
    m_sprite->setTextureRect((*m_curranimation)[m_frameindex].first);
    animation_timer.restart();
}

std::string Animator::getAnimationName() const {
    if (m_currkey == nullptr) return std::string();
    return *m_currkey;
}

unsigned int Animator::getFrame() const {
    return m_frameindex;
};

void Animator::setFrame(unsigned int frame_no) {
    if (m_curranimation == nullptr) return;
    m_frameindex = frame_no % m_curranimation->size();
};

void Animator::nextFrame() {
    if (m_curranimation == nullptr) return;
    m_frameindex = (m_frameindex + 1) % m_curranimation->size();
}

void Animator::prevFrame() {
    if (m_curranimation == nullptr) return;
    m_frameindex = (m_frameindex - 1) % m_curranimation->size();
}

void Animator::update() {
    if (m_curranimation == nullptr || m_sprite == nullptr) return;
    if (animation_timer.getElapsed() >= (*m_curranimation)[m_frameindex].second) {
        m_frameindex = (m_frameindex + 1) % m_curranimation->size();
        m_sprite->setTextureRect((*m_curranimation)[m_frameindex].first);
        animation_timer.restart();
    }
}

}  // namespace ed