#ifdef _WIN32

#include "Graphics.h"

#include <windows.h>
#include <cstdio>
#include <string>
#include "Camera.h"


namespace tplay {
	
	bool Graphics::isScreenChanged() {
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
		// formating on Windows is not supported
		/*std::string formatString = "\033[0";
		for (int i = 0; i < format.size(); i++) {
			formatString += ";" + std::to_string(format[i]);
		}
		return formatString + "m";*/
		return "";
	}
	
	
	Graphics::Graphics() {
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = false;
		SetConsoleCursorInfo(consoleHandle, &info);
	}
	
	
	void Graphics::updateSize() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		terminalSizeX = csbi.srWindow.Right - csbi.srWindow.Left;
		terminalSizeY = csbi.srWindow.Bottom - csbi.srWindow.Top;
	}
	
	
	int Graphics::getTerminalSizeX() {
		return terminalSizeX;
	}
	
	
	int Graphics::getTerminalSizeY() {
		return terminalSizeY;
	}
	
	
	void Graphics::addToWorld(int x, int y, std::string text) {
		for (int i = 0; i < text.size(); i++) {
			ScreenUnit SU;
			SU.x = x + i;
			SU.y = y;
			SU.ch = text.at(i);
			SU.format = currentFormat;
			screen.push_back(SU);
		}
	}
	
	
	void Graphics::addToScreen(int x, int y, std::string text) {
		addToWorld(x + currentCamera->getX(), y + currentCamera->getY(), text);
	}
	
	
	void Graphics::addToScreen(int x, int y, std::string text, Camera * camera) {
		addToWorld(x + camera->getX(), y + camera->getY(), text);
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
	
	
	void Graphics::setCamera(Camera * camera) {
		currentCamera = camera;
	}
	
	
	void Graphics::draw() {
		resetFormat();
		
		if (!isScreenChanged()) return; // if nothing is changed do not draw anything
		
		// preserve preovious terminal text
		for (int i = 0; i < terminalSizeY - lastTerminalSizeY; i++) {
			printf("\n");
		}
		
		// reset terminal to top left corner
		COORD pos = {0, 0};
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, pos);
		
		std::string textToPrint[terminalSizeX][terminalSizeY];
		
		// set background
		for (int y = 0; y < terminalSizeY; y++) { // Y axis
			for (int x = 0; x < terminalSizeX; x++) { // X axis
				textToPrint[x][y] = " ";
			}
		}
		
		// look what should be drawn on scren
		for (int i = 0; i < screen.size(); i++) {
			if( (screen[i].x >= currentCamera->getX() &&
			     screen[i].x < terminalSizeX + currentCamera->getX()) &&
			    (screen[i].y >= currentCamera->getY() &&
			     screen[i].y < terminalSizeY + currentCamera->getY())
			){
				textToPrint[screen[i].x - currentCamera->getX()][screen[i].y - currentCamera->getY()] = printFormat(screen[i].format) + screen[i].ch;
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
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = true;
		SetConsoleCursorInfo(consoleHandle, &info);
	}
	
}

#endif
