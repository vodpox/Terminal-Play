#ifndef INPUT_H
#define INPUT_H

enum Keyboard {
	A, a, B, b, C, c, D, d, E, e, F, f, G, g, H, h, I, i, J, j, K,
	k, L, l, M, m, N, n, O, o, P, p, Q, q, R, r, S, s, T, t, U, u,
	V, v, W, w, X, x, Y, y, Z, z, num0, num1, num2, num3, num4,
	num5, num6, num7, num8, num9, spacebar, escape, upArrow,
	downArrow, rightArrow, leftArrow
};

class Input {
	private:
		bool caseSensitive = false;

	public:
		void setCaseSensitivity(bool caseSensitive);
		bool getButton(Keyboard key);
};

#endif
