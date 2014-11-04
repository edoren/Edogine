#include <iostream>

#include <SDL2/SDL.h>
#include <Edogine/Edogine.hpp>

enum Scenes : ed::GameScene::ID {
    SCENE_R,
    SCENE_G,
    SCENE_B,
};

class SceneR : public ed::GameScene {
public:
    ed::Sprite image;

    SceneR(ed::Context& context) : ed::GameScene(context) {
        SDL_Texture* text = context.resources->loadTexture(context.renderer, "scene1.png");
        image.setTexture(text);
    }

    void pause() {};
    void resume() {};

    void handleInput(SDL_Event* event) {
        if (event->type == SDL_KEYDOWN) {
            if (event->key.repeat == 0) {
                if (event->key.keysym.sym == SDLK_2) {
                    this->requestSceneChange(SCENE_G);
                    std::cout << "Scene changed to: SceneG." << std::endl;
                } else if (event->key.keysym.sym == SDLK_3) {
                    this->requestSceneChange(SCENE_B);
                    std::cout << "Scene changed to: SceneB." << std::endl;
                }
            }
        }
    };

    void update(ed::Time dt) {};

    void draw() {
        image.draw(context.renderer);
    };
};

class SceneG : public ed::GameScene {
public:
    ed::Sprite image;

    SceneG(ed::Context& context) : ed::GameScene(context) {
        SDL_Texture* text = context.resources->loadTexture(context.renderer, "scene2.png");
        image.setTexture(text);
    }

    void pause() {};
    void resume() {};

    void handleInput(SDL_Event* event) {
        if (event->type == SDL_KEYDOWN) {
            if (event->key.repeat == 0) {
                if (event->key.keysym.sym == SDLK_1) {
                    this->requestSceneChange(SCENE_R);
                    std::cout << "Scene changed to: SceneR." << std::endl;
                } else if (event->key.keysym.sym == SDLK_3) {
                    this->requestSceneChange(SCENE_B);
                    std::cout << "Scene changed to: SceneB." << std::endl;
                }
            }
        }
    };

    void update(ed::Time dt) {};

    void draw() {
        image.draw(context.renderer);
    };
};

class SceneB : public ed::GameScene {
public:
    ed::Sprite image;

    SceneB(ed::Context& context) : ed::GameScene(context) {
        SDL_Texture* text = context.resources->loadTexture(context.renderer, "scene3.png");
        image.setTexture(text);
    }

    void pause() {};
    void resume() {};

    void handleInput(SDL_Event* event) {
        if (event->type == SDL_KEYDOWN) {
            if (event->key.repeat == 0) {
                if (event->key.keysym.sym == SDLK_1) {
                    this->requestSceneChange(SCENE_R);
                    std::cout << "Scene changed to: SceneR." << std::endl;
                } else if (event->key.keysym.sym == SDLK_2) {
                    this->requestSceneChange(SCENE_G);
                    std::cout << "Scene changed to: SceneG." << std::endl;
                }
            }
        }
    };

    void update(ed::Time dt) {};

    void draw() {
        image.draw(context.renderer);
    };
};

int main(int argc, char* argv[]) {
    ed::Init(EDOGINE_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
        "Scene Examples",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        ed::Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
        ed::Quit();
        return 1;
    }

    ed::GameEngine game(renderer);

    game.registerScene<SceneR>(SCENE_R);
    game.registerScene<SceneG>(SCENE_G);
    game.registerScene<SceneB>(SCENE_B);

    std::cout << "Initial scene: SceneR" << std::endl;
    game.setInitialScene(SCENE_R);

    game.run();

    ed::Quit();

    return 0;
}