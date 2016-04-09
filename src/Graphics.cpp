#include "Graphics.h"

#include <cstdio>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


bool Graphics::isScreenSchanged(){
	if(terminalSizeX != lastTerminalSizeX || terminalSizeY != lastTerminalSizeY){
		return true;
	}
	else if(screen.size() != lastScreen.size()){
		return true;
	}
	else{
		bool isChanged = false;
		for(int i = 0; i < screen.size(); i++){
			if(screen[i].x != lastScreen[i].x || screen[i].y != lastScreen[i].y ||
			   screen[i].ch != lastScreen[i].ch || screen[i].format != lastScreen[i].format
			){
				isChanged = true;
				break;
			}
		}
		if(!isChanged) screen.clear();
		return isChanged;
	}
}

Graphics::Graphics(){
	tcgetattr(0, &oldios);
	setTermios();
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
		ScreenUnit SU;
		SU.x = x + i;
		SU.y = y;
		SU.ch = text.at(i);
		SU.format = currentFormat;
		screen.push_back(SU);
	}
}

void Graphics::setCameraCoordinates(int x, int y){
	cameraX = x;
	cameraY = y;
}

void Graphics::draw(){
	if(!isScreenSchanged()) return; // if nothing is changed do not draw anything
	
	std::string textOnScreen[terminalSizeX][terminalSizeY];
	
	for(int y = 0; y < terminalSizeY; y++){ // Y axis
		for(int x = 0; x < terminalSizeX; x++){ // X axis
			textOnScreen[x][y] = ' ';
		}
	}
	
	for(int i = 0; i < screen.size(); i++){
		if( (screen[i].x >= cameraX && screen[i].x < terminalSizeX + cameraX) &&
		    (screen[i].y >= cameraY && screen[i].y < terminalSizeY + cameraY)){
			textOnScreen[screen[i].x - cameraX][screen[i].y - cameraY] = /*Format + */ screen[i].ch;
		}
	}
	

	for(int y = terminalSizeY - 1; y >= 0; y--){ // Y axis
		printf("\n");
		for(int x = 0; x < terminalSizeX; x++){ // X axis
			printf("%s", textOnScreen[x][y].c_str());
		}
	}
	
	lastTerminalSizeX = terminalSizeX;
	lastTerminalSizeY = terminalSizeY;
	lastScreen = screen;
	screen.clear();
	currentFormat.clear();
}
