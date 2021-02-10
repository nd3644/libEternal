#include "video.h"
#include "renderer.h"
#include <GL/glew.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "dbglog.h"


#include <cstring>

Eternal::VideoSystem::VideoSystem() {
    iElapsedFrames = iFPSTimer = iAverageFPS = 0;
    iMaxFPS = 0;
}

Eternal::VideoSystem::~VideoSystem() {

}

void Eternal::VideoSystem::Initialize(int x, int y, int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);
    myWindow = SDL_CreateWindow("meow !  :3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    myGLContext = SDL_GL_CreateContext(myWindow);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Couldn't initialize GLEW" << std::endl;
    }

    glClearColor(0, 0, 0, 1);

    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100,  MIX_DEFAULT_FORMAT, 2, 2048);

    myShader.Initialize();
    myShader.Bind();
    glViewport(0,0,w,h);

    // TODO: Init shaders
    iCurrentWindowWidth = WIN_W = w;
    iCurrentWindowHeight = WIN_H = h;

    myFBO.Initialize(w, h);
    mySprite.Load("null");
//    glEnable(GL_LINE_SMOOTH);

    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    (*DbgLog::GetInstance()) << "Init happened\n;";

    iFPSTimer = SDL_GetTicks();
}

bool Eternal::VideoSystem::Clear() {
    myFBO.Bind();
    
    myShader.Bind();
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    while(SDL_PollEvent(&mySDLEvent) != 0) {
        if((mySDLEvent.type == SDL_QUIT)) {
            Mix_CloseAudio();
            Mix_Quit();
            SDL_Quit();
            return false;
        }
        else if(mySDLEvent.type == SDL_WINDOWEVENT) {
            if(mySDLEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
                int newWidth = mySDLEvent.window.data1;
                int newHeight = mySDLEvent.window.data2;
                        
                glViewport(0, 0, newWidth, newHeight);
                iCurrentWindowWidth = newWidth;
                iCurrentWindowHeight = newHeight;
            }
        }
    }

    return true;
}

void Eternal::VideoSystem::Resize(int w, int h) {
    SDL_SetWindowSize(myWindow, w, h);
    int newWidth = w;
    int newHeight = h;

    glViewport(0, 0, newWidth, newHeight);
    iCurrentWindowWidth = newWidth;
    iCurrentWindowHeight = newHeight;
}

void Eternal::VideoSystem::SetMaxFPS(int i) {
    iMaxFPS = i;
}

int Eternal::VideoSystem::GetMaxFPS() const {
    return iMaxFPS;
}

void Eternal::VideoSystem::SwapBuffers() {
    ExportFrame("test2.bmp");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    myShader.Bind();
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,iCurrentWindowWidth,iCurrentWindowHeight);
    glBindTexture(GL_TEXTURE_2D, myFBO.myTextureID);
    mySprite.ForceResize(WIN_W, WIN_H);
    Eternal::Rect r(0, 0, WIN_W, WIN_H);
    Eternal::Rect c(0,0, WIN_W, WIN_H);
    mySprite.Flip(false,true);
    mySprite.Draw_NoBind(r,c);

    SDL_GL_SwapWindow(myWindow);
    iElapsedFrames++;

    if(SDL_GetTicks() - iFPSTimer > 1000) {
        SDL_SetWindowTitle(myWindow, std::to_string(iElapsedFrames).c_str());
        iElapsedFrames = 0;
        iFPSTimer = SDL_GetTicks();
    }

    static int fps = SDL_GetTicks();

    if(iMaxFPS != 0) {
        int time = SDL_GetTicks() - fps;
        if(time < 1000 / iMaxFPS) {
            SDL_Delay((1000 / iMaxFPS) - time);
        }
        fps = SDL_GetTicks();
    }
}

bool Eternal::VideoSystem::IsFullscreen() const {
    return (SDL_GetWindowFlags(myWindow) & SDL_WINDOW_FULLSCREEN);
}

void Eternal::VideoSystem::SetFullscreen(bool b) {
    if(b && !IsFullscreen()) {
        SDL_SetWindowFullscreen(myWindow, SDL_TRUE);
    }
    else if(!b && IsFullscreen()) {
        SDL_SetWindowFullscreen(myWindow, SDL_FALSE);
    }
}

void Eternal::VideoSystem::SetVSync(bool b) {
    int i = (b == true) ? 1 : 0;
    SDL_GL_SetSwapInterval(i);
}

bool Eternal::VideoSystem::GetVSync() const {
    return static_cast<bool>(SDL_GL_GetSwapInterval());
}

int Eternal::VideoSystem::GetCurrentWidth() const {
    return iCurrentWindowWidth;
}

int Eternal::VideoSystem::GetCurrentHeight() const {
    return iCurrentWindowHeight;
}

void Eternal::VideoSystem::ExportFrame(std::string sfilename) {
    GLubyte *pixels = new GLubyte[(WIN_W * WIN_H) * 3];

    for(int y = 0;y < WIN_H;y++) {
        for(int x = 0;x < WIN_W;x++) {
            std::swap(pixels[((y * WIN_W) + x)], pixels[(((WIN_H-1) - (y * WIN_W)) + x)]);
        }
    }
    glReadPixels(0,0,WIN_W,WIN_H,GL_RGB, GL_UNSIGNED_BYTE, pixels);    
    SDL_Surface *mySurf = SDL_CreateRGBSurface(0,WIN_W,WIN_H,24,0x00FF0000,0x0000FF00,0x000000FF,0);

    mySurf->pixels = pixels;

    SDL_SaveBMP(mySurf, sfilename.c_str());
}
