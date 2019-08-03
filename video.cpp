#include "video.h"
#include <GL/glew.h>
#include <iostream>

Eternal::VideoSystem::VideoSystem() {
}

Eternal::VideoSystem::~VideoSystem() {

}

void Eternal::VideoSystem::Initialize(int x, int y, int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);
    myWindow = SDL_CreateWindow("meow !  :3", x, y, w, h, SDL_WINDOW_OPENGL);

    myGLContext = SDL_GL_CreateContext(myWindow);

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Couldn't initialize GLEW" << std::endl;
    }

    glClearColor(0, 0, 0, 0);

    myShader.Initialize();
    myShader.Bind();
    glViewport(x,y,w,h);

    // TODO: Init shaders


//    glEnable(GL_LINE_SMOOTH);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Eternal::VideoSystem::Clear() {
    SDL_PollEvent(&mySDLEvent);

    if(mySDLEvent.type == SDL_QUIT) {
        return false;
    }
    else if(mySDLEvent.type = SDL_WINDOWEVENT && mySDLEvent.window.event == SDL_WINDOWEVENT_CLOSE) {
        return false;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

void Eternal::VideoSystem::SwapBuffers() {
    SDL_GL_SwapWindow(myWindow);
}