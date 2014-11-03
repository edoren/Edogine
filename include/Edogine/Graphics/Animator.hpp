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

#ifndef EDOGINE_ANIMATOR_HPP
#define EDOGINE_ANIMATOR_HPP

#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <cassert>

#include <SDL2/SDL.h>

#include <Edogine/Config.hpp>
#include <Edogine/System/Clock.hpp>
#include <Edogine/Graphics/Sprite.hpp>

namespace ed {

class EDOGINE_API Animator {
public:
    Animator();
    virtual ~Animator();

    explicit Animator(ed::Sprite* sprite);

    void setSprite(ed::Sprite* sprite);

    void addAnimation(const std::string& name,
                      const std::vector<SDL_Rect>& frames,
                      const ed::Time& time);

    void addAnimation(const std::string& name,
                      const std::vector<SDL_Rect>& frames,
                      const std::vector<ed::Time>& times);

    void setAnimation(const std::string& name);

    std::string getAnimationName() const;

    unsigned int getFrame() const;
    void setFrame(unsigned int frame_no);

    void nextFrame();
    void prevFrame();

    void update();  

private:
    ed::Sprite* m_sprite;
    ed::Clock animation_timer;
    std::size_t m_frameindex;

    std::unordered_map< 
        std::string,
        std::vector<std::pair<SDL_Rect, ed::Time>>
    > m_animation_hash;

    const std::string* m_currkey;
    std::vector<std::pair<SDL_Rect, ed::Time>>* m_curranimation;
};

}  // namespace ed

#endif  // EDOGINE_ANIMATOR_HPP