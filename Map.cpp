#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h> 
#include "Map.h"

using namespace std;

const char HORIZONTAL_WALL_BAR = char(205);
const char VERTICAL_WALL_BAR = char(186);
const char SNAKE_HEAD = 'O';
const char SNAKE_BODY = 'o';
const char FOOD = '*';
const char SPACE = ' ';
enum DIRECTION {UP, DOWN, LEFT, RIGHT};

Map::Map(Snake snake, unsigned int width, unsigned int height)
{
	this->snake = snake;
	this->width = width;
	this->height = height;
	this->size = width*height;
	this->map = new int[width*height];
	buildMap();
	this->running = true;
}

Map::~Map()
{
	if (this->map)
	{
		delete[] this->map;
	}
}

/* map values:						coordinates
>0: snake							-------x
0: free								|
-1: food							|
-2: horizontal wall					|
-3: vertical wall					y
*/
void Map::buildMap()
{
	unsigned int index;
	for (unsigned int y = 0; y < this->height; y++)
	{
		for (unsigned int x = 0; x < this->width; x++)
		{
			index = getMapIndex(x, y);
			if (y == 0 || y == this->height - 1)
			{
				this->map[index] = -2;
			}
			else
			{
				if (x == 0 || x == this->width - 1)
				{
					this->map[index] = -3;
				}
				else
				{
					this->map[index] = 0;
				}
			}
		}
	}
	this->snake.setHeadX(this->width / 2);
	this->snake.setHeadY(this->height / 2);
	index = getMapIndex(this->snake.getHeadX(), this->snake.getHeadY());
	generateFood(); //1st food
}

/* map values:
>0: snake
0: free
-1: food
-2: horizontal wall
-3: vertical wall
*/
char Map::getMapGraphicChar(int value)
{
	//snake
	if (value == this->snake.getLength())
	{
		return SNAKE_HEAD;
	}
	else if (value > 0)
	{
		return SNAKE_BODY;
	}

	//walls, space and food
	switch (value)
	{
	case 0: return SPACE;
	case -1: return FOOD;
	case -2: return HORIZONTAL_WALL_BAR;
	case -3: return VERTICAL_WALL_BAR;
	}
}

void Map::clearScreen()
{
	system("cls");
}

/* coordinates
-------x
|
|
|
y
*/
void Map::drawGUI()
{
	clearScreen();
	for (unsigned int y = 0; y < this->height; y++)
	{
		for (unsigned int x = 0; x < this->width; x++)
		{
			unsigned int index = getMapIndex(x, y);
			cout << getMapGraphicChar(map[index]);
		}
		cout << endl;
	}
}

void Map::run()
{
	while (this->running)
	{
		// If a key is pressed
		if (_kbhit())
		{
			// Change to direction determined by key pressed
			this->snake.computeDirection(_getch());
		}
		
		computeSnakeAnimation();

		drawGUI();

		Sleep(300);
	}

	// Print out game over text
	cout << "\t!!!Game over!" << endl << "\tYour score is: " << this->snake.getLength() - this->snake.getInitialLength();

	// Stop console from closing instantly
	cin.ignore();
}

/* map values:
>0: snake
0: free
-1: food
-2: horizontal wall
-3: vertical wall
*/
void Map::generateFood()
{
	unsigned int x;
	unsigned int y;
	unsigned int index;
	do
	{
		srand(time(0));
		x = rand() % (this->width - 2) + 1;
		srand(time(0));
		y = rand() % (this->height - 2) + 1;
		index = getMapIndex(x, y);

	} while (this->map[index] != 0);
	this->map[index] = -1;
}

void Map::moveSnake(int x, int y)
{
	unsigned int newX = this->snake.getHeadX() + x;
	unsigned int newY = this->snake.getHeadY() + y;
	unsigned int newIndex = getMapIndex(newX, newY);

	if (map[newIndex] == -1)
	{
		this->snake.increaseLength(1);
		generateFood();
	}
	// Check location is free
	else if (map[newIndex] == -2 || map[newIndex] == -3 || map[newIndex] > 0)
	{
		this->running = false;
	}
	this->snake.setHeadX(newX);
	this->snake.setHeadY(newY);
	map[newIndex] = this->snake.getLength() + 1;

	// Reduce snake values on map by 1
	for (unsigned int i = 0; i < this->size; i++)
	{
		if (map[i] > 0) map[i]--;
	}
}

void Map::computeSnakeAnimation()
{
	// Move in direction indicated
	switch (this->snake.getDirection())
	{
	case UP: moveSnake(0, -1);
		break;
	case RIGHT: moveSnake(1, 0);
		break;
	case DOWN: moveSnake(0, 1);
		break;
	case LEFT: moveSnake(-1, 0);
		break;
	}
}


// return index of array from x-y coordinates:
unsigned int Map::getMapIndex(unsigned int x, unsigned int y)
{
	return x + y*this->width;
}
