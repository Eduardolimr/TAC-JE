#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "GameObject.h"
#include <string>


class Sound : public Component{
public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound();

    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);

    void Update(float dt);
    void Is(std::string type);
    bool IsOpen();
private:
    Mix_Chunk * chunk;
    int channel;
};
