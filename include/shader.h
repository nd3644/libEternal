#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

namespace Eternal {
    class Shader {
        public:

            ~Shader();
            enum Type {
                SHADER_VERTEX = 0,
                SHADER_FRAGMENT
            };

            
            void Initialize();
            void Bind();
        private:
            GLuint myShaders[2];
            GLuint myProgram;
            bool bLoaded;
    };
}

#endif