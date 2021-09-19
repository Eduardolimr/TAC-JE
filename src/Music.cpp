#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include "Music.h"
#include <SDL_include.h>
#include <string>


Music::Music(){
    music = nullptr;
}


Music::Music(std::string file){
    music = nullptr;
    Open(file.c_str());
}


Music::~Music(){
    Stop(9);
    Mix_FreeMusic(music);
}


void Music::Play(int times){
    if(music == nullptr){
        SDL_GetError();
        return;
    }
    Mix_PlayMusic(music, times);
}


void Music::Stop(int msToStop){
    Mix_FadeOutMusic(msToStop);
}


void Music::Open(std::string file){
    Mix_Music *mus;

    mus = Mix_LoadMUS(file.c_str());

    if(mus == nullptr){
        printf("Error loading music %s\n", Mix_GetError());
    } else{
        music = mus;
    }
}


bool Music::IsOpen(){
    if(music == nullptr){
        return false;
    }
    return true;
}


