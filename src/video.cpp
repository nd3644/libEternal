#include "video.h"
#include "renderer.h"
#include <GL/glew.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

Eternal::VideoSystem::VideoSystem() {
}

Eternal::VideoSystem::~VideoSystem() {

}

void Eternal::VideoSystem::Initialize(int x, int y, int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);
    myWindow = SDL_CreateWindow("meow !  :3", x, y, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    myGLContext = SDL_GL_CreateContext(myWindow);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Couldn't initialize GLEW" << std::endl;
    }

    glClearColor(0, 0, 0, 0);

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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Eternal::VideoSystem::Clear() {
    myFBO.Bind();
    myShader.Bind();
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


                newWidth = (newWidth / WIN_W) * WIN_W;
                if(newWidth < WIN_W) {
                    newWidth = WIN_W;
                }
                newHeight = (newHeight / WIN_H) * WIN_H;
                if(newHeight < WIN_H) {
                    newHeight = WIN_H;
                }

                SDL_SetWindowSize(myWindow, newWidth, newHeight);
                
                glViewport(0, 0, newWidth, newHeight);
                iCurrentWindowWidth = newWidth;
                iCurrentWindowHeight = newHeight;
            }
        }
    }

    return true;
}

void Eternal::VideoSystem::SwapBuffers() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    myShader.Bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0,0,iCurrentWindowWidth,iCurrentWindowHeight);
    glBindTexture(GL_TEXTURE_2D, myFBO.myTextureID);
    mySprite.ForceResize(WIN_W, WIN_H);
    Eternal::Rect r(0, 0, WIN_W, WIN_H);
    Eternal::Rect c(0,0, WIN_W, WIN_H);
    mySprite.Flip(false,true);
    mySprite.Draw_NoBind(r,c);


    SDL_GL_SwapWindow(myWindow);
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
