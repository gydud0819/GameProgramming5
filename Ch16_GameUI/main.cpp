/*
* 작성일	: 2025-07-03
* 주제	: gameUI 비주얼적으로 구현하기
*/
#include <iostream>
#include <Windows.h>
#include <InventoryDP.h>
#include <queue>
#include <string>

using namespace std;

/*
* 콘솔 창 색을 변경하는 기능들
* ANSI ESCAPE 문자의 색을 변경하는 기능 만들기
*
* 목표 : 숫자로 표기하는 것이 아닌 사람이 알아보기 쉽도록 클래스 만들기
* Helper 클래스
* ex) Color::White, Color::UnderLine, Color::BG_White
*/

class Color
{
public:
	static const string RESET;
	static const string UNDERLINE;

	static const string BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE;
	static const string BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE;

	static void Print(const string& BG, const string& textColor, const string& message)
	{
		cout << BG << textColor << message << Color::RESET;

	}
};

const string Color::RESET = "\033[0m";		// 초기화 해주는 코드 
const string Color::UNDERLINE = "\033[4m";	// 글자에 밑줄 그어주는 코드

// 텍스트 색상 	30 ~ 37 : 글자 색
const string Color::BLACK = "\033[30m";
const string Color::RED = "\033[31m";
const string Color::GREEN = "\033[32m";
const string Color::YELLOW = "\033[33m";
const string Color::BLUE = "\033[34m";
const string Color::MAGENTA = "\033[35m";
const string Color::CYAN = "\033[36m";
const string Color::WHITE = "\033[37m";

// 배경 색상  41 ~ 47 : 배경색
const string Color::BG_RED = "\033[41m";
const string Color::BG_GREEN = "\033[42m";
const string Color::BG_YELLOW = "\033[43m";
const string Color::BG_BLUE = "\033[44m";
const string Color::BG_MAGENTA = "\033[45m";
const string Color::BG_CYAN = "\033[46m";
const string Color::BG_WHITE = "\033[47m";

void PrintMenu()
{
	cout << "[ ===Title=== ]" << endl;
	cout << endl;
	cout << Color::BG_GREEN << Color::MAGENTA << "[ 게임시작 ]" << Color::RESET << endl;
	cout << Color::BG_BLUE << Color::CYAN << "[ 불러오기 ]" << Color::RESET << endl;
	cout << Color::BG_RED << Color::WHITE << "[ 게임종료 ]" << Color::RESET << endl;

	cout << endl;

}

void PrintProgressBar(int current, int total, int width = 40)
{
	float progress = float(current) / total;		// float 타입으로 형변환 
	int filded = (int)(width * progress);

	for (int i = 0; i < filded; i++)
	{
		cout << Color::YELLOW << "■";

	}

	for (int i = filded; i < width; i++)
	{
		cout << Color::WHITE << "■";

	}

	cout << Color::RESET << (int)(progress * 100) << " %";
}

void LoadingAnmation()
{
	const int total = 20;		// 게임을 받아올 때 자주 사용 
	const int width = 30;

	cout << "로딩 진행 현황 그려주기" << endl;

	for (int i = 0; i <= total; i++)
	{
		system("cls");
		PrintProgressBar(i, total, width);
		cout << endl;
		cout.flush();
		Sleep(100);

	}

	// vector자료구조에 진행현황을 그림으로 저장했다가 갱신해보기 
}

void DrawBox(int width, int height)
{
	/*
	* 반복문을 이용해서 표현하기
	*/

	// 머리부분
	cout << Color::BG_CYAN << "+";
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}
	cout << "+" << Color::RESET << endl;

	for (int y = 0; y < height; y++)
	{
		// 왼쪽 기둥

		cout << Color::BG_CYAN << Color::WHITE << "|";

		// 공백
		for (int x = 0; x < width; x++)
		{
			cout << " ";
		}
		// 오른쪽 벽
		cout << Color::BG_CYAN << Color::WHITE << "|";
		cout << endl;
	}

	// 꼬리부분
	cout << Color::BG_CYAN << "+";
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}
	cout << "+" << Color::RESET << endl;
	//cout << Color::BG_CYAN << "+--------+" << Color::RESET << endl;
}
void GotoXY(int x, int y)
{
	COORD pos{ x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 도형 그리기 + 위치 이동

void DrawBox(int px, int py, int width, int height, const ItemW& item)
{
	/*
	* 반복문을 이용해서 표현하기
	*/

	// 머리부분
	GotoXY(px, py);
	cout << Color::BG_CYAN << "+";
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}

	cout << "+" << Color::RESET << endl;

	for (int y = 0; y < height; y++)
	{
		GotoXY(px, py + 1 + y);
		// 왼쪽 벽
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");

		// 아이템 정보 출력하기 (박스 안에)
		string content = " ";

		if (y == 1)
		{
			content = "이름 : " + item.GetName();
		}
		else if (y == 2)
		{
			content = "무게 : " + to_string(item.GetWeight());

		}
		else if (y == 3)
		{
			content = "가치 : " + to_string(item.GetValue());
		}

		if (!content.empty())
		{
			cout << Color::GREEN << content;
			for (int i = content.length(); i < width; i++)		// content의 길이만큼 
			{
				cout << " ";
			}
		}
		else
		{
			// 공백
			for (int i = 0; i < width; i++)
			{
				cout << " ";
			}
		}
		// 오른쪽 벽
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");
		cout << endl;
	}

	// 바닥부분
	GotoXY(px, py + height + 1);
	cout << Color::BG_CYAN << "+";
	for (int i = 0; i < width; i++)
	{

		cout << "-";
	}

	cout << "+" << Color::RESET << endl;
}

void TestI(const ItemW& item)
{
	cout << item.GetName() << endl;
}

void ProcedualDrawBox(int startX, int startY, vector<ItemW>& items)
{
	queue<ItemW> itemQ;
	itemQ.push(ItemW("망토", 40, 20));
	itemQ.push(ItemW("팬던트", 90, 30));
	itemQ.push(ItemW("반지", 50, 15));
	itemQ.push(ItemW("상의", 40, 20));
	itemQ.push(ItemW("하의", 90, 30));
	itemQ.push(ItemW("신발", 50, 15));
	itemQ.push(ItemW("부스터", 40, 20));
	itemQ.push(ItemW("펫", 90, 30));
	itemQ.push(ItemW("스페셜", 50, 15));

	

	for (auto& item : items)
	{
		itemQ.push(item);
	}
	
		
	int currentRow = 0;		// 현재 그려야 하는 도형의 x좌표
	int currentCol = 0;		// 현재 그려야 하는 도형의 y좌표

	const int box_Width = 15;
	const int box_Height = 6;
	const int box_RowSpacing = 5;
	const int box_ColSpacing = 5;

	while (!itemQ.empty())
	{
		ItemW current = itemQ.front();
		itemQ.pop();
		//TestI(current);
		
		// 3x3 박스로 아이템이 그려지도록 코드 작성하기 

		int boxX = startX + (currentRow * (box_RowSpacing + box_Width));
		int boxY = startY + (currentCol * (box_ColSpacing + box_Height));

		DrawBox(boxX, boxY, box_Width, box_Height, current);

		currentRow++;
		if (currentRow >= 4)
		{
			currentRow = 0;
			currentCol++;
		}

		Sleep(100);
		// ItemW 타입을 사용하는 함수 만들기
	}
}

int main()
{
	//cout << Color::MAGENTA << "\033[47m" << "글자" << Color::RESET << endl;		// 글자가 나오는 배경을 변경할 수 있음
	////cout << "\033[33m" << "글자" << "\033[0m" << endl;		// 글자 자체의 색을 변경할 수 있음
	//cout << Color::CYAN << "글자" << Color::RESET << endl;		// 글자 자체의 색을 변경할 수 있음
	//cout << Color::YELLOW << "글자" << Color::RESET << endl;		// 글자에 밑줄을 그을 수 있음
	//cout << Color::BG_BLUE << Color::CYAN << "===Title===" << Color::RESET << endl;
	//Color::Print(Color::BG_BLUE, Color::GREEN, "===Title===");

	// 로딩바, 메뉴 표시, 게임 UI 구현하기

	// Color 클래스를 사용해서 제목, 게임 시작, 게임 종료 만들기
	PrintMenu();


	// 게임 속 로딩바 만들기
	LoadingAnmation();
	//system("cls");
	//DrawBox(10, 10);

	//DrawBox(5, 5, 12, 3);			// x 간격은 20정도면 충분
	//
	//DrawBox(25, 5, 12, 3);
	//
	//DrawBox(45, 5, 12, 3);

	//int startX = 5;
	//int startY = 5;
	//
	//ItemW item("망치", 5, 10);
	//for (int i = 0; i < 4; i++)
	//{
	//	DrawBox(startX + 20 * i, startY /*+ 10 * i*/, 12, 5, item);
	//}

	InventoryW inventory(7);

	ItemW A("A", 6, 13);
	ItemW B("B", 4, 8);
	ItemW C("C", 3, 6);
	ItemW D("D", 5, 12);

	vector<ItemW> selectable{ A,B,C,D };
	//cout << "주어진 아이템의 최대 가치 : " << inventory.findBestItem(7, selectable);
	pair<int, vector<ItemW>> bestItems = inventory.findBestItem(7, selectable);

	cout << "주어진 아이템의 최대 가치 : " << bestItems.first << endl;
	vector<ItemW> ItemC = bestItems.second;

	ProcedualDrawBox(5,5, ItemC);

	return 0;
}