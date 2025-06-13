
/*
* ���ӿ��� ��ġ�� ǥ���ϴ� ��� (2D)
* map -> 2���� �迭�� �����
* ex. �̷� ã�� (maze), Ż�ⱸ���� �̵��ϴ� �ڵ� �ۼ��ϱ�
*/
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

#define SIZE 10

const int dx[4] = { 0,0,-2,2 };		// ����
const int dy[4] = { -1,1,0,0 };

struct Monster
{
	int x, y;
	int pre_x, pre_y;
	int step;
	vector<int> direction;

	Monster() = default;
	Monster(int x, int y, vector<int> direction) : x(x), y(y), direction(direction) 
	{
		pre_x = x;
		pre_y = y;
		step=0;
	}
};

void GotoXY(int x, int y)
{
	COORD pos{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 0�� ��, 1��, ��
// �Ա� (x,y) = (1,0) 
// �ⱸ (x,y) = (9,5)
int maze[SIZE][SIZE] =		// ���� y, �ڰ� x
{
	{1,0,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,1,0,0,1},
	{1,1,0,0,0,0,1,1,0,1},
	{1,0,0,1,0,0,0,0,0,0},
	{1,0,0,1,1,1,1,1,0,1},
	{1,0,1,1,0,0,1,0,0,1},
	{1,0,0,0,0,0,1,0,1,1},
	{1,1,1,1,1,1,1,1,1,1}
};

// maze[y][x] �� ���� 0�̸� '  ', 1�̸� '��'�� ǥ���ϴ� �ڵ� �����
int main()
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE;i++)
		{

			if (maze[j][i] == 1)
			{
				cout << "��";
			}
			else if (maze[j][i] == 0)
			{
				cout << "  ";
			}

		}
		cout << endl;

	}
#pragma region �̵��� ���� �̸� �����
	//vector<int> direction = { 1,1,1,3,1,3,3,1,3,3,3,3,3 };		// ������ �������°� 1, ������ �̵��� 3, ���� �̵��� 2, ���� �̵��� -1
	//int sx = 2; int sy = 0;
	//GotoXY(sx, sy);

	//cout << "��";

	//int pre_x = sx;		// �ܻ� �ذ��ϴ� ����
	//int pre_y = sy;


	////direction ���ڸ� �޾ƿͼ� GotoXY�� ��ǥ �����ϱ�
	//for (int i = 0; i < direction.size(); i++)
	//{
	//	GotoXY(pre_x, pre_y);	// �����̴� �ܻ���
	//	cout << "  ";			// "  "�� ������ �ǹ�

	//	int dir = direction[i];
	//	sx += dx[dir];		// �Ʒ��� �̵��ϴ� x
	//	sy += dy[dir];

	//	pre_x = sx;	
	//	pre_y = sy;

	//	GotoXY(sx, sy);
	//	cout << "��";

	//	//pre_x, pre_y: ���� ��ġ �� �����ϰ� ���� ��ġ�� �� �������� �ٽ� �׸���
	//	//cout<<"  "<<;

	//	Sleep(500);
	//}

#pragma endregion

#pragma region ���� ���� �̵��ϴ� ����
	//1. ������ ���� ���� ���Ͱ� ���ʴ�� ������ �ڵ� �ۼ��ϱ�(���潺 ����)
	//* vector<int> path = { }

	vector<int> path = { 1,1,1,3,1,3,3,1,3,3,3,3,3 };		// ������ 
	int monster_count = 5;	// ��ü ���� �� ����
	int interval = 2;		// ���� ���� �ֱ�
	int steps = path.size() + monster_count;	// ��ü ������ �̵� �Ÿ�
	int sx = 2; int sy = 0;
	vector<Monster> monsters;

	for (int i = 0; i < steps; i++)
	{
		if (i % interval == 0 && monsters.size() < monster_count)
		{
			monsters.emplace_back(sx, sy, path);		// emplace_back ���� �����ڷ� ���� ���� �� ���� 
		}

		//direction ���ڸ� �޾ƿͼ� GotoXY�� ��ǥ �����ϱ�
		for (int i = 0; i < monsters.size(); i++)
		{
			Monster& monster = monsters[i];

			if (monster.step >= monster.direction.size())
			{
				continue;
			}

			GotoXY(monster.pre_x, monster.pre_y);	// �����̴� �ܻ���
			cout << "  ";							// "  "�� ������ �ǹ�

			int dir = monster.direction[monster.step];
			monster.x += dx[dir];		// �Ʒ��� �̵��ϴ� x
			monster.y += dy[dir];

			monster.pre_x = monster.x;
			monster.pre_y = monster.y;

			GotoXY(sx, sy);
			cout << "��";

			//pre_x, pre_y: ���� ��ġ �� �����ϰ� ���� ��ġ�� �� �������� �ٽ� �׸���
			//cout<<"  "<<;

			Sleep(500);
		}
	}
	

	/*GotoXY(sx, sy);

	cout << "��";*/

	int pre_x = sx;		// �ܻ� �ذ��ϴ� ����
	int pre_y = sy;


	

#pragma endregion


/*
* 1. ������ ���� ���� ���Ͱ� ���ʴ�� ������ �ڵ� �ۼ��ϱ� (���潺 ����)
* vector<int> path = { } 
* 
* 2. ���� ���Ͱ� ������ �������� �����̴� �ڵ� �ۼ��ϱ�
* 
* 3. �ʿ� ���� ���������� �ڵ����� ã���ִ� �ۼ��ϱ� (���� �ڵ��׽�Ʈ ����)
*/

}
// ����(��, ��, ��, ��)
// �� : x=0, y= -1
// �� : x=0, y= 1
// �� : x=-1, y=0
// �� : x=1, y=0

