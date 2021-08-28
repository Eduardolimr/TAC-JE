#include <SDL.h>
#include <stdio.h>
#include "src/Game.h"

using namespace engine;

int main( int argc, char* args[] ) {
    Game::instance.run();

    return 0;
}