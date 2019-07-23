#ifndef APPLICATION_H
#define APPLICATION_H

#include "video.h"
#include "renderer.h"

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
	};
}

#endif
