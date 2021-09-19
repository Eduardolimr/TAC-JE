#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"
#include <vector>


class State{
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void AddObject(int mouseX, int mouseY);
private:
    Sprite bg;
    Music music;
    bool quitRequested;

    std::vector<std::unique_ptr<GameObject>> objectArray;
};