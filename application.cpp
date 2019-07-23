#include "application.h"

Eternal::Application::Application() {
    myVideoSystem = new VideoSystem();
    myRenderer = new Renderer();
    myInputHandle = new InputHandle();
}

Eternal::Application::~Application() {
    delete myVideoSystem;
    delete myRenderer;
    delete myInputHandle;
}

void Eternal::Application::OnInitialize() {
}

void Eternal::Application::OnUpdate() {

}

void Eternal::Application::OnDraw() {

}

void Eternal::Application::Start(int x, int y, int w, int h) {
    myVideoSystem->Initialize(x,y,w,h);
    myRenderer->Initialize();

    OnInitialize();
    while(myVideoSystem->Clear()) {
        myInputHandle->PollInputs();
        OnUpdate();
        OnDraw();
        myVideoSystem->SwapBuffers();
    }

}