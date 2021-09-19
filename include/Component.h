#define INCLUDE_SDL

#include <string>
#include <SDL_include.h>
#include "GameObject.h"


class GameObject;

class Component{
public:
    Component(GameObject& associated);
    virtual ~Component();.
    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(string type);

protected:
    GameObject& associated;
};