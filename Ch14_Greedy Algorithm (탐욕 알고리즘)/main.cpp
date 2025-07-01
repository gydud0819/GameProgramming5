/*
* �ۼ��� : 2025-07-01
* ���� : Ž�� �˰���
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <chrono>

using namespace std;


/*
* Ž�� �˰���
* ���� Ǯ�� ����� �ϳ�
* ������ �ظ� ã�� ���ؼ� ���� ��Ȳ���� ���� �ּ��� ����� ����ؼ� �����ϴ� ���
*/

/*
* 1, 2, 3�� ����
* ������ �Ž��� �ִ� ����
* n���� �������θ� �Ž��� ����ϴµ� ������ ����
* 500��, 100��, 50�� 10���� �ְ�, �� �� ������ �ּ����� ������ �Ž����ְ�ͤ��� ��
* n���� �Ž��� �ֱ� ���� ������ �ּ� ���� n ��ȯ�ϱ�

*/
#pragma region ���� �Ž��� �ִ� ����
// 1260���� �������θ� �Ž��� ����� �� �ּ����� ������ �ַ��� ��� �ؾ��ұ�
// ���� ��Ȳ���� ���� �ּ��� �����ϰ� ���� �� (IDEA) (Greedy)
// 500�� a, 100�� b, 50�� c, 10�� d				a+b+c+d ��ȯ�ϱ� 2+2+1+1
int CoinBack(int amount)		// amount �Ž��� ����ϴ� �� �ݾ�
{
	// amount ������ ������ ��ġ�� �����ؾ� �Ѵ�.
	// ��� �������� ����ؼ� a,b,c,d�� ǥ���ϰ� �� ���� �����ϱ�

	// �ݺ��Ǵ� �κ��� for�� ������ ����ϱ� 

	/*
	* vector int�� �����ϴ� ���� �ƴ϶� coin �ڷ����� ���� ǥ���ϱ�
	*/

	struct Coin
	{
		int value;
		int count;

		Coin(int _value) : value(_value), count(0) {}
	};

	// CointWallet �̸����� Coin�� ������ ���ÿ� �߰��ϱ�


	vector<int> coins = { 500,100,50,10 };
	// coins �ڷᱸ���� ���� ū ������� ������ �Ǿ�� �Ѵ�. 
	// ������������ ���Ľ�Ű�� �ڵ�
	int totalCount2 = 0;
	vector<Coin> coinwallet;
	for (int coin : coins)
	{
		coinwallet.emplace_back(coin);
	}

	for (auto& elem : coinwallet)
	{
		int num = amount / elem.value;
		elem.count = num;
		totalCount2 += num;
		amount = amount % elem.value;

		cout << elem.value << "���� �� : " << elem.count << endl;
	}

	int totalCount = 0;
	for (int coin : coins)
	{
		int num = amount / coin;		// �ѱݾ��� coin���� �����ش�.
		totalCount += num;
		amount = amount % coin;			// 

		cout << coin << "���� �� : " << num << endl;
	}

	cout << "������ �� ���� : " << totalCount << endl;

	// ���� �ۼ��� �ڵ�
	//int Won = amount;		// ���� �ݾ�

	//int a = Won / 500;		// �̷��� ������ ����ؾ��Ѵٰ�?
	//cout << "500���� �� : " << a << endl;

	//Won = Won - 500 * a;

	//int b = Won / 100;
	//cout << "100���� �� : " << b << endl;
	//Won -= 100 * b;

	//int c = Won / 50;
	//cout << "50���� �� : " << c << endl;
	//Won -= 50 * c;

	//int d = Won / 10;
	//cout << "10���� �� : " << d << endl;
	//Won -= 10 * d;

	//int totalCount = a + b + c + d;
	//cout << "������ �� ���� : " << totalCount << endl;

	return totalCount;


}
#pragma endregion


#pragma region ȸ�ǽ� ���� ����
/*
* ȸ�ǽ��� �����ϴ� �ð��� ������ �ð��� ������ �����ϵ��� �� ���� n�� �־�����.
* �� ȸ�ǽ��� �ִ�� �����ϴ� ��� ã�ƺ���
* �ִ�� ������ �� ����� ������ �� �ִ���
* � ������� ���� �� �ּ����� ������ �� �ִ���
*/

/*
* ���� 1931 ����
*
* 1. ���۽ð��� ���� ���� ������ �����Ѵ�.
* 2. ������ �ð��� �������� ������ �����Ѵ�.
* (ù��° ���Ҹ� ����Ѵ�)
*/

int meetingCount(int n)
{
	// ���۽ð��� ������ �ð��� �տ� ������ �ڿ� ������ ������ �����ؼ� ǥ���ϱ�

	vector<pair<int, int>> meeting = { {4,1}, {5,3}, {6,0}, { 7,5 }, {8,3}, {9,5}, {10,6}, { 11,8 }, {12,8}, {13,2}, { 14,12 } };

	// ������ �ð� ������ �����Ѵ�. ������ �ð��� key���� first�� �����ߴ�.
	sort(meeting.begin(), meeting.end());

	// ���� ��Ű�� �� ���� �����

	for (auto& i : meeting)
	{
		cout << i.first << "," << i.second << "||";
	}

	// (������ �ð�, ���� �ð�)
	// count�� 1�� ������Ų��.
	// time ���� ȸ�ǿ��� �����ϴ� �ð�
	// ���� ���õ� ȸ�ǿ� ������ �ð����� �������ֱ� 
	// time�� ���õ� ȸ�ǿ� ������ �ð����� �������ָ� �ȴ�.

	int count = 1;
	int time = meeting[0].first;	// ù��° �ð��� ������ �ð� 

	for (int i = 1; i < n; i++)
	{
		// ���� ���õ� �ð� ���ϱ� (������ �����߿��� ���۽ð��� ���� ���õ� �ð�)
		if (time <= meeting[i].second)
		{
			// ���� 1���� ��Ű��
			count++;
			// time�� ���õ� �ð����� �����ϱ�
			time = meeting[i].first;
		}

	}

	return count;
}

#pragma endregion

#pragma region 
/*
* ���۽ð�, ������ �ð��� '��'������ ����ϱ�		3600-1800-1800
* ���� �ʸ� �ٽ� '��' '��' '��'�� ��ȯ�ؼ� ����ϴ� �ڵ� �����
* [n�� n�� n��] ������ִ� �ڵ� �ۼ��ϱ�
*/

void FormatTime(int value)
{
	// 2167 -> �� �� �ʷ� ��ȯ�ϴ� �ڵ� ����� 

	struct Time
	{
		int value;
		int count;

		Time(int _value) : value(_value) {}
	};

	// value -> �� �� �� ����� �����ϱ�
	vector<int> times;		// �� : 3600��==1�ð� ��
		times.emplace_back(3600);
		times.emplace_back(60);
		times.emplace_back(1);
	
	for (auto& time : times)
	{
		int num = value / time.value;
	}



	cout << "��" << "��" << "��" << endl;
}
#pragma endregion



int main()
{
	cout << "���� �Ž����ֱ� ���� : 1260���� ��ȯ�ϱ�" << endl;
	cout << "�����" << endl;
	CoinBack(1260);

	cout << endl;

	cout << "ȸ�ǽ� �ִ� ���� ����" << endl;
	meetingCount(11);

	cout << "���� �ð����� ��ȯ�ϴ� ����" << endl;
	//FormatTime
	return 0;
}