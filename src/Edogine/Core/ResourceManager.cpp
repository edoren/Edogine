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

#include <Edogine/Core/ResourceManager.hpp>

#include <Edogine/Core/GameEngine.hpp>

namespace ed {

ResourceManager& ResourceManager::instance() {
    static std::unique_ptr<ResourceManager> instance(new ResourceManager);
    return *instance;
}

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {
    for (auto pair : m_texture_hash) {
        SDL_DestroyTexture(pair.second);
    }
}

SDL_Texture* ResourceManager::loadTexture(SDL_Renderer* renderer, const std::string& file) {
    if (m_texture_hash.find(file) != m_texture_hash.end())
        return m_texture_hash[file];
    
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (surface == nullptr) {
        fprintf(stderr, "Could not open image: %s\n", SDL_GetError());
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
        return nullptr;
    }

    m_texture_hash[file] = texture;

    return texture;
}

SDL_Texture* ResourceManager::loadTexture(SDL_Renderer* renderer, SDL_Surface* surface,
                                          const std::string& key) {
    if (m_texture_hash.find(key) != m_texture_hash.end())
        return m_texture_hash[key];

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == nullptr) {
        fprintf(stderr, "Could not create texture: %s\n", SDL_GetError());
        return nullptr;
    }

    m_texture_hash[key] = texture;

    return texture;
}

SDL_Texture* ResourceManager::getTexture(const std::string& file) {
    if (m_texture_hash.find(file) != m_texture_hash.end()) {
        return m_texture_hash[file];
    } else {
        fprintf(stderr, "Can't find the texture %s.\n", file.c_str());
        return nullptr;
    }
}

void ResourceManager::freeTexture(const std::string& file) {
    auto iter = m_texture_hash.find(file);
    if (iter != m_texture_hash.end()) {
        SDL_DestroyTexture(iter->second);
        m_texture_hash.erase(iter);
    } else {
        fprintf(stderr, "Can't find the texture %s.\n", file.c_str());
    }
}

}  // namespace ed
