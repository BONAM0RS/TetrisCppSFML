
#pragma once

#include <iostream>


struct Point { int x; int y; };


class Tetramino
{
public:
	Tetramino();
	~Tetramino();

public:
	void spawn();
	void setDirX(int x);
	void moveAxisX();
	void moveAxisY();
	void rotateRight();
	void resetPos();

	int getDirX()            { return xDir; }
	int getSquaresCount()    { return SQUARES_COUNT; }
	int getShapesCount()     { return SHAPES_COUNT; }
	Point* getSquarePoints() { return squares; }
	Point* getBackupPoints() { return backup; }

private:
	static const int SHAPES_COUNT  = 7;
	static const int SQUARES_COUNT = 4;

	const int SHAPES_MATRIX[SHAPES_COUNT][SQUARES_COUNT] =
	{
	 //      0,1,2,3                         0  1     x       
	 /* 0 */ 1,3,5,7, // I                 |----------->      
	 /* 1 */ 2,4,5,7, // S               0 | 0  1             square 0 = (0 % 2; 0 / 2) = (0;0)  |  square 1 = (1 % 2; 1 / 2) = (1;0)     
	 /* 2 */ 3,5,4,6, // Z               1 | 2  3             square 2 = (2 % 2; 2 / 2) = (0;1)  |  square 3 = (1 % 2; 1 / 2) = (1;1)    
	 /* 3 */ 3,5,4,7, // T               2 | 4  5             square 4 = (4 % 2; 4 / 2) = (0;2)  |  square 5 = (5 % 2; 5 / 2) = (1;2)
	 /* 4 */ 2,3,5,7, // L               3 | 6  7             square 6 = (6 % 2; 6 / 2) = (0;3)  |  square 7 = (7 % 2; 7 / 2) = (1;3)
	 /* 5 */ 3,5,7,6, // J                 | 
	 /* 6 */ 2,3,4,5, // O               y v
	};

	Point squares[4] = { 0 };
	Point backup[4] = { 0 };

	int xDir;
	int yDir;
};

