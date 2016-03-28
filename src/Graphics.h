#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <sys/ioctl.h>
#include <termios.h>

class Graphics{
	
	private:
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
};

#endif