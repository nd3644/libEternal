#include "audio_sound.h"

Eternal::Sound::Sound() {
    myChunk = nullptr;
}

Eternal::Sound::~Sound() {
    Cleanup();
}

void Eternal::Sound::Cleanup() {
    if(myChunk != nullptr) {
        Mix_FreeChunk(myChunk);
        myChunk = nullptr;
    }
}

void Eternal::Sound::Load(std::string sfilename) {
    Cleanup();
    myChunk = Mix_LoadWAV(sfilename.c_str());
}

void Eternal::Sound::Play(int count) {
    Mix_PlayChannel(-1, myChunk, count);
}

void Eternal::Sound::Pause() {
}

void Eternal::Sound::Stop() {
}