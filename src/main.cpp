#include <iostream>
#include <vector>

#include "application.h"
#include "audio_track.h"
#include "font.h"

class Game : public Eternal::Application {
        public:
            Game() {}
            ~Game() {}

            void OnInitialize() override {
                pos.w = 64;
                pos.h = 32;
                myFont.Load("data/hello");
            }

            void OnUpdate() override {
                pos.x += 1.0f;

            }

            void OnDraw() override {
                Eternal::Quad q;
                q.FromRect(pos);

                myRenderer->SetColor(1,0,0,1);
                myRenderer->DrawQuad(q);


                Eternal::Rect p, c;
                p.x = p.y = 100;
                p.w = p.h = c.w = c.h = 16;

                for(int x = 0;x < 64;x += 16) {
                    for(int y = 0;y < 64;y += 16) {
                        c.x = x;
                        c.y = y ;
                        p.x = 100 + (x);
                        p.y = 100 + (y);

                    }
                }

                p.w = 1;
                p.h = 64;
                p.x = 200;
                p.y = 100;
                c.w = 1;
                c.h = 64;
                c.x = 0;
                c.y = 0;

                for(int x = 0;x < 64;x++) {
                    c.x++;
                    p.x++;
                }

                for(int x = 0;x < 128;x++) {
                    myRenderer->SetColor((float)x / 128.0f, 1.0f, 1.0f, 1.0f);
                    myRenderer->PlotPoint(x,128);
                }
                myFont.DrawString("abcdefghijklmnopqrstuvwxyz", 0.0f, 0.0f, 1.0f, 255.0f, 255.0f, 255.0f, 255.0f);
                myFont.DrawString("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 8.0f, 32.0f, 1.0f,0.0f, 0.0f, 255.0f, 150);
                myFont.DrawString("MARIO x00 TIME", 8.0f, 64.0f, 1.0f,255.0f, 0.0f, 255.0f, 100);
                if(down) {
                    fScale -= 0.001f;
                    if(fScale <= 0) {
                        down = false;
                    }
                }
                else {
                    fScale += 0.001f;
                    if(fScale >= 2) {
                        down = true;
                    }
                }
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
