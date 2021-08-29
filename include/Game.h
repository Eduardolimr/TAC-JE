#define INCLUDE_SDL

#include "State.h"
#include <string>
#include <SDL_include.h>

namespace engine{
    static const std::string DEFAULT_GAME_NAME = "Eduardo Lima Ribeiro 16/0049458";
    static const int DEFAULT_HEIGHT(600);
    static const int DEFAULT_WIDTH(1024);

    class Game{
    public:
        ~Game();

        SDL_Renderer * GetRenderer();
        State& GetState();

        static Game& GetInstance();
        void run();
    private:
        static Game *   instance;
        SDL_Window *    window;
        SDL_Renderer *  renderer;
        State *         state;

        Game();
        Game(std::string title, int width, int height);
    };
}