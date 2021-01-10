#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"
#include <string>
#include <GL/glew.h>

namespace Eternal {
    class Mesh;
    class Sprite {
        public:
            Sprite();
            ~Sprite();

            void Load(std::string sfilename);
            void FromData(uint8_t *pixels, int width, int height, int bpp);
            
            void Bind();
            void Draw(Rect &pos, Rect &clip);

            void Draw_NoBind(Rect &pos, Rect &clip);
            void ForceResize(int width, int height);

            void AmendToMesh(Rect &pos, Rect &clip, Eternal::Mesh &mesh);

            int GetWidth() const { return w; }
            int GetHeight() const { return h; }

            void Flip(bool u, bool v) { bFlipU = u; bFlipV = v; }

            void SetColor(float r, float g, float b, float a);
        private:
            bool bFlipU, bFlipV;
            void ClearData();

            GLuint myTexID;
            int w, h;
            bool bLoaded;

            GLuint vertArrObj;
            GLuint arrayBuffers[3];

            Vec2 vVertexBuffer[6];
            Vec2 vTexCoords[6];
            RGBA ColorBuffer[6];

            std::string sName;
    };
}

#endif
