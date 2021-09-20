##define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "Face.h"
#include <string>
#include <SDL_include.h> 


Face::Face(GameObject& associated) : Component(associated){
    hitpoints = 30;
}

Face::Damage(int damage){
    hitpoints-= damage;

    if(hitpoints <= 0){
        associated->RequestDelete();
    }
}

Face::Update(float dt){

}


Face::Render(){

}


Face::Is(){
    if(type == "Face"){
        return true;
    }
    return false;
}