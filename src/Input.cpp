#include "Input.h"
#include <cstdio>


void Input::setCaseSensitivity(bool caseSensitivity){
	caseSensitive = caseSensitivity;
}

bool Input::getButton(Keyboard key){
	int input;
	input = getc(stdin);

	if(input >= 97 && input <= 122){ // lowercase letters
		if(caseSensitive){
			if( ((input - 97) * 2 + 1) == key ) return true;
			else return false;
		}
		else{
			if( ((input - 97) * 2 + 1) == key || ((input - 97) * 2 + 1) == key - 1) return true;
			else return false;
		}
	}

	if(input >= 65 && input <= 90){ // uppercase letters
		if(caseSensitive){
			if( ((input - 65) * 2) == key ) return true;
			else return false;
		}
		else{
			if( ((input - 65) * 2) == key || ((input - 65) * 2) == key - 1) return true;
			else return false;
		}
	}

	if(input >= 48 && input <= 57){ // numbers
		if( ((input - 48) + 52) == key ) return true;
		else return false;
	}

	if(input == 32){ // spacebar
		if( Keyboard::spacebar == key ) return true;
		else return false;
	}

	if(input == 27){ // escape/escaped buttons
		input = getc(stdin);
		if(input == -1){ // escape
			if( Keyboard::escape == key ) return true;
			else return false;
		}
		if(input == 91){ // arrows
			input = getc(stdin);
			if( ((input - 65) + Keyboard::upArrow) == key ) return true;
			else return false;
		}
	}
	return false;
}
