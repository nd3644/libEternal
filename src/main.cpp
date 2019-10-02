#include <iostream>
#include <vector>

#include "application.h"

class Game : public Eternal::Application {
        public:
            Game() {}
            ~Game() {}

            void OnInitialize() override {
                pos.w = 64;
                pos.h = 32;
                mySprite.Load("brick.bmp");
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


                        mySprite.Draw(p, c);
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
                    mySprite.Draw(p, c);
                }

                for(int x = 0;x < 128;x++) {
                    myRenderer->SetColor((float)x / 128.0f, 1, 1, 1);
                    myRenderer->PlotPoint(x,128);
                }
            }
        private:
            Eternal::Rect pos;
            Eternal::Sprite mySprite;
};


int main(int argc, char *args[]) {

    Game myGame;
    myGame.Start(0, 0, 640, 480);

    return 0;
}
