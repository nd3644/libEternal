#ifndef FRAMEBUFFER_h
#define FRAMEBUFFER_H

#include <GL/glew.h>

namespace Eternal {
    class FrameBuffer {
        public:
            FrameBuffer();
            ~FrameBuffer();

            void Initialize(int w, int h);
            void Bind();

            GLuint myTextureID;
        private:
            GLuint myFrameBufferID;
            GLuint myRenderBufferID;

            int iWidth, iHeight;
    };
}

#endif