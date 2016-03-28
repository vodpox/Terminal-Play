#include "Graphics.h"

#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

Graphics::Graphics(){
	tcgetattr(0, &oldios);
	setTermios();
	updateSize();
	clearScreen();
}

void Graphics::setTermios(){
	struct termios newios;
	newios = oldios;
	
  newios.c_lflag &= ~ICANON;
  newios.c_lflag &= ~ECHO;
	newios.c_cc[VMIN] = 0;
	newios.c_cc[VTIME] = 0;
	
  tcsetattr(0, TCSANOW, &newios);
}

void Graphics::resetTermios(){
	tcsetattr(0, TCSANOW, &oldios);
}

void Graphics::updateSize(){
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &winSize);
	terminalSizeX = winSize.ws_col;
	terminalSizeY = winSize.ws_row;	
}

int Graphics::getTerminalSizeX(){
	return terminalSizeX;
}

int Graphics::getTerminalSizeY(){
	return terminalSizeY;
}

void Graphics::clearScreen(){
	for(int y = 0; y < terminalSizeY; y++){
		printf("\n");
	}
}