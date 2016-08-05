#include "Graphics.h"

#include <cstdio>
#include <string>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


namespace tplay {
	
	bool Graphics::isScreenSchanged() {
		if (terminalSizeX != lastTerminalSizeX || terminalSizeY != lastTerminalSizeY) {
			return true;
		}
		else if (screen.size() != lastScreen.size()) {
			return true;
		}
		else {
			bool isChanged = false;
			for (int i = 0; i < screen.size(); i++) {
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


	std::string Graphics::printFormat(std::vector<Format> format) {
		std::string formatString = "\033[0";
		for (int i = 0; i < format.size(); i++) {
			formatString += ";" + std::to_string(format[i]);
		}
		return formatString + "m";
	}


	Graphics::Graphics() {
		tcgetattr(0, &oldios);
		setTermios();
	}


	void Graphics::setTermios() {
		struct termios newios;
		newios = oldios;
		
	  newios.c_lflag &= ~ICANON;
	  newios.c_lflag &= ~ECHO;
		newios.c_cc[VMIN] = 0;
		newios.c_cc[VTIME] = 0;
		
	  tcsetattr(0, TCSANOW, &newios);
	}


	void Graphics::resetTermios() {
		tcsetattr(0, TCSANOW, &oldios);
	}


	void Graphics::updateSize() {
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &winSize);
		terminalSizeX = winSize.ws_col;
		terminalSizeY = winSize.ws_row;	
	}


	int Graphics::getTerminalSizeX() {
		return terminalSizeX;
	}


	int Graphics::getTerminalSizeY() {
		return terminalSizeY;
	}


	void Graphics::setFormat(Format format) {
		bool alreadyExists = false;
		for (int i = 0; i < currentFormat.size(); i++) {
			if(currentFormat[i] == format){
				alreadyExists = true;
				break;
			}
		}
		if (!alreadyExists) currentFormat.push_back(format);
		return;
	}


	void Graphics::unsetFormat(Format format) {
		for (int i = 0; i < currentFormat.size(); i++) {
			if (currentFormat[i] == format) {
				currentFormat.erase(currentFormat.begin() + i);
				return;
			}
		}
	}


	void Graphics::resetFormat() {
		currentFormat.clear();
	}


	void Graphics::addToScreen(int x, int y, std::string text) {
		for (int i = 0; i < text.size(); i++) {
			ScreenUnit SU;
			SU.x = x + i;
			SU.y = y;
			SU.ch = text.at(i);
			SU.format = currentFormat;
			screen.push_back(SU);
		}
	}


	void Graphics::setCameraCoordinates(int x, int y) {
		cameraX = x;
		cameraY = y;
	}


	void Graphics::updateCameraCoordinates(int x, int y) {
		cameraX += x;
		cameraY += y;
	}


	int Graphics::getCameraX() {
		return cameraX;
	}


	int Graphics::getCameraY() {
		return cameraY;
	}


	void Graphics::draw() {
		if (!isScreenSchanged()) return; // if nothing is changed do not draw anything
		
		// preserve preovious terminal text
		for (int i = 0; i < terminalSizeY - lastTerminalSizeY; i++) {
			printf("\n");
		}
		
		printf("\033[H");// reset terminal to top left corner
		
		std::string textToPrint[terminalSizeX][terminalSizeY];
		
		// set background
		for (int y = 0; y < terminalSizeY; y++) { // Y axis
			for (int x = 0; x < terminalSizeX; x++) { // X axis
				textToPrint[x][y] = "\033[0m ";
			}
		}
		
		// look what should be drawn on scren
		for (int i = 0; i < screen.size(); i++) {
			if( (screen[i].x >= cameraX && screen[i].x < terminalSizeX + cameraX) &&
			    (screen[i].y >= cameraY && screen[i].y < terminalSizeY + cameraY)){
				textToPrint[screen[i].x - cameraX][screen[i].y - cameraY] = printFormat(screen[i].format) + screen[i].ch;
			}
		}
		
		// draw frame
		for (int y = terminalSizeY - 1; y >= 0; y--) { // Y axis
			for (int x = 0; x < terminalSizeX; x++) { // X axis
				printf("%s", textToPrint[x][y].c_str());
			}
			if(y > 0) printf("\n");
		}
		
		lastTerminalSizeX = terminalSizeX;
		lastTerminalSizeY = terminalSizeY;
		lastScreen = screen;
		screen.clear();
		currentFormat.clear();
	}


	Graphics::~Graphics() {
		resetTermios();
		printf("\033[0m");
	}
	
}
