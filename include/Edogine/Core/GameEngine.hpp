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

#ifndef EDOGINE_GAMEENGINE_HPP
#define EDOGINE_GAMEENGINE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <Edogine/Config.hpp>
#include <Edogine/System/Clock.hpp>
#include <Edogine/Core/GameScene.hpp>
#include <Edogine/Core/SceneManager.hpp>
#include <Edogine/Core/ResourceManager.hpp>

namespace ed {

enum InitFlags : uint8_t {
    EDOGINE_INIT_GRAPHICS = 0x1,
    EDOGINE_INIT_AUDIO = 0x2,
    EDOGINE_INIT_EVERYTHING = 0xFF
};

inline InitFlags operator|(InitFlags a, InitFlags b) {
    return static_cast<InitFlags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline InitFlags operator&(InitFlags a, InitFlags b) {
    return static_cast<InitFlags>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

extern EDOGINE_API int Init(InitFlags flags);
extern EDOGINE_API void Quit();

class EDOGINE_API GameEngine {
public:
    GameEngine(SDL_Renderer* renderer);
    ~GameEngine();
    
    void run();
    bool isRunning();

    // States must be registered before run the engine
    template <typename T>
    void registerScene(GameScene::ID id);

    void setInitialScene(GameScene::ID id);

private:
    void handleInput();
    void render();

private:
    Context m_context;
    ed::Clock m_frameclock;
    bool m_running;
};

template <typename T>
inline void GameEngine::registerScene(GameScene::ID id) {
    m_context.scenes->registerScene<T>(id);
}

}  // namespace ed

#endif  // EDOGINE_GAMEENGINE_HPP
