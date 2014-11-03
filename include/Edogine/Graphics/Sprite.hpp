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

#ifndef EDOGINE_SPRITE_HPP
#define EDOGINE_SPRITE_HPP

#include <SDL2/SDL.h>

#include <Edogine/Config.hpp>
#include <Edogine/System/Vector2.hpp>

namespace ed {

class EDOGINE_API Sprite {
public:
    Sprite();
    Sprite(SDL_Texture* texture);
    Sprite(SDL_Texture* texture, const SDL_Rect& texture_rect);
    virtual ~Sprite();

    void setTexture(SDL_Texture* texture);

    void setTextureRect(const SDL_Rect& texture_rect);

    void setOrigin(const ed::Vector2i& origin);

    void setPosition(float x_pos, float y_pos);
    void setPosition(const ed::Vector2f& position);

    void move(float dx, float dy);
    void move(const ed::Vector2f& offset);

    void setRotation(double angle);
    void rotate(double angle);

    void setFlip(bool x, bool y);

    void draw(SDL_Renderer* renderer);

private:
    SDL_Texture* m_texture;
    SDL_Rect m_texture_rect;
    SDL_Rect m_dest_rect;

    SDL_Point m_origin;
    ed::Vector2f m_position;
    SDL_RendererFlip m_flip;
    ed::Vector2f m_scale;
    double m_rotation;
};

}  // namespace ed

#endif  // EDOGINE_SPRITE_HPP