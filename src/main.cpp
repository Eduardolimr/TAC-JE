#include <stdio.h>
#include "Game.h"

using namespace engine;

int main( int argc, char** argv) {
    Game::instance.run();

    return 0;
}