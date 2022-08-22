#pragma once

#include "map.h"
#include "Agent.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
//typedef struct MapStruct
//{
//	
//}Map;

//typedef struct AgentStruct
//{
//
//}Agent;

class World
{
public:
	World();
	~World();
	void generate();
	void open();
	short* getMap();
	bool showMap();

	void getGlobalOptimalPath();
private:
	/*地图参数*/
	const int height = 100;
	const int width = 100;

	/*智能体参数*/
	const int num_of_agents = 5;

	Map map;
	Agent agents[5];

	

};