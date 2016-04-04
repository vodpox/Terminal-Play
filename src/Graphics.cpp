#include "Graphics.h"

#include <cstdio>
#include <string>
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

void Graphics::setFormat(Format format){
	bool alreadyExists = false;
	for(int i = 0; i < currentFormat.size(); i++){
		if(currentFormat[i] == format){
			alreadyExists = true;
			break;
		}
	}
	if(!alreadyExists) currentFormat.push_back(format);
	return;
}

void Graphics::unsetFormat(Format format){
	for(int i = 0; i < currentFormat.size(); i++){
		if(currentFormat[i] == format){
			currentFormat.erase(currentFormat.begin() + i);
			return;
		}
	}
}

void Graphics::resetFormat(){
	currentFormat.clear();
}

void Graphics::addToScreen(int x, int y, std::string text){
	for(int i = 0; i < text.size(); i++){
		ScreenSpace SP;
		SP.x = x + i;
		SP.y = y;
		SP.ch = text.at(i);
		SP.format = currentFormat;
		screen.push_back(SP);
	}
}

void Graphics::draw(){
	std::string textOnScreen[terminalSizeX][terminalSizeY];
	
	for(int y = 0; y < terminalSizeY; y++){ // Y axis
		for(int x = 0; x < terminalSizeX; x++){ // X axis
			textOnScreen[x][y] = ' ';
		}
	}
	
	for(int i = 0; i < screen.size(); i++){
		if( (screen[i].x >= 0 && screen[i].x < terminalSizeX) &&
		    (screen[i].y >= 0 && screen[i].y < terminalSizeY) ){
			textOnScreen[screen[i].x][screen[i].y] = /*Format + */ screen[i].ch;
		}
	}
	
	for(int y = 0; y < terminalSizeY; y++){ // Y axis
		for(int x = 0; x < terminalSizeX; x++){ // X axis
			printf("%s", textOnScreen[x][y].c_str());
		}
	}
	
	screen.clear();
	currentFormat.clear();
}
