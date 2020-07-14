#include <iostream>
#include <vector>

#include "application.h"
#include "audio_track.h"
#include "font.h"


#include "gui_panel.h"
#include "textbox.h"

#include <algorithm>

const int WINDOW_W = 1024;
const int WINDOW_H = 768;

Eternal::Font myFont;

class Diag : public Eternal::PanelUI {
    public:
        Diag() : PanelUI(WINDOW_W - 300,64, 256, 256) {
            myBox.SetGeometry(4, 4 + 32, 256 - 8, 12);
/*            for(int i = 0;i < 3;i++) {
                mySliders[i].SetGeometry(4 + 38, 12 + (i * 32), 256 - 12 - 38, 16);
                sliderLabels[i].Move(4, 16 + (i * 32));
                AddWidget(&sliderLabels[i]);
            }
            sliderLabels[0].SetText("red");
            sliderLabels[1].SetText("green");
            sliderLabels[2].SetText("blue");
            myButton.Move(4 , 4);
            AddWidget((Eternal::Widget*)&mySliders[0]);
            AddWidget((Eternal::Widget*)&mySliders[1]);
            AddWidget((Eternal::Widget*)&mySliders[2]);

            AddWidget((Eternal::Widget*)&myRadio);
            myRadio.SetText("radio");
            myRadio.SetGeometry(24, 200, 16, 16);

            AddWidget((Eternal::Widget*)&myButton);
            myButton.Move(GetGeometry().w - myButton.GetGeometry().w - 4, GetGeometry().h - myButton.GetGeometry().h - 4);
            myButton.SetText("close");*/
        }
        ~Diag() {} 

        void OnUpdate(Eternal::InputHandle *myInputHandle) {
            if(myInputHandle->IsKeyTap(Eternal::InputHandle::KEY_START)) {
                bShown = true;
            }
            if(!bShown) {
                return;
            }
            
            PanelUI::OnUpdate(myInputHandle);

            if(myButton.WasClicked()) {
                bShown = false;
                printf("clicked\n");
            }
        }
        
        void OnDraw(Eternal::Renderer *myRenderer) {
            PanelUI::OnDraw(myRenderer);
            if(!bShown) {
                return;
            }
        }
    private:
        Eternal::Button myButton;
        Eternal::Label sliderLabels[3];
        Eternal::Slider mySliders[3];
        Eternal::Textbox myBox;
        Eternal::Radiobox myRadio;
};

class Menu : public Eternal::PanelUI {
    public:
        Menu() : Eternal::PanelUI(200, 200, 256, 256) {
            button_OnePlay.SetGeometry(8, 8, 24, 24);
            button_OnePlay.SetText("Play computer");
            

            button_Hostgame.SetGeometry(8, 8 + 32, 48, 24);
            button_Hostgame.SetText("Host game");


            button_Joingame.SetGeometry(8, 8 + 64, 48, 24);
            button_Joingame.SetText("Join game");
            
            AddWidget((Eternal::Widget*)&button_OnePlay);
            AddWidget((Eternal::Widget*)&button_Hostgame);
            AddWidget((Eternal::Widget*)&button_Joingame);
        }
        void OnUpdate(Eternal::InputHandle *myInputHandle) {
            if(myInputHandle->IsKeyTap(Eternal::InputHandle::KEY_START)) {
                bShown = true;
            }
            if(!bShown) {
                return;
            }
            PanelUI::OnUpdate(myInputHandle);


        }
        
        void OnDraw(Eternal::Renderer *myRenderer) {
            if(!bShown) {
                return;
            }


            PanelUI::OnDraw(myRenderer);
        }
    private:
    Eternal::Button button_OnePlay,
                    button_Hostgame,
                    button_Joingame;
};

class OBB {
    public:

        void Set(float x, float y, float w, float h, float r) {
            v[0].x = -w / 2;    v[0].y = -h / 2;
            v[1].x = w / 2;    v[1].y = -h / 2;
            v[2].x = w / 2;    v[2].y = h / 2;
            v[3].x = -w / 2;    v[3].y = h / 2;
            
            float centreX = v[1].x - v[0].x / 2;
            float centreY = v[2].y - v[0].y / 2;
            for(int i = 0;i < 4;i++) {
                float tx = cos(r)*(v[i].x) - sin(r)*(v[i].y);
                float ty = sin(r)*(v[i].x) + cos(r)*(v[i].y);

                v[i].x = tx;
                v[i].y = ty;

                v[i].x += x;
                v[i].y += y;
            }
        }

        bool Collides(OBB &b, Eternal::Renderer *myRenderer) {
            Eternal::Vec2 axis[4];
            axis[0] = v[3] - v[0];
            axis[1] = v[1] - v[0];

            //

            axis[2] = b.v[3] - b.v[0];
            axis[3] = b.v[1] - b.v[0];

            axis[0].Normalize();
            axis[1].Normalize();
            axis[2].Normalize();
            axis[3].Normalize();

          
            Eternal::Vec2 start;
            Eternal::Vec2 end;



            bool axisCheck[4] = { false, false, false, false };
            int count = 0;
            for(int j = 0;j < 4;j++) {

                
                float proj[4];
                float proj_b[4];
                Eternal::Vec2 *minA = &v[0];
                Eternal::Vec2 *maxA = &v[0];

                Eternal::Vec2 *minB = &v[0];
                Eternal::Vec2 *maxB = &v[0];
                for(int i = 0;i < 4;i++) {
                    proj[i] = v[i].Dot(axis[j]);

                    if(proj[i] < minA->Dot(axis[j])) {
                        minA = &v[i];
                    }
                    if(proj[i] > maxA->Dot(axis[j])) {
                        maxA = &v[i];
                    }

                    proj_b[i] = v[i].Dot(axis[j]);

                    if(proj_b[i] < minB->Dot(axis[j])) {
                        minA = &v[i];
                    }
                    if(proj_b[i] > maxB->Dot(axis[j])) {
                        maxA = &v[i];
                    }
                }

                if(minA->Dot(axis[j]) > minB->Dot(axis[j])
                && minA->Dot(axis[j]) < maxB->Dot(axis[j])) {
                    count++;
                }
                else if(minB->Dot(axis[j]) > minA->Dot(axis[j])
                && minB->Dot(axis[j]) < maxA->Dot(axis[j])) {
                    count++;
                }
            }
            std::cout << "found " << count << " overlaps" << std::endl;

            if(axisCheck[0] == true && axisCheck[1]== true && axisCheck[2]== true && axisCheck[3]== true) {
                printf("found\n");
                return true;
            }

            return false;
        }

        void Draw(Eternal::Renderer *myRenderer) {
            myRenderer->DrawLine(v[0].x, v[0].y, v[1].x, v[1].y);
            myRenderer->DrawLine(v[1].x, v[1].y, v[2].x, v[2].y);
            myRenderer->DrawLine(v[2].x, v[2].y, v[3].x, v[3].y);
            myRenderer->DrawLine(v[3].x, v[3].y, v[0].x, v[0].y);

            myRenderer->DrawLine(v[0].x, v[0].y, v[2].x, v[2].y);
            myRenderer->DrawLine(v[1].x, v[1].y, v[3].x, v[3].y);

            myRenderer->PlotPoint(v[0].x, v[0].y);
            myRenderer->PlotPoint(v[1].x, v[1].y);
            myRenderer->PlotPoint(v[2].x, v[2].y);
            myRenderer->PlotPoint(v[3].x, v[3].y);
        }

        Eternal::Vec2 v[4];
};

class Game : public Eternal::Application {
        public:
            Game() {}
            ~Game() {
            }

            Eternal::Sprite mySprite;

            uint32_t ColorBuffer[640 * 480 * 3];

            void test_func();

            void OnInitialize() override {
                pos.w = 128;
                pos.h = 128;
                myFont.Load("data/hello");
            }

            void OnUpdate() override {
                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_ESCAPE)) {
                    exit(0);
                }
                pos.x += 1.0f;
                //diag.OnUpdate(myInputHandle);
                myMenu.OnUpdate(myInputHandle);
            }


            void OnDraw() override {
                //diag.OnDraw(myRenderer);

                OBB Box1;
                OBB Box2;

                static float r = 0;
                static float r2 = 0;

                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_SPACE)) {
                    r += 0.005f;
                }

                static float x1 = 100, y1 = 100;
                static float x2 = 220, y2 = 220;

                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_RIGHT)) {
                    x1++;
                }
                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_LEFT)) {
                    x1--;
                }

                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_UP)) {
                    y1--;
                }
                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_DOWN)) {
                    y1++;
                }

                Box1.Set(x1, y1, 32, 64, r);
                Box2.Set(x2, y2, 32, 64, r2);

                myRenderer->SetColor(0,1,0,1);
                Box1.Draw(myRenderer);
                myRenderer->SetColor(0,0,1,1);
                Box2.Draw(myRenderer);

                if(Box1.Collides(Box2, myRenderer)) {
                    printf("true\n");
                }

                myMenu.OnDraw(myRenderer);
            }
        private:
           // Diag diag;
           Menu myMenu;
            Eternal::Rect pos;
            float fScale = 1;
            bool down = true;

            Eternal::AudioTrack t;
};


int main(int argc, char *args[]) {

    Game myGame;
    myGame.Start(0, 0, WINDOW_W, WINDOW_H);

    return 0;
}
