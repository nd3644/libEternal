#include "application.h"

Eternal::Application::Application() {
    myVideoSystem = new VideoSystem();
    myRenderer = new Renderer();
}

Eternal::Application::~Application() {
    delete myVideoSystem;
    delete myRenderer;
}

void Eternal::Application::OnInitialize() {
}

void Eternal::Application::OnUpdate() {

}

void Eternal::Application::OnDraw() {

}

void Eternal::Application::Start(int x, int y, int w, int h) {
    OnInitialize();
    myVideoSystem->Initialize(x,y,w,h);
    myRenderer->Initialize();
    while(myVideoSystem->Clear()) {
        OnUpdate();
        OnDraw();
        myVideoSystem->SwapBuffers();
    }


}