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

#include <Edogine/Core/GameEngine.hpp>

namespace ed {

int Init(InitFlags flags) {
    if (flags & EDOGINE_INIT_GRAPHICS) {
        int errcode;
        errcode = SDL_Init(SDL_INIT_EVERYTHING);
        if (errcode != 0) return errcode;

        errcode = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
        if (errcode != 0) return errcode;
    }
    return 0;
}

void Quit() {
    SDL_Quit();
    IMG_Quit();
}

GameEngine::GameEngine(SDL_Renderer* renderer) : m_running(false), m_frameclock(false) {
    m_context.renderer = renderer;
    m_context.scenes = new SceneManager(m_context);
    m_context.resources = &ResourceManager::instance();
}

GameEngine::~GameEngine() {
    delete m_context.scenes;
}

void GameEngine::run() {
    m_running = true;
    m_frameclock.resume();

#ifndef NDEBUG
    ed::Clock fpsclock;
    uint32_t cont = 0;
#endif

    while (m_running) {
#ifndef NDEBUG
        if (fpsclock.getElapsed().asSeconds() >= 1.f) {
            fprintf(stdout, "FPS %u\n", cont);
            cont = 0;
            fpsclock.restart();
        }
        cont++;
#endif
        this->handleInput();
        this->render();
    };
}


bool GameEngine::isRunning() {
    return m_running;
}

void GameEngine::setInitialScene(GameScene::ID id) {
    m_context.scenes->pushScene(id);
}

void GameEngine::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            m_running = false;
        }
        m_context.scenes->handleInput(&event);
    }
}

void GameEngine::render() {
    SDL_RenderClear(m_context.renderer);

    m_context.scenes->update(m_frameclock.getElapsed());
    m_frameclock.restart();
    m_context.scenes->draw();

    SDL_RenderPresent(m_context.renderer);
}

}  // namespace ed
