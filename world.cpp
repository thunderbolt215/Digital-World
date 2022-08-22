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


	//��ʼ�ϰ�����
	srand(time(nullptr)); // �õ�ǰʱ����Ϊ����
	int min = OccupancyNum / 30, max = OccupancyNum / 20;//����������Ӱ���ϰ�����ɢ�̶�
	//int min = 200, max = 280;
	int OccupancyInitNum = (rand() % (max - min)) + min;//��Χ[min,max)
	//randomValue = (rand() % (max - min + 1)) + min;//��Χ[min,max]
	//randomValue = (rand() % (max - min)) + min + 1;//��Χ(min,max]

	//���ɳ�ʼ�ϰ���
	for (OccupancyCnt = 0; OccupancyCnt < OccupancyInitNum; ) {

		//srand(time(nullptr));
		//�����ϰ����λ��
		int OccupancyRow = rand() % height;
		int OccupancyCol = rand() % width;
		if (map.map_ptr[OccupancyRow * height + OccupancyCol] == 0) {
			map.map_ptr[OccupancyRow * height + OccupancyCol] = 1;
			OccupancyCnt++;
		}

	}

	//ѭ�����
	while (OccupancyCnt < OccupancyNum)
	{
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				//�������ϰ�����չ
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

	//�������ʼ������������յ�,��֤��ͨ
	srand(time(nullptr)); // �õ�ǰʱ����Ϊ����
	for (int id = 0; id < num_of_agents; id++)
		agents[id].Initialize(height, width, map.map_ptr);

}

short* World::getMap() {
	return map.map_ptr;
}

bool World::showMap() {
	auto map_buf = getMap();
	if (map_buf == nullptr) {
		cout << "�޳�ʼ����ͼ" << endl;
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
	//�����������·��������
	for (int id = 0; id < num_of_agents; id++)
	{
		agents[id].getPath(height, width, map.map_ptr);
		
		//test: ���������·��
		cout << "Agent number: " << id << endl;
		agents[id].showPath(height, width, (short*)map.map_ptr);
	}
}



