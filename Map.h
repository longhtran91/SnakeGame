#include "Snake.h"

#pragma once
class Map
{
private:
	Snake snake;
	unsigned int width;
	unsigned int height;
	unsigned int size;
	int *map; 
	bool running;
	void buildMap();
	char getMapGraphicChar(int value);
	void drawGUI();
	void clearScreen();
	void generateFood();
	void moveSnake(int x, int y);
	unsigned int getMapIndex(unsigned int x, unsigned int y);
	void computeSnakeAnimation();
public:
	Map(Snake snake, unsigned int width, unsigned int height);
	~Map();
	void run();
	
};