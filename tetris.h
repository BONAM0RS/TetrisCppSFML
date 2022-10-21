
#pragma once

#include <SFML/Graphics.hpp>
#include "tetramino.h"

using namespace sf;


class Tetris
{
public:
	Tetris(RenderWindow& win);
	~Tetris();

private:
	void TickEvent();
	void CloseEvent();
	void KeyPressedEvent();
	void KeyReleasedEvent();

	void loadTextureFiles();
	void createSprites();

	void moveShape();
	void destroyFullRow();
	void drawObjects();

	void restartGame();

	bool checkCollision();
	
private:
	static const int DOT_PIXELS = 18;

	static const int FIELD_WIDTH = 10; 
	static const int FIELD_HEIGHT = 20; 

	int field[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

	RenderWindow& window;
	
	Texture texture_background;
	Texture texture_frame;
	Texture texture_tiles;
	
	Sprite sprite_background;
	Sprite sprite_frame;
	Sprite sprite_tiles;
	
	Tetramino* shape;

	Point* squares;
	Point* backup;

	bool isRotate;
	bool isPaused;

	int colorNum;
	int score;
	
	Clock clock;
	float timer;
	float delay;

	Event event;
};

