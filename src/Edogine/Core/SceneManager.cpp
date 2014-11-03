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

#include <Edogine/Core/SceneManager.hpp>

#include <cassert>

namespace ed {

SceneManager::SceneManager(Context& context) : m_context(&context) {
}

void SceneManager::pushScene(GameScene::ID id) {
    auto found = m_factories.find(id);
    assert(found != m_factories.end());

    m_scenes.emplace_back(found->second());
}

void SceneManager::popScene() {
    m_scenes.pop_back();
}

void SceneManager::changeScene(GameScene::ID id) {
    m_scenes.pop_back();
    this->pushScene(id);
}

void SceneManager::clearScenes() {
    m_scenes.clear();
}

void SceneManager::handleInput(SDL_Event* event) {
    if (m_scenes.empty()) return;

    m_scenes.back()->handleInput(event);
}

void SceneManager::update(ed::Time dt) {
    for (auto& state : m_scenes) {
        state->update(dt);
    }
}

void SceneManager::draw() {
    for (auto& state : m_scenes) {
        state->draw();
    }
}

bool SceneManager::empty() {
    return m_scenes.empty();
}

}  // namespace ed
