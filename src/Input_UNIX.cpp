#ifdef __unix

#include "Input.h"
#include <cstdio>


namespace tplay {
	
	void Input::getInput() {
		for (int i = 0; i < 3; i++) {
			input[i] = getc(stdin);
		}
	}

	bool Input::isButtonDown(Keyboard key) {
		if (input[1] != -1) { // escaped buttons
			if (input[1] == 91) { // arrows
				if (input[2] == key) return true;
				else return false;
			}
		}
		
		if (input[0] >= 97 && input[0] <= 122) { // convert lowercase to uppercase
			input[0] -= 32;
		}
		if (input[0] == key) return true;
		
		return false;
	}
	
}

#endif
