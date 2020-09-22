#pragma once
class Snake
{
private:
	unsigned int headX;
	unsigned int headY;
	unsigned int direction;
	unsigned int initialLength;
	unsigned int length;
public:
	Snake();
	Snake(unsigned int intialLength);
	unsigned int getHeadX();
	void setHeadX(unsigned int x);
	unsigned int getHeadY();
	void setHeadY(unsigned int y);
	void computeDirection(char key);
	void increaseLength(int value);
	unsigned int getDirection();
	unsigned int getLength();
	unsigned int getInitialLength();
};
