#define INCLUDE_SDL

#include <string>
#include <vector>
#include "Component.hpp"
#include "Rect.h"
#include "SDL_include.h"

class Face: public Component{
public:
    Face(GameObject& associated);
    void Damage(int damage);

    void Update(float dt);
    void Render();
    bool Is(std::string type);

private:
    int hitpoints;
};