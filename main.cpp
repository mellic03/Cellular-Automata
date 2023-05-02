#include <iostream>

#include "C---Software-Rasterizer/renderer.h"

int main(int argc, char **argv)
{
    Renderer ren;
    Model m1;

    auto a = SDL_GetTicks();
    auto b = SDL_GetTicks();

    m1.transform().rotate(vec3(0.0f, 0.0f, 0.785398f));

    while (1)
    {
        a = SDL_GetTicks();
        auto delta = a - b;

        if (delta > 1000.0/60.0)
        {
            ren.beginFrame();

            ren.draw(m1);
            // m1.transform().rotate(vec3(0.0f, 0.0f, 0.007f));

            ren.endFrame();
            b = SDL_GetTicks();
        }
    }

    return 0;
}