#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE


#include "Game.h"
#include <SDL_include.h>
#include <string>

using namespace engine;


Sprite::Sprite(){
    texture = nullptr;
}


Sprite::Sprite(std::string file){
    texture = nullptr;
    Open(file.c_str());
}


Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}


void Sprite::Open(std::string file){
    int w = GetWidth();
    int h = GetWidth();

    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(engine::Game::GetInstance().GetRenderer(),file.c_str());
    if(texture == nullptr){
        SDL_GetError();
        return;
    }

    if(!SDL_QueryTexture(texture, nullptr, nullptr, &w, &h)){
        SDL_GetError();
        return;
    }
    
    SDL_RenderSetClipRect(engine::Game::GetInstance().GetRenderer(), &clipRect);
}


void Sprite::SetClip(int x, int y, int h, int w){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.h = h;
    clipRect.w = w;
}


void Sprite::Render(int x, int y){
    SDL_Rect dst;

    dst.x = x;
    dst.y = y;
    dst.h = clipRect.h;
    dst.w = clipRect.w;

    SDL_RenderCopy(engine::Game::GetInstance().GetRenderer(), texture, &clipRect, &dst);
}


int Sprite::GetHeight(){
    return height;
}


int Sprite::GetWidth(){
    return width;
}


bool Sprite::IsOpen(){
    if(texture != nullptr){
        return true;
    }
    return false;
}
