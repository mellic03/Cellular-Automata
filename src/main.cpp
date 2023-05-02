#include <iostream>

#include "system.h"


int main(int argc, char **argv)
{
    Renderer ren;

    auto a = SDL_GetTicks();
    auto b = SDL_GetTicks();

    while (1)
    {
        a = SDL_GetTicks();
        auto delta = a - b;

        if (delta > 1000.0/60.0)
        {
            ren.beginFrame();


            ren.endFrame();
            b = SDL_GetTicks();
        }
    }

    return 0;
}