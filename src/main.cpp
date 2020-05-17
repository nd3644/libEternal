#include <iostream>
#include <vector>

#include "application.h"
#include "audio_track.h"

#include "font.h"

class Game : public Eternal::Application {
        public:
            Game() {}
            ~Game() {}

            Eternal::Sprite mySprite;

            void OnInitialize() override {
                pos.w = 128;
                pos.h = 128;
                myFont.Load("data/hello");
            }

            void OnUpdate() override {
                pos.x += 1.0f;
            }

            void OnDraw() override {

            }
        private:
            Eternal::Rect pos;
            Eternal::Font myFont;
            float fScale = 1;
            bool down = true;

            Eternal::AudioTrack t;
};


int main(int argc, char *args[]) {

    Game myGame;
    myGame.Start(0, 0, 640, 480);

    return 0;
}
