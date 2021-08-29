#include "Sprite.h"
#include "Music.h"

class State{
public:
    State();
    bool QuitRequested();
    void LoadAssets();
    void Update();
    void Render();
private:
    Sprite bg;
    Music music;
    bool quitRequested;
};