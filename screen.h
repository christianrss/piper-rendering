#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

class Screen
{

public:

    static Screen* Instance();

public:

    bool Initialize();
    void ClearScreen();
    void Present();
    void Shutdown();

private:

    Screen();
    Screen(const Screen&);
    Screen& operator=(const Screen&);

private:

    SDL_Window* window;
    SDL_GLContext context;
};

#endif