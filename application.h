#ifndef APPLICATION_H
#define APPLICATION_H

#include "video.h"
#include "renderer.h"
#include "sprite.h"
#include "input.h"

namespace Eternal {
	class Application {
		public:
			Application();
			~Application();
			
			virtual void OnInitialize();
			virtual void OnUpdate();
			virtual void OnDraw();
			void Start(int x, int y, int w, int h);

		private:

		protected:
			Renderer *myRenderer;
			VideoSystem *myVideoSystem;
			InputHandle *myInputHandle;
	};
}

#endif
