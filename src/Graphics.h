#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <sys/ioctl.h>
#include <termios.h>
#include <vector>
#include <string>

enum Format{Bold};

struct ScreenSpace{
	int x;
	int y;
	char ch;
	std::vector<Format> format;
};

class Graphics{
	
	private:
		std::vector<ScreenSpace> screen;
		
		std::vector<Format> currentFormat;
		
		struct termios oldios;
		struct winsize winSize;
		int terminalSizeX;
		int terminalSizeY;
	
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
		void draw();
};

#endif