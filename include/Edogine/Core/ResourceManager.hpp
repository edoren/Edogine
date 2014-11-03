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

#ifndef EDOGINE_RESOURCEMANAGER_HPP
#define EDOGINE_RESOURCEMANAGER_HPP

#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Edogine/Config.hpp>

namespace ed {

class EDOGINE_API ResourceManager {
public:
    ~ResourceManager();

    static ResourceManager& instance();

    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& file);
    SDL_Texture* loadTexture(SDL_Renderer* renderer, SDL_Surface* surface,
                             const std::string& key);
    SDL_Texture* getTexture(const std::string& file);
    void freeTexture(const std::string& file);

private:
    ResourceManager();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager& operator=(const ResourceManager& other) = delete;

private:
    std::unordered_map<std::string, SDL_Texture*> m_texture_hash;
};

}

#endif  // EDOGINE_RESOURCEMANAGER_HPP
