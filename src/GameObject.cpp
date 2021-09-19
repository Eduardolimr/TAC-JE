#define INCLUDE_SDL

#include <string>
#include <vector
#include <algorithm>
#include "GameObject.h"
#include "SDL_include.h"

GameObject::GameObject(){
    isDead = false;
}


GameObject::~GameObject(){
    for(vector<Component>::reverse_iterator i = components.rbegin(); i!= components.rend(); ++i){

    }
}


GameObject::Update(float dt){
    for(int i: components){
        components[i]->Update(dt);
    }
}



GameObject::Render(){
    for(int i: components){
        components[i]->Render();
    }
}


GameObject::IsDead(){
    return this.isDead;
}


GameObject::RequestDelete(){
    isDead = true;
}



GameObject::AddComponent(Component* cpt){
    components.insert(components.end(), cpt);
}



GameObject::RemoveComponent(Component* cpt){
    if(int index = std::find(components.begin(), components.end(), cpt) != components.end()){

    }
}