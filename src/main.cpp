#include <iostream>
#include <vector>

#include "application.h"
#include "audio_track.h"

#include "font.h"

#include <ebmp.h>

class Game : public Eternal::Application {
        public:
            Game() {}
            ~Game() {}

            Eternal::Sprite mySprite;
            Eternal::Bmp myBmp;

            void OnInitialize() override {
                pos.w = 128;
                pos.h = 128;
                myFont.Load("data/hello");
                myBmp.Load("data/kawaii_alpha.bmp");
                mySprite.FromData(myBmp.GetPixels(), myBmp.GetWidth(), myBmp.GetHeight(), myBmp.GetBPP());
                std::cout << "bmp err: " << myBmp.GetError() << std::endl;
            }

            void OnUpdate() override {
                pos.x += 1.0f;
            }

            void OnDraw() override {
                Eternal::Rect p(0,0,myBmp.GetWidth(),myBmp.GetHeight()), c(0,0,myBmp.GetWidth(),myBmp.GetHeight());
                mySprite.Draw(p,c);
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
