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

#ifndef EDOGINE_SCENEMANAGER_HPP
#define EDOGINE_SCENEMANAGER_HPP

#include <map>
#include <vector>
#include <memory>
#include <functional>

#include <SDL2/SDL.h>

#include <Edogine/Config.hpp>
#include <Edogine/Core/Context.hpp>
#include <Edogine/Core/GameScene.hpp>
#include <Edogine/System/Time.hpp>

namespace ed {

class EDOGINE_API SceneManager {
public:
    SceneManager(Context& context);

    void pushScene(GameScene::ID id);
    void popScene();
    void changeScene(GameScene::ID id);
    void clearScenes();

    void handleInput(SDL_Event* event);
    void update(ed::Time dt);
    void draw();

    bool empty();

    // Scenes must be registered before push
    template <typename T>
    void registerScene(GameScene::ID id);

private:
    SceneManager(const SceneManager& other) = delete;
    SceneManager& operator=(const SceneManager& other) = delete;

private:
    Context* m_context;
    std::vector<std::unique_ptr<GameScene>> m_scenes;
    std::map<
        GameScene::ID,
        std::function<std::unique_ptr<GameScene>()>
    > m_factories;
};

}  // namespace ed

#include <Edogine/Core/SceneManager.inl>

#endif  // EDOGINE_SCENEMANAGER_HPP
