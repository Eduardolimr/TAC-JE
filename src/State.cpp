#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "State.h"


State::State(){
    quitRequested = false;
    bg = new Sprite();
    music = new Music();
}


void State::LoadAssets(){
    bg.Open('assets/img/ocean.png');
    music.Open('assets/audio/stateState.ogg');

    bg.SetClip(0, 0, 1024, 600);
    music.Play(-1);
}


void State::Update(){
    if(SDL_QuitRequested()){
        quitRequested = true;
    }
}


void State::Render(){

}


bool State::QuitRequested(){
    return quitRequested;
}