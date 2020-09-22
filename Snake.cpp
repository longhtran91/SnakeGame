#include "Snake.h"
enum DIRECTION { UP, DOWN, LEFT, RIGHT };

Snake::Snake()
{

}

Snake::Snake(unsigned int initialLength)
{
	this->length = initialLength;
	this->initialLength = initialLength;
	this->direction = UP;
}

unsigned int Snake::getHeadX()
{
	return this->headX;
}

void Snake::setHeadX(unsigned int x)
{
	this->headX = x;
}

unsigned int Snake::getHeadY()
{
	return this->headY;
}

void Snake::setHeadY(unsigned int y)
{
	this->headY = y;
}

void Snake::computeDirection(char key)
{
	switch (key)
	{
	case 'w':
		if (this->direction != DOWN) this->direction = UP;
		break;
	case 'd':
		if (this->direction != LEFT) this->direction = RIGHT;
		break;
	case 's':
		if (this->direction != UP) this->direction = DOWN;
		break;
	case 'a':
		if (this->direction != RIGHT) this->direction = LEFT;
		break;
	}
}

void Snake::increaseLength(int value)
{
	this->length += value;
}

unsigned int Snake::getDirection()
{
	return this->direction;
}

unsigned int Snake::getLength()
{
	return this->length;
}

unsigned int Snake::getInitialLength()
{
	return this->initialLength;
}
