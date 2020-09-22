#include "Map.h"
#include "Snake.h"


using namespace std;

const unsigned int MAP_WIDTH = 30;
const unsigned int MAP_HEIGHT = 20;

int main()
{
	Snake snake(3);
	Map map(snake, MAP_WIDTH, MAP_HEIGHT);
	map.run();
}

