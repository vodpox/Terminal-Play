#ifndef CAMERA_H
#define CAMERA_H

namespace tplay {
	
	class Camera {
		
		private:
			int x = 0;
			int y = 0;
		
		public:
			void setCoordinates(int, int);
			
			int getX();
			int getY();
		
	};
	
}

#endif