#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include "Sound.h"
#include <SDL_include.h>
#include <string>


Sound::Sound : (GameObject& associated): Component(associated){
    chunk = nullptr;
}


Sound::Sound(GameObject& associated, std::string file): Component(associated){
    Sound(associated);
    Open(file.c_str());
}


Sound::~Sound(){
    Stop(9);
    Mix_FreeChunk(chunk);
}


void Sound::Play(int times){
    if(chunk == nullptr){
        SDL_GetError();
        return;
    }
    Mix_PlayChannel(-1, chunk, times);
}


void Sound::Stop(int msToStop){
    Mix_HaltChannel(msToStop);
}


void Sound::Open(std::string file){
    Mix_Chunk *cnk;

    cnk = Mix_LoadWAV(file.c_str());

    if(cnk == nullptr){
        printf("Error loading Sound %s\n", Mix_GetError());
    } else{
        chunk = chunk;
    }
}


bool Sound::IsOpen(){
    if(Sound == nullptr){
        return false;
    }
    return true;
}


