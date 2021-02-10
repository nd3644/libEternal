#include <iostream>
#include <vector>

#include "application.h"
#include "audio_track.h"
#include "mesh.h"
#include "font.h"


#include "gui_panel.h"
#include "textbox.h"

#include <algorithm>

struct vec2_t {
	float x, y;
};

struct vec3_t {
	float x, y, z;
};

vec3_t cube_verts[8];
#define BUFFER_OFFSET(i) ((void*)(i))

void CompileArr();
std::vector<vec3_t>vertList;
std::vector<vec2_t>uvList;


void CompileArr() {

	uvList.clear();
	vertList.clear();

	auto tex2 = [](float x, float y) {
		vec2_t uv = { x, y };
		uvList.push_back(uv);
	};

	auto vert3 = [](float x, float y, float z) {
		vec3_t v = { x, y, z };
		vertList.push_back(v);
	};

	tex2(0, 0); vert3(cube_verts[0].x, cube_verts[0].y, cube_verts[0].z);
	tex2(1, 0); vert3(cube_verts[1].x, cube_verts[1].y, cube_verts[1].z);
	tex2(0, 1); vert3(cube_verts[3].x, cube_verts[3].y, cube_verts[3].z);

	tex2(0, 1); vert3(cube_verts[3].x, cube_verts[3].y, cube_verts[3].z);
	tex2(1, 0); vert3(cube_verts[1].x, cube_verts[1].y, cube_verts[1].z);
	tex2(1, 1); vert3(cube_verts[2].x, cube_verts[2].y, cube_verts[2].z);
	
	// back
	tex2(0, 0); vert3(cube_verts[0+4].x, cube_verts[0+4].y, cube_verts[0+4].z);
	tex2(1, 0); vert3(cube_verts[1+4].x, cube_verts[1+4].y, cube_verts[1+4].z);
	tex2(0, 1); vert3(cube_verts[3+4].x, cube_verts[3+4].y, cube_verts[3+4].z);

	tex2(0, 1); vert3(cube_verts[3+4].x, cube_verts[3+4].y, cube_verts[3+4].z);
	tex2(1, 0); vert3(cube_verts[1+4].x, cube_verts[1+4].y, cube_verts[1+4].z);
	tex2(1, 1); vert3(cube_verts[2+4].x, cube_verts[2+4].y, cube_verts[2+4].z);
	
	
	// top
	tex2(0, 0); vert3(cube_verts[0].x, cube_verts[0].y, cube_verts[0].z);
	tex2(0, 1); vert3(cube_verts[4].x, cube_verts[4].y, cube_verts[4].z);
	tex2(1, 1); vert3(cube_verts[5].x, cube_verts[5].y, cube_verts[5].z);

	tex2(1, 1); vert3(cube_verts[5].x, cube_verts[5].y, cube_verts[4].z);
	tex2(1, 0); vert3(cube_verts[1].x, cube_verts[1].y, cube_verts[1].z);
	tex2(0, 0); vert3(cube_verts[0].x, cube_verts[0].y, cube_verts[0].z);
	
	
	// bottom
	tex2(0, 0); vert3(cube_verts[3].x, cube_verts[3].y, cube_verts[3].z);
	tex2(0, 1); vert3(cube_verts[7].x, cube_verts[7].y, cube_verts[7].z);
	tex2(1, 1); vert3(cube_verts[6].x, cube_verts[6].y, cube_verts[6].z);

	tex2(1, 1); vert3(cube_verts[6].x, cube_verts[6].y, cube_verts[6].z);
	tex2(1, 0); vert3(cube_verts[2].x, cube_verts[2].y, cube_verts[2].z);
	tex2(0, 0); vert3(cube_verts[3].x, cube_verts[3].y, cube_verts[3].z);
	
	
	// left
	tex2(0, 0); vert3(cube_verts[0].x, cube_verts[0].y, cube_verts[0].z);
	tex2(1, 0); vert3(cube_verts[4].x, cube_verts[4].y, cube_verts[4].z);
	tex2(1, 1); vert3(cube_verts[7].x, cube_verts[7].y, cube_verts[7].z);
	
	tex2(0, 0); vert3(cube_verts[0].x, cube_verts[0].y, cube_verts[0].z);
	tex2(0, 1); vert3(cube_verts[3].x, cube_verts[3].y, cube_verts[3].z);
	tex2(1, 1); vert3(cube_verts[7].x, cube_verts[7].y, cube_verts[7].z);
	
	// right
	tex2(0, 0); vert3(cube_verts[1].x, cube_verts[1].y, cube_verts[1].z);
	tex2(1, 0); vert3(cube_verts[5].x, cube_verts[5].y, cube_verts[5].z);
	tex2(1, 1); vert3(cube_verts[6].x, cube_verts[6].y, cube_verts[6].z);
	
	tex2(0, 0); vert3(cube_verts[1].x, cube_verts[1].y, cube_verts[1].z);
	tex2(0, 1); vert3(cube_verts[2].x, cube_verts[2].y, cube_verts[2].z);
	tex2(1, 1); vert3(cube_verts[6].x, cube_verts[6].y, cube_verts[6].z);
}


void DrawSprite() {
	GLuint vao, myBuffers[2];
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(2, &myBuffers[0]);
	glBindBuffer(GL_ARRAY_BUFFER, myBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3_t) * 6, &vertList[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, myBuffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2_t) * 6, &uvList[0], GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glDeleteBuffers(2, &myBuffers[0]);
	glDeleteVertexArrays(1, &vao);
}

GLuint LoadTexture(std::string sfilename) {
	GLuint tex;

	// load smile texture
	SDL_Surface *surf = SDL_LoadBMP(sfilename.c_str());
	if(surf == NULL) {
		std::cout << "Couldn't load " + sfilename << std::endl;
		std::cout << "\t *" << SDL_GetError() << std::endl;
		exit(0);
	}
	
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 3, surf->w, surf->h, 0, GL_BGR, GL_UNSIGNED_BYTE, surf->pixels);
	
	SDL_FreeSurface(surf);

	return tex;
}

const int WINDOW_W = 256;
const int WINDOW_H = 256;

Eternal::Font myFont;

class Diag : public Eternal::PanelUI {
    public:
        Diag() : PanelUI(WINDOW_W - 300,64, 256, 256) {
            myBox.SetGeometry(4, 4 + 32, 256 - 8, 12);
            for(int i = 0;i < 3;i++) {
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
            myButton.SetText("close");
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

            Eternal::Mesh myMesh;

            Eternal::Sprite mySprite;

            uint32_t ColorBuffer[640 * 480 * 3];

            void test_func();

            void OnInitialize() override {
                pos.w = 128;
                pos.h = 128;
                myFont.Load("data/hello");
                spr.Load("data/smile32.bmp");

                myMesh.Vert2(0,0); myMesh.Color4(0,0,255,255); myMesh.TexCoord2(0,0);
                myMesh.Vert2(1,0); myMesh.Color4(255,0,255,255); myMesh.TexCoord2(1,0);
                myMesh.Vert2(1,1); myMesh.Color4(0,255,255,255); myMesh.TexCoord2(0,1);

                myVideoSystem->SetMaxFPS(60);
            }

            void OnUpdate() override {
                if(myInputHandle->IsKeyDown(Eternal::InputHandle::KEY_ESCAPE)) {
                    exit(0);
                }
                pos.x += 1.0f;
                diag.OnUpdate(myInputHandle);
                myMenu.OnUpdate(myInputHandle);
            }


            void OnDraw() override {
                Eternal::Rect r(0,0,128,128);
                Eternal::Rect c(0,0,128,128);

                spr.Draw(r,c);


                Eternal::Quad q;
                r = { 200, 200, 64,64 };
                q.FromRect(r);
                myRenderer->SetColor(0,255,0,255);
    //            myRenderer->DrawQuad(q);
//                diag.OnDraw(myRenderer);


                static bool up = true;
                static float f = 0;
                if(up) {
                    f += 1;
                    if(f >= 254) {
                        up = false;
                    }
                }
                else {
                    f -= 1;
                    if(f <= 1) {
                        up = true;
                    }
                }
                r = { 0, 0, 300, 300 };
                q.FromRect(r);
                myRenderer->SetColor(1,1,1,0.8f);
                myRenderer->DrawQuad(q);
                

                if(myInputHandle->IsKeyTap(((Eternal::InputHandle::Key)SDL_SCANCODE_9))) {
                    myVideoSystem->ExportFrame("test.bmp");
                }

//                myMenu.OnDraw(myRenderer);
            }
        private:
            GLuint id;
            Diag diag;
           Menu myMenu;
            Eternal::Rect pos;
            float fScale = 1;
            bool down = true;

            Eternal::Sprite spr;

            Eternal::AudioTrack t;
};

Game myGame;
int main(int argc, char *args[]) {
    cube_verts[0] = { -1, -1, -1 };
	cube_verts[1] = { 1, -1, -1 };
	cube_verts[2] = { 1, 1, -1 };
	cube_verts[3] = { -1, 1, -1 };
	
	cube_verts[4] = { -1, -1, 1 };
	cube_verts[5] = { 1, -1, 1 };
	cube_verts[7] = { -1, 1, 1 };
	cube_verts[6] = { 1, 1, 1 };
	CompileArr();

    myGame.Start(0, 0, WINDOW_W, WINDOW_H);

    return 0;
}
