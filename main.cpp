#include <iostream>
#include <cstdlib>
#include <ctime>
#include "world.h"
using namespace std;

int main() {
	const int height = 10;
	const int width = 10;

	//test
	World world;

	world.open();
	world.generate();
	world.showMap();

	//Agent test
	world.getGlobalOptimalPath();

	return 0;
}