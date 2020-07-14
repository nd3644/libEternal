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
            int DrawStringCentered(std::string str, float fromX = 0.0f, float fromY = 0.0f, float fScale = 1.0f,
                                            float red = 255.0f, float green = 255.0f, float blue = 255.0f, float alpha = 255.0f);
            int DrawString(std::string str, float fromX = 0.0f, float fromY = 0.0f, float fScale = 1.0f,
                                            float red = 255.0f, float green = 255.0f, float blue = 255.0f, float alpha = 255.0f);
        private:
            int iFontSize;
            glyph *glyphList;
            Sprite myFontSheet;
    };
}

#endif
