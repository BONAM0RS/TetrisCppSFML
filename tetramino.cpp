
#include "tetramino.h"


Tetramino::Tetramino()
{
	xDir = 0;
	yDir = 1;

	std::cout << " Tetramino created" << std::endl;
}


Tetramino::~Tetramino()
{
	std::cout << "\n Tetramino deleted" << std::endl;
}


void Tetramino::spawn()
{
	int random = rand() % SHAPES_COUNT;

	for (int i = 0; i < SQUARES_COUNT; i++)
	{
		squares[i].x = SHAPES_MATRIX[random][i] % 2;
		squares[i].y = SHAPES_MATRIX[random][i] / 2;

		// Random spawn
		squares[i].x += random;
		// It is necessary to correctly track the overflow of the field along the y-axis (restart)
		squares[i].y--;

		//std::cout << squares[i].y << std::endl;
		// std::cout << SHAPES_MATRIX[random][i] << std::endl;
		// std::cout << i << ". " << "x, y = " << a[i].x << ", " << a[i].y << std::endl;
	}
}


void Tetramino::setDirX(int x)
{
	xDir = x;
}


void Tetramino::moveAxisX()
{
	for (int i = 0; i < SQUARES_COUNT; i++)
	{
		backup[i] = squares[i]; // reserve position
		squares[i].x += xDir;
	}

	xDir = 0;
}


void Tetramino::moveAxisY()
{
	for (int i = 0; i < SQUARES_COUNT; i++)
	{
		backup[i] = squares[i]; // reserve position
		squares[i].y += yDir;
	}
}

void Tetramino::rotateRight()
{
	Point center = squares[1];

	for (int i = 0; i < SQUARES_COUNT; i++)
	{
		// Math explanation
		/*
		angle degree = 90;

		X = center.x + (squares[i].x − center.x) * cos⁡(angle degree) − (squares[i].y − center.y) * sin⁡(angle degree);
		Y = center.y + (squares[i].y − center.y) * cos⁡(angle degree) + (squares[i].x − center.x) * sin⁡(angle degree);

		cos(90) = 0;
		sin(90) = 1;

		X = center.x - (squares[i].y - center.y);
		Y = center.y + (squares[i].x - center.x);
		*/

		int x = squares[i].y - center.y;
		int y = squares[i].x - center.x;
		
		squares[i].x = center.x - x;
		squares[i].y = center.y + y;
	}
}


void Tetramino::resetPos()
{
	for (int i = 0; i < SQUARES_COUNT; i++)
	{
		squares[i] = backup[i];
	}
}

