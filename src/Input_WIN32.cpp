#ifdef _WIN32

#include "Input.h"
#include <cstdio>
#include <conio.h>


namespace tplay {
	
	void Input::getInput() {
		input[0] = -1;
		input[1] = -1;
		input[2] = -1;
		for(int i = 0; _kbhit() && i < 3; i++) {
			input[i] = _getch();
		}
	}

	bool Input::isButtonDown(Keyboard key) {
		if (input[1] != -1) { // escaped buttons
			if (input[1] == key) return true;
			else return false;
		}
		
		if (input[0] >= 97 && input[0] <= 122) { // convert lowercase to uppercase
			input[0] -= 32;
		}
		if (input[0] == key) return true;
		
		return false;
	}
	
}

#endif
