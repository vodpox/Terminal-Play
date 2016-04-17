#ifndef SCENE_H
#define SCENE_H

class Scene{
	
	public:
		virtual void update(){}
		virtual void draw(){}
		virtual ~Scene() {}
	
};

#endif