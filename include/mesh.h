#ifndef MESH_H
#define MESH_H

#include "types.h"
#include <GL/glew.h>
#include <vector>

namespace Eternal {
    class Mesh {
        public:
            Mesh();
            ~Mesh();


            void Clean();
            void Vert2(float x, float y);
            void TexCoord2(float x, float y);
            void Color4(float r, float g, float b, float a);
            void Draw();
        private:
            GLuint vertArrObj;
            GLuint arrayBuffers[3];

            std::vector<Vec2>vVertBuffer; // Vec2 vVertexBuffer[6];
            std::vector<Vec2>vTexCoords; // Vec2 Vec2 vTexCoords[6];
            std::vector<RGBA>ColorBuffer; // RGBA ColorBuffer[6];        
    };
}

#endif
