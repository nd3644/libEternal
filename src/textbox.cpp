#include "textbox.h"

#include "renderer.h"

Eternal::Textbox::Textbox() {
    bFocused = false;
}

Eternal::Textbox::~Textbox() {
}

void Eternal::Textbox::OnDraw(Renderer *myRenderer) {
    Widget::OnDraw(myRenderer);
    Eternal::Quad q;
    Eternal::Rect newRect = GetRelativePosition();
    q.FromRect(newRect);

    myRenderer->SetColor(0.5f, 0.5f, 0.5f, 0.5f);
    myRenderer->DrawQuad(q);

    sContents = "ABCDEFGHIJLMNOPQRSTUVWXYZ";
    myRenderer->GetFont().DrawString(sContents, newRect.x, newRect.y, 1);
}


void Eternal::Textbox::OnUpdate(InputHandle *myInputHandle) {
    Widget::OnUpdate(myInputHandle);
    if(myInputHandle->IsMouseClick(InputHandle::MouseButtons::MBUTTON_LEFT)) {
        if(IsMouseOver()) {
            bFocused = true;
        }
        else {
            bFocused = false;
        }
    }
}