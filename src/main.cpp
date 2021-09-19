#include <stdio.h>
#include "Game.h"

using namespace engine;

int main( int argc, char** argv) {
    Game& g = g.GetInstance(); 
    g.run();

    return 0;
}