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
            }

            void OnUpdate() override {
                pos.x += 1.0f;

            }

            void OnDraw() override {
                Eternal::Quad q;
                q.FromRect(pos);

                myRenderer->SetColor(1,0,0,1);
                myRenderer->DrawQuad(q);
            }
        private:
            Eternal::Rect pos;
};


int main(int argc, char *args[]) {

    Game myGame;
    myGame.Start(0, 0, 640, 480);

    return 0;
}
