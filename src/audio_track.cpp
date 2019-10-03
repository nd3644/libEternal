#include "audio_track.h"

Eternal::AudioTrack::AudioTrack() {
    myMusic = nullptr;
}

Eternal::AudioTrack::~AudioTrack() {
    Cleanup();
}

void Eternal::AudioTrack::Load(std::string sfilename) {
    Cleanup();
    myMusic = Mix_LoadMUS(sfilename.c_str());
}

void Eternal::AudioTrack::Cleanup() {
    if(myMusic != nullptr) {
        Mix_FreeMusic(myMusic);
        myMusic = nullptr;
    }
}

void Eternal::AudioTrack::Play(int count) {
    Mix_PlayMusic(myMusic, count);
}

void Eternal::AudioTrack::Pause() {
    Mix_PauseMusic();
}

void Eternal::AudioTrack::Stop() {
    Mix_HaltMusic();
}