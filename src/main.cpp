#include <iostream>
#include <fstream>
#include "system.h"



int main(int argc, char **argv)
{
    Renderer ren(argv[1], WIDTH, WIDTH, 1200, 1200);
    System sys(argv[1]);
    SlimeMold r1;

    auto a = SDL_GetTicks();
    auto b = SDL_GetTicks();


    while (1)
    {
        a = SDL_GetTicks();
        auto delta = a - b;

        // if (delta > 1000.0f / 120.0f)
        {
            ren.beginFrame();

            sys.draw(&r1, ren);
            sys.tick(&r1);

            ren.endFrame();
            b = SDL_GetTicks();
        }
    }

    return 0;
}
