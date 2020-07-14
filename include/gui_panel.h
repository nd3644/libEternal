#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include <vector>
#include "widget.h"
#include "types.h"
#include "renderer.h"


namespace Eternal {
    enum Flags {
        FLAGS_NONE = 0x00,
        FLAGS_DRAGGABLE = 0x02
    };

    class InputHandle;
    class Slider : public Widget {
        public:
            Slider(Widget *parent = nullptr) : Widget(parent) {
                rWidgetRect.w = 32; rWidgetRect.h = 12; fSliderVal = 0.5f;
                bGrabbed = false;
            }
            ~Slider() {}

            void OnDraw(Eternal::Renderer *myRenderer) override {

                Eternal::Rect rNewRect = rWidgetRect;
                if(parent != nullptr) {
                    rNewRect.x += parent->rWidgetRect.x;
                    rNewRect.y += parent->rWidgetRect.y;
                }
                myRenderer->SetColor(1,1,1,0.5f);
                myRenderer->DrawLine(rNewRect.x, rNewRect.y + (rNewRect.h / 2), rNewRect.x + rNewRect.w, rNewRect.y + (rNewRect.h / 2));

                Eternal::Rect block = { rNewRect.x + (rNewRect.w * fSliderVal), rNewRect.y, 4, rNewRect.h };
                Eternal::Quad q;
                q.FromRect(block);
                myRenderer->DrawQuad(q);
            }
            void OnUpdate(Eternal::InputHandle *myInputHandle) override {
                Widget::OnUpdate(myInputHandle);
                
                Eternal::Rect rNewRect = GetRelativePosition();

                if(IsMouseOver() && myInputHandle->IsMouseClick(InputHandle::MouseButtons::MBUTTON_LEFT)) {
                    bGrabbed = true;
                }
                else if(!myInputHandle->IsMouseDown(InputHandle::MouseButtons::MBUTTON_LEFT)) {
                    bGrabbed = false;
                }
                if(bGrabbed) {
                    fSliderVal = (myInputHandle->GetMouseX() - rNewRect.x) / rNewRect.w;
                    if(fSliderVal < 0)
                        fSliderVal = 0;
                    if(fSliderVal > 1)
                        fSliderVal = 1;
                }
            }
        private:
            float fSliderVal;
            bool bGrabbed;
    };

    class Button : public Widget {
        public:
            Button(Widget *parent = nullptr) : Widget(parent) {
                rWidgetRect.w = 48; rWidgetRect.h = 24;
                bClicked = false;
            }
            ~Button() { }

            void OnDraw(Eternal::Renderer *myRenderer) override;
            void OnUpdate(Eternal::InputHandle *myInputHandle) override {
                Widget::OnUpdate(myInputHandle);
                bClicked = false;
                if(IsMouseOver() && myInputHandle->IsMouseClick(InputHandle::MBUTTON_LEFT)) {
                    bClicked = true;
                }
            }

            bool WasClicked() {
                return bClicked;
            }

            void SetText(std::string str) {
                myText = str;
            }
        private:
            std::string myText;
            bool bClicked;
    };

    class Label : public Widget {
        public:
            Label(Widget *parent = nullptr) : Widget(parent) {
                rWidgetRect.w = 48; rWidgetRect.h = 24;
            }
            ~Label() { }

            void OnDraw(Eternal::Renderer *myRenderer) override;
            void OnUpdate(Eternal::InputHandle *myInputHandle) override {
                Widget::OnUpdate(myInputHandle);
            }
            void SetText(std::string str) {
                myText = str;
            }
        private:
            std::string myText;
    };

    class PanelUI : public Widget {
        public:
            PanelUI(float x, float y, float w, float h);
            PanelUI() {}
            ~PanelUI();

            void OnDraw(Eternal::Renderer *myRenderer);
            void OnUpdate(Eternal::InputHandle *myInputHandle);

            void SetFlags(Flags flags);
        private:
            Flags myFlags;
            bool bGrabbed;
    };


    class Radiobox : public Widget {
        public:
            Radiobox(Widget *parent = nullptr) : Widget(parent) , myLabel(parent) {
                 bChecked = false;
                 rWidgetRect = { 0, 0, 16, 16 };
            }
            ~Radiobox() {}

            void OnDraw(Eternal::Renderer *myRenderer) override;
            void OnUpdate(Eternal::InputHandle *myInputHandle) override;
            void SetText(std::string str) {
                myLabel.SetText(str);
            }
        private:
            Label myLabel;
            bool bChecked;
    };
}

#endif