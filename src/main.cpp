#include <iostream>
#include <vector>

#include "application.h"

class Game : public Eternal::Application {
        public:
            Game() {}
            ~Game() {}

            void OnInitialize() override {

            }

            void OnUpdate() override {

            }

            void OnDraw() override {

            }
        private:
};

int main(int argc, char *args[]) {

    Game myGame;
    myGame.Start(0, 0, 640, 480);

    return 0;
}
