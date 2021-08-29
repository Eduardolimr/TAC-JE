#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "Game.h"
#include <string>
#include <SDL_include.h> 

using namespace engine;


Game& Game::GetInstance() {
    if(instance != nullptr){
        return *instance;
    }
    instance = new Game();
    return *instance;
}

Game::Game(){
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        SDL_GetError();
    }

    if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
        SDL_GetError();
    }

    if(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)){
        SDL_GetError();
    }

    window = SDL_CreateWindow(engine::DEFAULT_GAME_NAME.c_str(), 
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 
                              engine::DEFAULT_WIDTH, 
                              engine::DEFAULT_HEIGHT, 
                              0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


Game::Game(std::string title, int width, int height){
    if(instance != nullptr){
        return;
    }
    instance = this;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
        SDL_GetError();
    }

    if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
        SDL_GetError();
    }

    if(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)){
        SDL_GetError();
    }

    window = SDL_CreateWindow(title.c_str(), 
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 
                              width, 
                              height, 
                              0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


Game::~Game(){
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    
    SDL_DestroyWindow(window);
    window = nullptr;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


State& Game::GetState(){
    return *state;
}


SDL_Renderer* Game::GetRenderer(){
    return renderer;
}



void Game::run(){
    while(!state->QuitRequested()){
        state->Update();
        state->Render();

        SDL_RenderPresent(renderer);
        SDL_Delay(33);

    }
}