#ifndef AUDIO_TRACK_H
#define AUDIO_TRACK_H

#include <SDL2/SDL_mixer.h>
#include <string>

namespace Eternal {
    class AudioTrack {
        public:
            AudioTrack();
            ~AudioTrack();

            void Load(std::string sfilename);
            void Play();
            void Pause();
            void Stop();
        private:

    };
}

#endif