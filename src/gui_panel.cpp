#include "gui_panel.h"
#include "renderer.h"
#include "input.h"
#include <iostream>


Eternal::PanelUI::PanelUI(float x, float y, float w, float h) : Widget(nullptr) {
    rWidgetRect = { x, y, w, h };

    bGrabbed = false;
}

Eternal::PanelUI::~PanelUI() {

}

void Eternal::PanelUI::OnDraw(Eternal::Renderer *myRenderer) {
    if(!bShown) {
        return;
    }
    Eternal::Quad q;
    q.FromRect(rWidgetRect);
    myRenderer->SetColor(0.3f, 0.3f, 0.3f, 0.8f);
    myRenderer->DrawQuad(q);

    // render handle
    myRenderer->SetColor(0.4f,0.4f,0.4f, 0.8f);
    Eternal::Rect r = { rWidgetRect.x, rWidgetRect.y - 16, rWidgetRect.w, 16 };
    q.FromRect(r);
    myRenderer->DrawQuad(q);

    Widget::OnDraw(myRenderer);
}

void Eternal::PanelUI::OnUpdate(Eternal::InputHandle *myInputHandle) {
    Widget::OnUpdate(myInputHandle);
    float mx = myInputHandle->GetMouseX();
    float my = myInputHandle->GetMouseY();
    
    if(bGrabbed && !myInputHandle->IsMouseDown(InputHandle::MBUTTON_LEFT)) {
        bGrabbed = false;
    }
    else if (myInputHandle->IsMouseClick(InputHandle::MBUTTON_LEFT)) {
        if(myFlags & FLAGS_DRAGGABLE) {
            if(mx > rWidgetRect.x &&  mx < rWidgetRect.x + rWidgetRect.w
            && my > rWidgetRect.y-16 && my < rWidgetRect.y-16 + 16) {
                bGrabbed = true;
            }
        }
    }

    if(bGrabbed) {
        rWidgetRect.x += myInputHandle->GetMouseX() - myInputHandle->GetFormerMouseX();
        rWidgetRect.y += myInputHandle->GetMouseY() - myInputHandle->GetFormerMouseY();
    }
}

void Eternal::PanelUI::SetFlags(Flags flags) {
    myFlags = flags;
}

void Eternal::Button::OnDraw(Eternal::Renderer *myRenderer) {
    Widget::OnDraw(myRenderer);
    Eternal::Quad q;
    if(IsMouseOver()) {
        myRenderer->SetColor(0.4, 0.4, 0.4,0.5f);
    }
    else {
        myRenderer->SetColor(0.2f, 0.2f, 0.2f, 0.5f);
    }
    Eternal::Rect newRect = GetRelativePosition();
    q.FromRect(newRect);
    myRenderer->DrawQuad(q);

    int length = myRenderer->GetFont().DrawStringCentered(myText, newRect.x + (newRect.w / 2), newRect.y + (newRect.h/2), 1.0f);
    if(length > rWidgetRect.w) {
        rWidgetRect.w = (float)length + 18;
    }

}


void Eternal::Label::OnDraw(Eternal::Renderer *myRenderer) {
    Eternal::Rect newRect = GetRelativePosition();
    myRenderer->GetFont().DrawString(myText, newRect.x, newRect.y);
}


void Eternal::Radiobox::OnDraw(Eternal::Renderer *myRenderer) {

    Widget::OnDraw(myRenderer);
    myLabel.OnDraw(myRenderer);

    Eternal::Quad q;
    Eternal::Rect r = GetRelativePosition();
    r.w = r.h = 16;
    q.FromRect(r);
    if(bChecked) {
        myRenderer->SetColor(0,1,0,1);
    }
    else {
        myRenderer->SetColor(0,0.25f,0,1);
    }
    myRenderer->DrawQuad(q);
}

void Eternal::Radiobox::OnUpdate(Eternal::InputHandle *myInputHandle) {

    Widget::OnUpdate(myInputHandle);

    myLabel.SetGeometry(GetRelativePosition().x + 20, GetRelativePosition().y, GetRelativePosition().w, GetRelativePosition().h);
    myLabel.OnUpdate(myInputHandle);
    if(myInputHandle->IsMouseClick(InputHandle::MBUTTON_LEFT) && IsMouseOver()) {
        bChecked = !bChecked;
    }
}