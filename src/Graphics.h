#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <sys/ioctl.h>
#include <termios.h>
#include <vector>
#include <string>

namespace tplay {
	
	enum Format {
		BOLD = 1, FAINT = 2, BLINK = 5, NEGATIVE = 7,
		FOREGROUND_BLACK = 30, FOREGROUND_RED = 31, FOREGROUND_GREEN = 32,
		FOREGROUND_YELLOW = 33, FOREGROUND_BLUE = 34, FOREGROUND_MAGENTA = 35,
		FOREGROUND_CYAN = 36, FOREGROUND_WHITE = 37, FOREGROUND_DEFAULT = 39,
		BACKGROUND_BLACK = 40, BACKGROUND_RED = 41, BACKGROUND_GREEN = 42,
		BACKGROUND_YELLOW = 43, BACKGROUND_BLUE = 44, BACKGROUND_MAGENTA = 45,
		BACKGROUND_CYAN = 46, BACKGROUND_WHITE = 47, BACKGROUND_DEFAULT = 49
	};

	struct ScreenUnit {
		int x;
		int y;
		char ch;
		std::vector<Format> format;
	};

	class Graphics {
		
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
			
			int lastTerminalSizeX = 0;
			int lastTerminalSizeY = 0; // = 0 is for preserving previous terminal text when drawing first frame
			
			void resetTermios();
			bool isScreenSchanged();
			std::string printFormat(std::vector<Format> format);
		
		public:
			Graphics();
			void setTermios();
			void updateSize();
			
			int getTerminalSizeX();
			int getTerminalSizeY();
			
			// adding to screen
			void addToWorld(int x, int y, std::string text);
			void addToScreen(int x, int y, std::string text);
			
			// formatting
			void setFormat(Format format);
			void unsetFormat(Format format);
			void resetFormat();
			
			// camera
			void setCameraCoordinates(int x, int y);
			void updateCameraCoordinates(int x, int y);
			int getCameraX();
			int getCameraY();
			
			void draw();
			
			~Graphics();
	};
	
}

#endif