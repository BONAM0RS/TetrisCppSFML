
#include "tetris.h"


int main()
{
	// Create window: width, height, title
	RenderWindow window(VideoMode(320, 480), "Tetris");

	Tetris run(window);

	return 0;
}

