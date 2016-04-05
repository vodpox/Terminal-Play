#include "Input.h"
#include <cstdio>


bool Input::getButton(Keyboard key){
	int input;
	input = getc(stdin);
	
	if(input >= 97 && input <= 122){ // lowercase letters
		if( input - 97 == key ) return true;
		else return false;
	}

	if(input >= 65 && input <= 90){ // uppercase letters
		if( input - 65 == key ) return true;
		else return false;
	}

	if(input >= 48 && input <= 57){ // numbers
		if( ((input - 48) + 52) == key ) return true;
		else return false;
	}

	if(input == 32){ // spacebar
		if( Keyboard::SPACEBAR == key ) return true;
		else return false;
	}

	if(input == 27){ // escape/escaped buttons
		input = getc(stdin);
		if(input == -1){ // escape
			if( Keyboard::ESCAPE == key ) return true;
			else return false;
		}
		if(input == 91){ // arrows
			input = getc(stdin);
			if( ((input - 65) + Keyboard::UP_ARROW) == key ) return true;
			else return false;
		}
	}
	return false;
}
