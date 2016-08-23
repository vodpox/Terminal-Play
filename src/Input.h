#ifndef INPUT_H
#define INPUT_H

namespace tplay {
	
	enum Keyboard {
		A = 65, B = 66, C = 67, D = 68, E = 69, F = 70, G = 71, H = 72, I = 73,
		J = 74, K = 75, L = 76, M = 77, N = 78, O = 79, P = 80, Q = 81, R = 82,
		S = 83, T = 84, U = 85, V = 86, W = 87, X = 88, Y = 89, Z = 90,
		NUM_0 = 48, NUM_1 = 49, NUM_2 = 50, NUM_3 = 51, NUM_4 = 52,
		NUM_5 = 53, NUM_6 = 54, NUM_7 = 55, NUM_8 = 56, NUM_9 = 57,
		SPACEBAR = 32, TAB = 9, ESCAPE = 27, BACKSPACE = 127, ENTER = 10,
		UP_ARROW = 65, DOWN_ARROW = 66, RIGHT_ARROW = 67, LEFT_ARROW = 68
	};

	class Input {
		private:
			int input[3];
		
		public:
			void getInput();
			bool isButtonDown(Keyboard key);
	};
	
}

#endif
