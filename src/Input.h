#ifndef INPUT_H
#define INPUT_H

enum Keyboard {
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
	SPACEBAR, ESCAPE, UP_ARROW, DOWN_ARROW, RIGHT_ARROW, LEFT_ARROW
};

class Input {
	public:
		bool getButton(Keyboard key);
};

#endif
