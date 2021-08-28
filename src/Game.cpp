#include "Game.h"

using namespace engine;

Game Game::instance;

void Game::set_properties(std::string name, std::pair<int, int> window_size, unsigned int fps) {
    g_name = name;
    g_window_size = window_size;
    g_fps = fps;
    g_window = NULL;
    g_surface = NULL;
    g_canvas = NULL;
    g_menu_background = NULL;
    g_music = NULL;
}


bool setup_sdl(){
    INFO("Setup SDL");

    INFO("Init video and audio");
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        SDL_ERROR("SDL_Init");
        return false;
    }

    INFO("init image png");
    int img_flags = IMG_INIT_PNG;
    if(!(IMG_Init(img_flags) & img_flags)) {
        SDL_IMG_ERROR("IMG_Init");
        return false;
    }

    INFO("Init TTF");
    if(TTF_Init() == -1) {
        SDL_TTF_ERROR("TTF_Init");
        return false;
    }

    INFO("Open audio Mixer");
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_MIX_ERROR("Mix_OpenAudio");
        return false;
    }

    return true;
}


bool Game::create_window() {
    bool success;

    INFO("Create window (" << g_name << ", " << g_window_size.first << ", "
        << g_window_size.second << ")");
    
    INFO("Create window");
    g_window = SDL_CreateWindow(g_name.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                g_window_size.first,
                                g_window_size.second,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL){
        SDL_ERROR("SDL_CreateWindow");
        return false;
    }

    INFO("Create canvas");
    g_canvas = SDL_CreateRenderer(g_window,
                                  -1, // Render driver
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(g_canvas == NULL){
        SDL_ERROR("SDL_CreateRenderer");
        return false;
    }
    
    success = load_media();
    if(!success) { 
        SDL_ERROR("SDL_Load");
        return false;
    }

    SDL_SetRenderDrawColor(g_canvas,
                            g_background_color.r, g_background_color.b,
                            g_background_color.g, g_background_color.a);
    return true;


}


bool teardown_sdl(){
    INFO("Teardown SDL");

    INFO("Quit SDL Mix");
    Mix_Quit();

    INFO("Quit SDL TTF");
    TTF_Quit();

    INFO("Quit SDL IMG");
    IMG_Quit();

    INFO("Quit SDL");
    SDL_Quit();

    return true;
}


bool Game::destroy_window(){
    INFO("Destroy canvas");
    SDL_DestroyRenderer(g_canvas);
    g_canvas = NULL;

    INFO("Destroy window");
    SDL_DestroyWindow(g_window);
    g_window = NULL;

    return true;
}


void Game::run(){
    INFO("Game" << g_name << "Setup");

    g_state = State::init;

    if(setup_sdl() && create_window()){
        INFO("Start game loop");
        g_state = State::main_loop;

        double frame_time = 1000.0 / static_cast<double>(g_fps);

        while(g_state != State::exit_loop) {
            SDL_RenderClear(g_canvas);
            SDL_RenderPresent(g_canvas);
            //Apply the image
			SDL_BlitSurface( g_menu_background, NULL, g_surface, NULL);
			//Update the surface
			SDL_UpdateWindowSurface(g_window);
            if( Mix_PlayingMusic() == 0 ) {
				//Play the music
				Mix_PlayMusic(g_music, -1 );
			}

            // Syncing frames with desired fps
            if(frame_time > g_elapsed_time) {
                SDL_Delay(frame_time - g_elapsed_time);
            }

            SDL_Delay(10000);
            set_state(State::exit_loop);
        }

        INFO("Cleaning up resources");
    }

    INFO("Game shutdown");
    g_state = State::quit;
    destroy_window();
    teardown_sdl();
}

void Game::set_background_color(int r, int g, int b , int a) {
    g_background_color.r = r;
    g_background_color.g = g;
    g_background_color.b = b;
    g_background_color.a = a;

    if(g_canvas != NULL){
        SDL_SetRenderDrawColor(g_canvas,
                                g_background_color.r,
                                g_background_color.g,
                                g_background_color.b,
                                g_background_color.a);
    }
}

bool Game::load_media() {
    bool success = true;
	g_menu_background = IMG_Load( "assets/img/space.jpg" );
	if(g_menu_background == NULL ) {
		success = false;
	}
    g_music = Mix_LoadMUS("bensound_scifi.mp3");
	if(g_music == NULL)
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	return success;
}