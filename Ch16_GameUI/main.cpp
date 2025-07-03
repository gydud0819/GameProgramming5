/*
* 작성일	: 2025-07-03
* 주제	: gameUI 비주얼적으로 구현하기
*/
#include <iostream>
#include <Windows.h>

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
		cout << BG << textColor << "===Title===" << Color::RESET << endl;

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

void LoadingAnmation()		// 하나로 표현하고 싶은데 ㅇㅅㅇ
{
	cout << "로딩 진행 현황 그려주기" << endl;

	for (int i = 0; i < 20; i++)
	{
		PrintProgressBar(i, 20);
		cout << endl;
		cout.flush();
		Sleep(100);

	}

	// vector자료구조에 진행현황을 그림으로 저장했다가 갱신해보기 
}

void DrawBox()
{
	/*
	* 반복문을 이용해서 표현하기 
	*/
	cout << Color::BG_CYAN << "+---------+" << Color::RESET << endl;
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << "         " << endl;
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << endl;
	cout << "         " << endl;
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << endl;
	cout << "         " << endl;
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << endl;
	cout << "         " << endl;
	Color::Print(Color::BG_CYAN, Color::WHITE, "|");
	cout << endl;
	cout << "+---------+" << endl;
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

	DrawBox();

	return 0;
}