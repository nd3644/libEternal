#ifndef WIDGET_H
#define WIDGET_H

#include "types.h"

#include "input.h"
#include <vector>

namespace Eternal {
    class Renderer;
    class Widget {
        public:
            Widget(Widget *parent = nullptr) {
                SetParent(parent);
                bMouseIsOver = false;
                bShown = false;
            }
            ~Widget() {}


            void Show(bool b) {
                bShown = b;
            }

            bool IsShown() const {
                return bShown;
            }

            Eternal::Rect GetRelativePosition() {
                Eternal::Rect r = rWidgetRect;
                if(parent != nullptr) {
                    r.x += parent->rWidgetRect.x;
                    r.y += parent->rWidgetRect.y;
                }
                return r;
            }
            void SetParent(Widget *parent) {
                this->parent = parent;
            }

            void AddWidget(Widget *widget) {
                widget->parent = (Widget*)this;
                myWidgets.push_back(widget);
            }

            void SetGeometry(float x, float y, float w, float h) {
                rWidgetRect = { x, y, w, h };
            }

            Eternal::Rect GetGeometry() {
                return rWidgetRect;
            }

            virtual void Resize(float w, float h) {
                rWidgetRect.w = w;
                rWidgetRect.h = h;
            }
            virtual void Move(float x, float y) {
                rWidgetRect.x = x;
                rWidgetRect.y = y;
            }

            virtual void OnDraw(Renderer *myRenderer) {
                if(!bShown) {
                    return;
                }
                for(unsigned int i = 0; i < myWidgets.size();i++) {
                    myWidgets[i]->OnDraw(myRenderer);
                }
            }
            virtual void OnUpdate(InputHandle *myInputHandle) {
                Rect rNewRect = rWidgetRect;
                if(parent != nullptr) {
                    rNewRect.x += parent->rWidgetRect.x;
                    rNewRect.y += parent->rWidgetRect.y;
                }
                bMouseIsOver = false;
                if(myInputHandle->GetMouseX() > rNewRect.x && myInputHandle->GetMouseX() < rNewRect.x + rNewRect.w &&
                myInputHandle->GetMouseY() > rNewRect.y && myInputHandle->GetMouseY() < rNewRect.y + rNewRect.h ) {
                    bMouseIsOver = true;
                }

                for(unsigned int i = 0; i < myWidgets.size();i++) {
                    myWidgets[i]->OnUpdate(myInputHandle);
                }
            }

            bool IsMouseOver() {
                return bMouseIsOver;
            }
        private:
            bool bMouseIsOver;
            
        protected:
            bool bShown;
    
        public:
            Eternal::Rect rWidgetRect;
            Widget *parent;
            std::vector<Widget *>myWidgets;
    };
}

#endif
