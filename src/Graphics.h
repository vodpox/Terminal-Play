#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <sys/ioctl.h>
#include <termios.h>
#include <vector>
#include <string>

enum Format{Bold};

struct ScreenUnit{
	int x;
	int y;
	char ch;
	std::vector<Format> format;
};

class Graphics{
	
	private:
		int cameraX = 0;
		int cameraY = 0;
		
		std::vector<ScreenUnit> screen;
		std::vector<ScreenUnit> lastScreen;
		std::vector<Format> currentFormat;
		
		struct termios oldios;
		struct winsize winSize;
		int terminalSizeX;
		int terminalSizeY;
		
		int lastTerminalSizeX;
		int lastTerminalSizeY;
		bool isScreenSchanged();
	
	public:
		Graphics();
		void setTermios();
		void resetTermios();
		void updateSize();
		
		int getTerminalSizeX();
		int getTerminalSizeY();
		
		void clearScreen();
		void setFormat(Format format);
		void unsetFormat(Format format);
		void resetFormat();
		void addToScreen(int x, int y, std::string text);
		void setCameraCoordinates(int x, int y);
		void draw();
};

#endif