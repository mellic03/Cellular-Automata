#include <iostream>

#include "system.h"


int main(int argc, char **argv)
{
    Renderer ren(WIDTH, WIDTH, 1200, 1200);
    System sys;
    SlimeMold r1;

    auto a = SDL_GetTicks();
    auto b = SDL_GetTicks();

    while (1)
    {
        a = SDL_GetTicks();
        auto delta = a - b;

        // if (delta > 1000.0/60.0)
        {
            ren.beginFrame();

            sys.tick(&r1);
            sys.draw(&r1, ren);

            ren.endFrame();
            b = SDL_GetTicks();
        }
    }

    return 0;
}