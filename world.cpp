#include "world.h"

World::World()
{
}

World::~World()
{
}

void World::open() 
{
	map.Initialize(height, width);
}

void World::generate()
{

	const int MapSize = height * width;
	const double OccupancyRate = 0.3;
	const int OccupancyNum = int(OccupancyRate * MapSize);

	int OccupancyCnt = 0;


	//初始障碍物数
	srand(time(nullptr)); // 用当前时间作为种子
	int min = OccupancyNum / 30, max = OccupancyNum / 20;//这两个参数影响障碍物离散程度
	//int min = 200, max = 280;
	int OccupancyInitNum = (rand() % (max - min)) + min;//范围[min,max)
	//randomValue = (rand() % (max - min + 1)) + min;//范围[min,max]
	//randomValue = (rand() % (max - min)) + min + 1;//范围(min,max]

	//生成初始障碍物
	for (OccupancyCnt = 0; OccupancyCnt < OccupancyInitNum; ) {

		//srand(time(nullptr));
		//生成障碍物的位置
		int OccupancyRow = rand() % height;
		int OccupancyCol = rand() % width;
		if (map.map_ptr[OccupancyRow * height + OccupancyCol] == 0) {
			map.map_ptr[OccupancyRow * height + OccupancyCol] = 1;
			OccupancyCnt++;
		}

	}

	//循环填充
	while (OccupancyCnt < OccupancyNum)
	{
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				//从已有障碍物扩展
				if (map.map_ptr[row * height + col] == 1) {
					//srand(time(nullptr));
					int row_d = rand() % 2 - 1;
					int col_d = rand() % 2 - 1;
					if (map.map_ptr[(row + row_d) * height + (col + col_d)] == 0
						&& (row + row_d) >= 0 && (row + row_d) < height
						&& (col + col_d) >= 0 && (col + col_d) < width) {
						map.map_ptr[(row + row_d) * height + (col + col_d)] = 1;
						OccupancyCnt++;
					}
				}

			}
		}
	}

	//智能体初始化，生成起点终点,保证连通
	srand(time(nullptr)); // 用当前时间作为种子
	for (int id = 0; id < num_of_agents; id++)
		agents[id].Initialize(height, width, map.map_ptr);

}

short* World::getMap() {
	return map.map_ptr;
}

bool World::showMap() {
	auto map_buf = getMap();
	if (map_buf == nullptr) {
		cout << "无初始化地图" << endl;
		return false;

	}
	else {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				cout << map_buf[row * height + col];
			}
			cout << endl;
		}

		return true;
	}

}


void World::getGlobalOptimalPath()
{
	//求出各智能体路径并保存
	for (int id = 0; id < num_of_agents; id++)
	{
		agents[id].getPath(height, width, map.map_ptr);
		
		//test: 输出智能体路径
		cout << "Agent number: " << id << endl;
		agents[id].showPath(height, width, (short*)map.map_ptr);
	}
}



