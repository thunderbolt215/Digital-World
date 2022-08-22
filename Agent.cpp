#include "Agent.h"
#include "Astar.h"

int randnum(const int min, const int max)
{
	return (rand() % (max - min)) + min; //��Χ[min,max)
}

Agent::Agent()
{
	startx = starty = finishx = finishy = length_of_path = 0;
    movement = nullptr;
}

Agent::~Agent()
{
    free(movement);
}

void Agent::Initialize(const int height, const int width, const short* map)
{
    //srand(time(nullptr)); // �õ�ǰʱ����Ϊ����
    //cout << endl << height << " " << width << endl;
    movement = (int*)malloc(sizeof(int) * height * width * 3);

    while (1)
    {
        startx = randnum(0, height);
        starty = randnum(0, width);
        finishx = randnum(0, height);
        finishy = randnum(0, width);

        if (map[startx * height + starty] == 0 &&
            map[finishx * height + finishy] == 0 &&
            getPath(height, width, map))
            break;
    }
}

bool Agent::getPath(const int height, const int width, const short* map)
{
   // cout << endl << "start: (" << startx << "," << starty << ")" << endl
     //   << "finish: (" << finishx << "," << finishy << ")" << endl;
   /* cout << "map:" << endl;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            cout << map[row * height + col];
        }
        cout << endl;
    }*/
    

    //���Թ���ȵ�ʱ������ȷ�ģ�����ȿ��ܳ�����
    Astar astar(height, width);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (map[row * height + col] == 1)
                // ��������Ҫ������
                astar.setBlock({ col,row });
        }
    }

    if (astar.search(startx, starty, finishx, finishy)) {

        //cout << "entered" << endl;

        //�ҵ�ͨ·
        list<Node*> searchPath;
        // ��������Ҫ������
        Node* sNode = &astar.nodeMap[finishy][finishx];
        do
        {
            searchPath.push_front(sNode);
            sNode = sNode->parent;
        } while (sNode != nullptr);//���Ϊ��ָ��

        //cout << "step 1 completed" << endl;

        //��¼·��
        length_of_path = 0;
        for (auto& x : searchPath) {
            movement[length_of_path * num_of_props + 0] = x->x;
            movement[length_of_path * num_of_props + 1] = x->y;
            movement[length_of_path * num_of_props + 2] = 0;
            //cout << '(' << x->x << ',' << x->y << ')';
            length_of_path++;
        }
        //cout << "path recorded" << endl;

        //��¼��̬
        for (int id = 0; id < length_of_path-1; id++)
        {
            for (int dir = 0; dir < 4; dir++)
            {
                if (movement[id * num_of_props + 0] + direction[dir][0] == movement[(id + 1) * num_of_props + 0] &&
                    movement[id * num_of_props + 1] + direction[dir][1] == movement[(id + 1) * num_of_props + 1])
                {
                    movement[id * num_of_props + 2] = dir;
                    break;
                }
            }
        }
        movement[(length_of_path - 1) * num_of_props + 2] = movement[(length_of_path - 2) * num_of_props + 2];
        //showPath(height, width, (short*)map);
        return true;
    }
    else
    {
        //cout << "�޷����" << endl;
        return false;
    }
}

void Agent::showPath(const int height, const int width, const short* map)
{
    short tmp[500 * 500];
    char label[6] = { '0','1','^','v','<','>' };
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            tmp[row * height + col] = map[row * height + col];
        }
    }

    for (int id = 0; id < length_of_path; id++)
    {
        int x = movement[id * num_of_props + 0];
        int y = movement[id * num_of_props + 1];
        tmp[x * height + y] = movement[id * num_of_props + 2] + 2;
    }
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            cout << label[tmp[row * height + col]];
        }
        cout << endl;
    }
}