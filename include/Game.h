#ifndef __ENGINE__GAME__ 
#define __ENGINE_GAME__

#include <string>
#include "sdl_log.h"
#include "log.h"
#include "sdl2include.h"

namespace engine{
    static const std::string DEFAULT_GAME_NAME = "Jogo TAC";
    static const std::pair<int, int> DEFAULT_WINDOW_SIZE(640, 480);
}

class Game{
public:
    enum class State{
            created,
            init,
            main_loop,
            exit_loop,
            paused,
            quit
    };
    static Game instance;

    void set_properties(std::string name, 
                        std::pair<int, int> window_size, 
                        unsigned int fps=60);
    void run();
    void set_background_color(int r, int g, int b, int a);

    inline void set_state(Game::State state){ g_state = state; }
    inline std::pair<int, int> window_size() { return g_window_size; }
    inline SDL_Renderer * canvas() { return g_canvas; }
    inline unsigned int elapsed_time() { return g_elapsed_time; }
    inline double elapsed_time_seconds() { return g_elapsed_time/ 1000.0; } 
    
private:
        Game(): g_name(engine::DEFAULT_GAME_NAME), g_window_size(engine::DEFAULT_WINDOW_SIZE),
                g_state(State::created), g_background_color({0xff, 0xff, 0xff, 0xff}) {}
        
        std::string             g_name;
        std::pair<int, int>     g_window_size;
        unsigned int            g_fps;
        State                   g_state;

        SDL_Window *            g_window;
        SDL_Renderer *          g_canvas;
        SDL_Color               g_background_color;
        SDL_Surface *           g_surface;
        SDL_Surface *           g_menu_background;
        Mix_Music  *            g_music;
        unsigned int            g_elapsed_time;

        bool create_window();
        bool destroy_window();
        bool load_media();
};

#endif