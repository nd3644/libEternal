#include "timer.h"
#include <SDL2/SDL.h>

Eternal::Timer::Timer() {
    iTicks = 0;
    bTicking = false;
}

Eternal::Timer::~Timer() {
}

void Eternal::Timer::Start() {
    iTicks = SDL_GetTicks();
    bTicking = true;
}

void Eternal::Timer::Stop() {
    iTicks = 0;
    bTicking = false;
}

int Eternal::Timer::GetTicks() {
    return SDL_GetTicks() - iTicks;
}