#ifndef FONT_H
#define FONT_H

#include <sprite.h>
#include <string>

namespace Eternal {

    struct glyph {
        int minX, minY;
        int maxX, maxY;

        int advance;
    };

    class Font {
        public:
            Font();
            ~Font();

            void Load(std::string sfilename);
            void DrawString(std::string str, float fromX, float fromY, float fScale);
        private:
            int iFontSize;
            glyph *glyphList;
            Sprite myFontSheet;
    };
}

#endif
