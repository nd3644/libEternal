#include "audio_sound.h"

Eternal::Sound::Sound() {
    myChunk = nullptr;
    iChosenChannel = -1;
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
    iChosenChannel = Mix_PlayChannel(-1, myChunk, count);
}

void Eternal::Sound::Pause() {
}

void Eternal::Sound::Stop() {
}

void Eternal::Sound::SetVolume(int i) {
    Mix_VolumeChunk(myChunk, i);
}

bool Eternal::Sound::IsPlaying() {
    if(iChosenChannel == -1) {
        return false;
    }
    if(Mix_Playing(iChosenChannel) && Mix_GetChunk(iChosenChannel) == myChunk) {
        return true;
    }
    return false;
}