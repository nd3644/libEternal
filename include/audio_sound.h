#ifndef AUDIO_SOUND_H
#define AUDIO_SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>

namespace Eternal {
    class Sound {
        public:
            Sound();
            ~Sound();

            void Load(std::string sfilename);
            void Play(int count);
            void Pause();
            void Stop();

        private:
            void Cleanup();

        private:
            Mix_Chunk *myChunk;
    };
}

#endif