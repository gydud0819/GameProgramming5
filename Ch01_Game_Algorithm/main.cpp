
/*
* 게임에서 위치를 표현하는 방법 (2D)
* map -> 2차원 배열로 만들기
* ex. 미로 찾기 (maze), 탈출구까지 이동하는 코드 작성하기
*/
#include <iostream>
#include <vector>
#include <Windows.h>

using namespace std;

#define SIZE 10

const int dx[4] = { 0,0,-2,2 };		// 방향
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

// 0은 길, 1은, 벽
// 입구 (x,y) = (1,0) 
// 출구 (x,y) = (9,5)
int maze[SIZE][SIZE] =		// 앞이 y, 뒤가 x
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

// maze[y][x] 의 값이 0이면 '  ', 1이면 '■'를 표현하는 코드 만들기
int main()
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE;i++)
		{

			if (maze[j][i] == 1)
			{
				cout << "■";
			}
			else if (maze[j][i] == 0)
			{
				cout << "  ";
			}

		}
		cout << endl;

	}
#pragma region 이동할 길을 미리 만들기
	//vector<int> direction = { 1,1,1,3,1,3,3,1,3,3,3,3,3 };		// 밑으로 내려가는게 1, 오른쪽 이동은 3, 왼쪽 이동은 2, 위로 이동은 -1
	//int sx = 2; int sy = 0;
	//GotoXY(sx, sy);

	//cout << "★";

	//int pre_x = sx;		// 잔상 해결하는 변수
	//int pre_y = sy;


	////direction 숫자를 받아와서 GotoXY의 좌표 변경하기
	//for (int i = 0; i < direction.size(); i++)
	//{
	//	GotoXY(pre_x, pre_y);	// 움직이는 잔상을
	//	cout << "  ";			// "  "로 지우라는 의미

	//	int dir = direction[i];
	//	sx += dx[dir];		// 아래로 이동하는 x
	//	sy += dy[dir];

	//	pre_x = sx;	
	//	pre_y = sy;

	//	GotoXY(sx, sy);
	//	cout << "★";

	//	//pre_x, pre_y: 이전 위치 값 저장하고 이전 위치를 빈 공간에다 다시 그리기
	//	//cout<<"  "<<;

	//	Sleep(500);
	//}

#pragma endregion

#pragma region 길을 따라 이동하는 몬스터
	//1. 정해진 길을 따라 몬스터가 차례대로 나오는 코드 작성하기(디펜스 게임)
	//* vector<int> path = { }

	vector<int> path = { 1,1,1,3,1,3,3,1,3,3,3,3,3 };		// 밑으로 
	int monster_count = 5;	// 전체 몬스터 총 개수
	int interval = 2;		// 몬스터 생성 주기
	int steps = path.size() + monster_count;	// 전체 몬스터의 이동 거리
	int sx = 2; int sy = 0;
	vector<Monster> monsters;

	for (int i = 0; i < steps; i++)
	{
		if (i % interval == 0 && monsters.size() < monster_count)
		{
			monsters.emplace_back(sx, sy, path);		// emplace_back 사용시 생성자로 값을 넣을 수 있음 
		}
	}
	

	GotoXY(sx, sy);

	cout << "★";

	int pre_x = sx;		// 잔상 해결하는 변수
	int pre_y = sy;


	//direction 숫자를 받아와서 GotoXY의 좌표 변경하기
	for (int i = 0; i < monsters.size(); i++)
	{
		Monster& monster = monsters[i];

		if (monster.step >= monster.direction.size())
		{
			continue;
		}

		GotoXY(monster.pre_x, monster.pre_y);	// 움직이는 잔상을
		cout << "  ";							// "  "로 지우라는 의미

		int dir = monster.direction[monster.step];
		monster.x += dx[dir];		// 아래로 이동하는 x
		monster.y += dy[dir];

		monster.pre_x = monster.x;
		monster.pre_y = monster.y;

		GotoXY(sx, sy);
		cout << "★";

		//pre_x, pre_y: 이전 위치 값 저장하고 이전 위치를 빈 공간에다 다시 그리기
		//cout<<"  "<<;

		Sleep(500);
	}

#pragma endregion


/*
* 1. 정해진 길을 따라 몬스터가 차례대로 나오는 코드 작성하기 (디펜스 게임)
* vector<int> path = { } 
* 
* 2. 여러 몬스터가 각자의 방향으로 움직이는 코드 작성하기
* 
* 3. 맵에 따라 도착지점을 자동으로 찾아주는 작성하기 (실제 코딩테스트 문제)
*/

}
// 방향(상, 하, 좌, 우)
// 상 : x=0, y= -1
// 하 : x=0, y= 1
// 좌 : x=-1, y=0
// 우 : x=1, y=0

