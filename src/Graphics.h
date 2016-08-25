#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef __unix
	#include <sys/ioctl.h>
	#include <termios.h>
#endif
#include <vector>
#include <string>

#include "Camera.h"

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
			
			#ifdef __unix
				struct termios oldios;
				struct winsize winSize;
			#endif
			int terminalSizeX;
			int terminalSizeY;
			
			int lastTerminalSizeX = 0;
			int lastTerminalSizeY = 0; // = 0 is for preserving previous terminal text when drawing first frame
			
			bool isScreenChanged();
			std::string printFormat(std::vector<Format> format);
			
			Camera * currentCamera;
		
		public:
			Graphics();
			void updateSize();
			
			int getTerminalSizeX();
			int getTerminalSizeY();
				
			// adding to screen
			void addToWorld(int x, int y, std::string text);
			void addToScreen(int x, int y, std::string text);
			void addToScreen(int x, int y, std::string text, Camera * camera);
			
			// formatting
			void setFormat(Format format);
			void unsetFormat(Format format);
			void resetFormat();
			
			// camera
			void setCamera(Camera * camera);
			
			void draw();
			
			~Graphics();
	};
	
}

#endif
