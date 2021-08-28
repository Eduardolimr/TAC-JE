#include <SDL.h>
#include <stdio.h>
#include "Game.h"

using namespace engine;

int main( int argc, char* args[] ) {
    Game::instance.run();

    return 0;
}