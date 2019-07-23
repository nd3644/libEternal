#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"
#include <string>
#include <GL/glew.h>

namespace Eternal {
    class Sprite {
        public:
            Sprite();
            ~Sprite();

            void Load(std::string sfilename);
            void Draw(Rect &pos, Rect &clip);
        private:
            void ClearData();

            GLuint myTexID;
            int w, h;
            bool bLoaded;

            GLuint vertArrObj;
            GLuint arrayBuffers[3];

            Vec2 vVertexBuffer[6];
            Vec2 vTexCoords[6];
            RGBA ColorBuffer[6];
            float ftexcoords[6 * 2];
    };
}

#endif
