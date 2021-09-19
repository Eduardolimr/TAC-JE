#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "State.h"
#include <string>

State::State():bg(), music(){
    quitRequested = false;
}


void State::LoadAssets(){
    std::string str1, str2;
    str1 = ".././assets/img/ocean.jpg";
    str2 = ".././assets/audio/stageState.ogg";

    bg.Open(str1);
    bg.Render(0,0);
    music.Open(str2);
    music.Play();
}


void State::Update(float dt){
    if(SDL_QuitRequested()){
        quitRequested = true;
    }
}


void State::Render(){
    bg.Render(0,0);
}


bool State::QuitRequested(){
    return quitRequested;
}