#ifndef SCENE_H
#define SCENE_H

namespace tplay {
	
	class Scene {
		
		public:
			virtual void onEnter() {}
			virtual void onExit() {}
			virtual void update() {}
			virtual void draw() {}
			virtual ~Scene() {}
		
	};
	
}

#endif