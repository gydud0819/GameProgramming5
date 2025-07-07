/*
* 작성일	: 2025-07-07
* 주제	: 충돌 구현하기
*/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
* 충돌 :
* 면 : 사각형의 넓이, 경계
* bounding box
*/

struct Rectangle
{
	int x, y;
	int width, height;

	Rectangle(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) { }
};

// c++도 배치를 ㅅㅂ 
bool collisionCheck(Rectangle r1, Rectangle r2)
{
	bool xOverlap = (r1.x + r1.width >= r2.x) && (r1.x <= r2.x + r2.width);	// && 전부가 겹쳐야하는데 ||쓰면 둘중 하나라도 겹치면 겹친다라고 해도되지 않나 
	// case 1. 

	bool yOverlap = (r1.y + r1.height >= r2.y) && (r1.y <= r2.y + r2.height);

	bool IsCollision = xOverlap && yOverlap;

	if (IsCollision)	// 겹칠 때
	{
		cout << "겹칩니다." << endl;
		return true;
	}

	else
	{
		cout << "겹치지 않습니다." << endl;
		return true;
	}
}

class Bullet
{
public:
	Rectangle collider;
	bool IsCollision;

	Bullet(Rectangle& _col) : collider(_col), IsCollision(false) { }

	void IsCollisionCheck(const Bullet& other)
	{
		if (collisionCheck(collider, other.collider))
		{
			IsCollision = true;
		}
		else
		{
			IsCollision;
		}
		
	}
};

// 문제 1. 두 사각형이 겹치면 "겹칩니다" 출력을 하고
// 그렇지 않으면 "겹치지 않습니다" 출력을 하는 함수 만들기

// AABB 충돌
// Axis Ailgned Bounding box



// 구형 충돌 
// circle collisionCheck Detection
// 두 원의 원점, 반지름
// 원점 사이의 거리(distance) d = (피타고리스 정리를 이용해서 구하기)
// d =(<, = ,>) r1 + r2;

struct Circle
{
	// 원점
	// 반지름
	float x, y, r;
	// 생성자
	Circle(float _x, float _y, float _r) : x(_x), y(_y), r(_r) { }
};

bool CircleCheck(Circle c1, Circle c2)
{
	double dx = c1.x - c2.x;	// 가로의 길이를 제곱하고 더해준다. 음수 타입도 사용될 수 있어야 한다.
	double dy = c1.y- c2.y;	// 가로의 길이를 제곱하고 더해준다. 음수 타입도 사용될 수 있어야 한다.

	double distanceSq = (dx * dx) + (dy * dy);		// distance의 거리 제곱 

	bool IsCollision = sqrt(distanceSq) <= (c1.r + c2.r) * (c1.r + c2.r);
	if (IsCollision)
	{
		cout << "충돌한다." << endl;
		return true;
	}
	else
	{
		cout << "충돌하지 않는다." << endl;
		return true;
	}
}

// Ch16 DrawBox를 Ch17로 가져와서 그리기
// 두 사각형이 겹치는지 눈으로 확인하고 두 사각형이 겹친다면 충돌한 오브젝트를 그리지 않게 작성하기

int main()
{
	Rectangle r1(3, 3, 4, 4);
	Rectangle r2(8, 3, 4, 4);

	collisionCheck(r1, r2);

	cout << endl;

	Circle c1(1, 1, 3);
	Circle c2(3, 3, 2);

	CircleCheck(c1, c2);

	cout << endl;

	// 게임 충돌 사용 예시 
	Bullet bullet(r1);
	Bullet bullet2(r2);

	bullet.IsCollisionCheck(bullet2);
	cout << endl;

	if (bullet.IsCollision)
	{
		cout << "그리지 마세요." << endl;
	}
	else
	{
		cout << "그려라" << endl;
	}
}
