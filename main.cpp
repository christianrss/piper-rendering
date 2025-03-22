#include <iostream>
#include <SDL2/SDL.h>
#include "screen.h"

bool isAppRunning = true;

int main(int argc, char* argv[])
{
    Screen::Instance()->Initialize();

    while (isAppRunning)
    {
        Screen::Instance()->ClearScreen();
        Screen::Instance()->Present();
    }

    Screen::Instance()->Shutdown();

    return 0;
}