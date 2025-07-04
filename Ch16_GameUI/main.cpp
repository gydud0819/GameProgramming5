/*
* �ۼ���	: 2025-07-03
* ����	: gameUI ���־������� �����ϱ�
*/
#include <iostream>
#include <Windows.h>
#include <InventoryDP.h>
#include <queue>
#include <string>

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
		cout << BG << textColor << message << Color::RESET;

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

void LoadingAnmation()
{
	const int total = 20;		// ������ �޾ƿ� �� ���� ��� 
	const int width = 30;

	cout << "�ε� ���� ��Ȳ �׷��ֱ�" << endl;

	for (int i = 0; i <= total; i++)
	{
		system("cls");
		PrintProgressBar(i, total, width);
		cout << endl;
		cout.flush();
		Sleep(100);

	}

	// vector�ڷᱸ���� ������Ȳ�� �׸����� �����ߴٰ� �����غ��� 
}

void DrawBox(int width, int height)
{
	/*
	* �ݺ����� �̿��ؼ� ǥ���ϱ�
	*/

	// �Ӹ��κ�
	cout << Color::BG_CYAN << "+";
	for (int i = 0; i < width; i++)
	{
		cout << "-";
	}
	cout << "+" << Color::RESET << endl;

	for (int y = 0; y < height; y++)
	{
		// ���� ���

		cout << Color::BG_CYAN << Color::WHITE << "|";

		// ����
		for (int x = 0; x < width; x++)
		{
			cout << " ";
		}
		// ������ ��
		cout << Color::BG_CYAN << Color::WHITE << "|";
		cout << endl;
	}

	// �����κ�
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

// ���� �׸��� + ��ġ �̵�

void DrawBox(int px, int py, int width, int height, const ItemW& item)
{
	/*
	* �ݺ����� �̿��ؼ� ǥ���ϱ�
	*/

	// �Ӹ��κ�
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
		// ���� ��
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");

		// ������ ���� ����ϱ� (�ڽ� �ȿ�)
		string content = " ";

		if (y == 1)
		{
			content = "�̸� : " + item.GetName();
		}
		else if (y == 2)
		{
			content = "���� : " + to_string(item.GetWeight());

		}
		else if (y == 3)
		{
			content = "��ġ : " + to_string(item.GetValue());
		}

		if (!content.empty())
		{
			cout << Color::GREEN << content;
			for (int i = content.length(); i < width; i++)		// content�� ���̸�ŭ 
			{
				cout << " ";
			}
		}
		else
		{
			// ����
			for (int i = 0; i < width; i++)
			{
				cout << " ";
			}
		}
		// ������ ��
		Color::Print(Color::BG_CYAN, Color::WHITE, "|");
		cout << endl;
	}

	// �ٴںκ�
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
	itemQ.push(ItemW("����", 40, 20));
	itemQ.push(ItemW("�Ҵ�Ʈ", 90, 30));
	itemQ.push(ItemW("����", 50, 15));
	itemQ.push(ItemW("����", 40, 20));
	itemQ.push(ItemW("����", 90, 30));
	itemQ.push(ItemW("�Ź�", 50, 15));
	itemQ.push(ItemW("�ν���", 40, 20));
	itemQ.push(ItemW("��", 90, 30));
	itemQ.push(ItemW("�����", 50, 15));

	

	for (auto& item : items)
	{
		itemQ.push(item);
	}
	
		
	int currentRow = 0;		// ���� �׷��� �ϴ� ������ x��ǥ
	int currentCol = 0;		// ���� �׷��� �ϴ� ������ y��ǥ

	const int box_Width = 15;
	const int box_Height = 6;
	const int box_RowSpacing = 5;
	const int box_ColSpacing = 5;

	while (!itemQ.empty())
	{
		ItemW current = itemQ.front();
		itemQ.pop();
		//TestI(current);
		
		// 3x3 �ڽ��� �������� �׷������� �ڵ� �ۼ��ϱ� 

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
		// ItemW Ÿ���� ����ϴ� �Լ� �����
	}
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
	//system("cls");
	//DrawBox(10, 10);

	//DrawBox(5, 5, 12, 3);			// x ������ 20������ ���
	//
	//DrawBox(25, 5, 12, 3);
	//
	//DrawBox(45, 5, 12, 3);

	//int startX = 5;
	//int startY = 5;
	//
	//ItemW item("��ġ", 5, 10);
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
	//cout << "�־��� �������� �ִ� ��ġ : " << inventory.findBestItem(7, selectable);
	pair<int, vector<ItemW>> bestItems = inventory.findBestItem(7, selectable);

	cout << "�־��� �������� �ִ� ��ġ : " << bestItems.first << endl;
	vector<ItemW> ItemC = bestItems.second;

	ProcedualDrawBox(5,5, ItemC);

	return 0;
}