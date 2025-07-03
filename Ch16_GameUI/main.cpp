/*
* �ۼ���	: 2025-07-03
* ����	: gameUI ���־������� �����ϱ�
*/
#include <iostream>
#include <Windows.h>

using namespace std;

/*
* �ܼ� â ���� �����ϴ� ��ɵ�
* ANSI ESCAPE ������ ���� �����ϴ� ��� �����
*
* ��ǥ : ���ڷ� ǥ���ϴ� ���� �ƴ� ����� �˾ƺ��� ������ Ŭ���� �����
* Helper Ŭ����
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

const string Color::RESET = "\033[0m";		// �ʱ�ȭ ���ִ� �ڵ� 
const string Color::UNDERLINE = "\033[4m";	// ���ڿ� ���� �׾��ִ� �ڵ�

// �ؽ�Ʈ ���� 	30 ~ 37 : ���� ��
const string Color::BLACK = "\033[30m";
const string Color::RED = "\033[31m";
const string Color::GREEN = "\033[32m";
const string Color::YELLOW = "\033[33m";
const string Color::BLUE = "\033[34m";
const string Color::MAGENTA = "\033[35m";
const string Color::CYAN = "\033[36m";
const string Color::WHITE = "\033[37m";

// ��� ����  41 ~ 47 : ����
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
	cout << Color::BG_GREEN << Color::MAGENTA << "[ ���ӽ��� ]" << Color::RESET << endl;
	cout << Color::BG_BLUE << Color::CYAN << "[ �ҷ����� ]" << Color::RESET << endl;
	cout << Color::BG_RED << Color::WHITE << "[ �������� ]" << Color::RESET << endl;

	cout << endl;

}

void PrintProgressBar(int current, int total, int width = 40)
{
	float progress = float(current) / total;		// float Ÿ������ ����ȯ 
	int filded = (int)(width * progress);

	for (int i = 0; i < filded; i++)
	{
		cout << Color::YELLOW << "��";

	}

	for (int i = filded; i < width; i++)
	{
		cout << Color::WHITE << "��";

	}

	cout << Color::RESET << (int)(progress * 100) << " %";
}

void LoadingAnmation()		// �ϳ��� ǥ���ϰ� ������ ������
{
	cout << "�ε� ���� ��Ȳ �׷��ֱ�" << endl;

	for (int i = 0; i < 20; i++)
	{
		PrintProgressBar(i, 20);
		cout << endl;
		cout.flush();
		Sleep(100);

	}

	// vector�ڷᱸ���� ������Ȳ�� �׸����� �����ߴٰ� �����غ��� 
}

void DrawBox()
{
	/*
	* �ݺ����� �̿��ؼ� ǥ���ϱ� 
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
	//cout << Color::MAGENTA << "\033[47m" << "����" << Color::RESET << endl;		// ���ڰ� ������ ����� ������ �� ����
	////cout << "\033[33m" << "����" << "\033[0m" << endl;		// ���� ��ü�� ���� ������ �� ����
	//cout << Color::CYAN << "����" << Color::RESET << endl;		// ���� ��ü�� ���� ������ �� ����
	//cout << Color::YELLOW << "����" << Color::RESET << endl;		// ���ڿ� ������ ���� �� ����
	//cout << Color::BG_BLUE << Color::CYAN << "===Title===" << Color::RESET << endl;
	//Color::Print(Color::BG_BLUE, Color::GREEN, "===Title===");

	// �ε���, �޴� ǥ��, ���� UI �����ϱ�

	// Color Ŭ������ ����ؼ� ����, ���� ����, ���� ���� �����
	PrintMenu();


	// ���� �� �ε��� �����
	LoadingAnmation();

	DrawBox();

	return 0;
}