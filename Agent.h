#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Agent
{
public:
	Agent();
	~Agent();
	void Initialize(const int height, const int width, const short* map);
	bool getPath(const int height, const int width, const short* map);
	void showPath(const int height, const int width, const short* map);

	int startx, starty, finishx, finishy, length_of_path;
	int *movement;

private:

	const int direction[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };//用来生成节点周围上下左右的坐标
	const int UP = 0;
	const int DOWN = 1;
	const int LEFT = 2;
	const int RIGHT = 3;
	const int num_of_props = 3;


};