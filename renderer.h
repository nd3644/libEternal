#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include <GL/glew.h>

namespace Eternal {
    class Renderer {
        public:
            Renderer();
            ~Renderer();

            void Initialize();

            void SetColor(float r, float g, float b, float a);
            void DrawQuad(Quad &quad);
            void DrawTriangle(Triangle &triangle);
            void DrawLine(float sx, float sy, float fx, float fy);
        private:
            GLuint vertArrObj;
            GLuint arrayBuffers[3];

            Vec2 vVertexBuffer[6];
            RGBA ColorBuffer[6];
            float ftexcoords[6 * 2];
            bool bInitialized;
    };
}

#endif