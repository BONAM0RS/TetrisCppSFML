
#include "tetris.h"


Tetris::Tetris(RenderWindow& win)
	: window(win)
{
	// Init
	isRotate = false;
	isPaused = false;

	colorNum = 1;
	score = 0;

	timer = 0.f;
	delay = 0.3f;

	srand((unsigned int)time(0));

	std::cout << "\n Tetris created" << std::endl;

	// Allocate memory to create Tetramino object
	shape = new Tetramino();

	// Init the shape points that contain coordinates of the squares
	squares = shape->getSquarePoints();
	backup = shape->getBackupPoints();

	shape->spawn();

	// Setup graphic objects
	loadTextureFiles();
	createSprites();
	
	// Start game loop
	TickEvent();
}


Tetris::~Tetris()
{
	// Return allocated memory
	delete shape;
	std::cout << " Tetris deleted" << std::endl;
}


void Tetris::loadTextureFiles()
{
	texture_background.loadFromFile("Images\\background.png");
	texture_frame.loadFromFile("Images\\frame.png");
	texture_tiles.loadFromFile("Images\\tiles.png");

	std::cout << " Textures loaded" << std::endl;
}


void Tetris::createSprites()
{
	sprite_background.setTexture(texture_background);
	sprite_frame.setTexture(texture_frame);
	sprite_tiles.setTexture(texture_tiles);

	// Cut out a separate 18x18 pixel square from the sprite
	sprite_tiles.setTextureRect(IntRect(0, 0, DOT_PIXELS, DOT_PIXELS));

	std::cout << " Sprites loaded" << std::endl;
}


void Tetris::TickEvent()
{
	// Main app loop
	while (window.isOpen())
	{
		// Events loop
		while (window.pollEvent(event))
		{
			CloseEvent();
			KeyPressedEvent();
			KeyReleasedEvent();
		}

		if (isPaused == false)
		{
			// Control movement
			moveShape();

			// Destroy row if it is full and move squares down
			destroyFullRow();

			// Restart the game if the squares collide with the top border
			restartGame();

			// Clear the whole window before rendering a new frame
			window.clear(Color::White);

			// Repaint 
			drawObjects();
		}

		// End the current frame and display its contents on screen
		window.display();
	}
}


void Tetris::CloseEvent()
{
	if (event.type == Event::Closed)
	{
		window.close();
		std::cout << "\n Window closed" << std::endl;
	}
}


void Tetris::KeyPressedEvent()
{
	if (event.type == Event::KeyPressed)
	{
		window.setKeyRepeatEnabled(true);

		if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Space)
		{
			window.setKeyRepeatEnabled(false);
			isRotate = true;
		}
		else if (event.key.code == Keyboard::Left)
		{
			shape->setDirX(-1);
		}
		else if (event.key.code == Keyboard::Right)
		{
			shape->setDirX(1);
		}
		else if (event.key.code == Keyboard::P)
		{
			if (isPaused == false)
			{
				isPaused = true;
			}
			else
			{
				isPaused = false;
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		delay = 0.05f;
	}
}

void Tetris::KeyReleasedEvent()
{
	if (event.type == Event::KeyReleased)
	{
		delay = 0.3f;
	}
}

void Tetris::moveShape()
{
	// Horizontal movement
	shape->moveAxisX();

	if (checkCollision() == true)
	{
		shape->resetPos();
	}

	// Vertical movement down based on timer tick
	float timeElapsed = clock.getElapsedTime().asSeconds();
	timer += timeElapsed;
	clock.restart();

	if (timer > delay)
	{
		shape->moveAxisY();

		if (checkCollision() == true)
		{
			for (int i = 0; i < shape->getSquaresCount(); i++)
			{
				field[backup[i].y][backup[i].x] = colorNum;
			}

			colorNum = 1 + rand() % shape->getShapesCount();

			shape->spawn();
		}

		timer = 0;
	}

	// Rotation movement
	if (isRotate == true)
	{
		shape->rotateRight();
		
		if (checkCollision() == true)
		{
			shape->resetPos();
		}

		isRotate = false;
	}
}


bool Tetris::checkCollision()
{
	// collision!
	for (int i = 0; i < shape->getSquaresCount(); i++)
	{
		// Check if shape collide with left & right borders of game field 
		if (squares[i].x < 0 || squares[i].x >= FIELD_WIDTH)
		{
			return true; 
		}

		// Check if shape collide with bottom border of game field
		else if (squares[i].y >= FIELD_HEIGHT)
		{
			return true;
		}
		
		// Check if shape collide with squares on the way
		else if (field[squares[i].y][squares[i].x] != 0)
		{
			return true;
		}
	}

	// no collision!
	return false;
}


void Tetris::destroyFullRow()
{
	int k = FIELD_HEIGHT - 1;
	for (int y = FIELD_HEIGHT - 1; y > 0; y--)
	{
		int count = 0;
		for (int x = 0; x < FIELD_WIDTH; x++)
		{
			if (field[y][x] != 0)
			{
				count++;
			}

			if (count == FIELD_WIDTH)
			{
				score++;
				std::cout << " Row destroyed! Score = " << score << std::endl;
			}
			
			field[k][x] = field[y][x];
		}
		
		if (count < FIELD_WIDTH)
		{
			k--;
		}
	}
}


void Tetris::drawObjects()
{
	window.draw(sprite_background);
	window.draw(sprite_frame);

	// Draw squares that are attached to the field
	for (int i = 0; i < FIELD_HEIGHT; i++)
	{ 
		for (int j = 0; j < FIELD_WIDTH; j++)
		{
			if (field[i][j] == 0) 
				continue;
			
			sprite_tiles.setTextureRect(IntRect(field[i][j] * DOT_PIXELS, 0, DOT_PIXELS, DOT_PIXELS)); // color
			sprite_tiles.setPosition(j * DOT_PIXELS, i * DOT_PIXELS); // position
			sprite_tiles.move(28, 31); // offset
			window.draw(sprite_tiles);
		}
	}
	
	// Draw a controlled shape
	for (int i = 0; i < shape->getSquaresCount(); i++)
	{
		sprite_tiles.setTextureRect(IntRect(colorNum * DOT_PIXELS, 0, DOT_PIXELS, DOT_PIXELS)); // color
		sprite_tiles.setPosition(squares[i].x * DOT_PIXELS, squares[i].y * DOT_PIXELS); // position
		sprite_tiles.move(28, 31); // offset

		window.draw(sprite_tiles);
	}
}


void Tetris::restartGame()
{
	for (int i = 0; i < FIELD_WIDTH; i++)
	{
		if (field[0][i] != 0)
		{
			for (int y = 0; y < FIELD_HEIGHT; y++)
			{
				for (int x = 0; x < FIELD_WIDTH; x++)
				{
					field[y][x] = 0;
				}
			}

			score = 0;
			std::cout << " Restart" << std::endl;
		}
	}
}

