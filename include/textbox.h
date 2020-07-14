#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "widget.h"
#include <string>

namespace Eternal {
    class Renderer;
    class InputHandle;
    class Textbox : public Widget {
        public:
            Textbox();
            ~Textbox();

            void OnDraw(Renderer *myRenderer) override;
            void OnUpdate(InputHandle *myInputHandle) override;
        private:
            std::string sContents;
            bool bFocused;
    };
}

#endif