#include "Camera.h"

namespace tplay {
	
	void Camera::setCoordinates(int newX, int newY) {
		x = newX;
		y = newY;
	}
	
	int Camera::getX() {
		return x;
	}
	
	int Camera::getY() {
		return y;
	}
	
}