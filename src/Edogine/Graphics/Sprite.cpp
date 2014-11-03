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

#include <Edogine/Graphics/Sprite.hpp>

#include <cstdio>

namespace ed {

Sprite::Sprite()
      : m_texture(nullptr),
        m_texture_rect({ 0, 0, 0, 0 }),
        m_dest_rect({ 0, 0, 0, 0 }),
        m_origin({ 0, 0 }),
        m_position(0, 0),
        m_flip(SDL_FLIP_NONE),
        m_rotation(0.0) {
}

Sprite::Sprite(SDL_Texture* texture)
      : m_texture(texture),
        m_origin({ 0, 0 }),
        m_position(0, 0),
        m_flip(SDL_FLIP_NONE),
        m_rotation(0.0) {
    int texture_width = 0;
    int texture_height = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

    m_texture_rect.w = texture_width;
    m_texture_rect.h = texture_height;
    m_dest_rect.w = texture_width;
    m_dest_rect.h = texture_height;
}

Sprite::Sprite(SDL_Texture* texture, const SDL_Rect& texture_rect)
      : m_texture(texture),
        m_texture_rect(texture_rect),
        m_dest_rect({ 0, 0, m_texture_rect.w, m_texture_rect.h }),
        m_origin({ 0, 0 }),
        m_position(0, 0),
        m_flip(SDL_FLIP_NONE),
        m_rotation(0.0) {
}

Sprite::~Sprite() {
}

void Sprite::setTexture(SDL_Texture* texture) {
    if (m_texture == nullptr) {
        int texture_width = 0;
        int texture_height = 0;
        SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

        m_texture_rect.w = texture_width;
        m_texture_rect.h = texture_height;
        m_dest_rect.w = texture_width;
        m_dest_rect.h = texture_height;
    }

    m_texture = texture;
}

void Sprite::setTextureRect(const SDL_Rect& texture_rect) {
    m_texture_rect = texture_rect;
    m_dest_rect.w = texture_rect.w;
    m_dest_rect.h = texture_rect.h;
}


void Sprite::setOrigin(const ed::Vector2i& origin) {
    m_origin.x = origin.x;
    m_origin.y = origin.y;
    m_dest_rect.x = static_cast<int>(m_position.x) - m_origin.x;
    m_dest_rect.y = static_cast<int>(m_position.y) - m_origin.y;
};

void Sprite::setPosition(float x_pos, float y_pos) {
    m_position.x = x_pos;
    m_position.y = y_pos;
    m_dest_rect.x = static_cast<int>(m_position.x) - m_origin.x;
    m_dest_rect.y = static_cast<int>(m_position.y) - m_origin.y;
}

void Sprite::setPosition(const ed::Vector2f& position) {
    m_position = position;
    m_dest_rect.x = static_cast<int>(m_position.x) - m_origin.x;
    m_dest_rect.y = static_cast<int>(m_position.y) - m_origin.y;
}

void Sprite::move(float dx, float dy) {
    m_position.x += dx;
    m_position.y += dy;
    m_dest_rect.x = static_cast<int>(m_position.x) - m_origin.x;
    m_dest_rect.y = static_cast<int>(m_position.y) - m_origin.y;
}

void Sprite::move(const ed::Vector2f& offset) {
    m_position += offset;
    m_dest_rect.x = static_cast<int>(m_position.x) - m_origin.x;
    m_dest_rect.y = static_cast<int>(m_position.y) - m_origin.y;
}

void Sprite::setRotation(double angle) {
    m_rotation = angle;
}

void Sprite::rotate(double angle) {
    m_rotation += angle;
}

void Sprite::setFlip(bool x, bool y) {
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (x) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    if (y) flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
    m_flip = flip;
}

void Sprite::draw(SDL_Renderer* renderer) {
    SDL_RenderCopyEx(renderer, m_texture,
                     &m_texture_rect, &m_dest_rect,
                     m_rotation, &m_origin, m_flip);
}

}  // namespace ed
