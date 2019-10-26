#ifndef VIDEO_H
#define VIDEO_H

#include <SDL2/SDL.h>
#include "shader.h"
#include "framebuffer.h"
#include "sprite.h"

namespace Eternal {
	class VideoSystem {
		public:
			VideoSystem();
			~VideoSystem();

			void Initialize(int x, int y, int w, int h);

			bool Clear();
			void SwapBuffers();
		private:
			SDL_Renderer *myRenderer;
			SDL_Window *myWindow;
			SDL_GLContext myGLContext;
			SDL_Event mySDLEvent;
			Shader myShader;

			FrameBuffer myFBO;

			Sprite mySprite;

			int iCurrentWindowWidth, iCurrentWindowHeight;
	};
}

#endif
