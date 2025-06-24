/*
* �ۼ���	: 2025-06-24
* ����	: �켱���� ť�� �̿��Ͽ� minHeap, maxHeap ���� �ۼ��ϱ�, rpg �������̵� ���� ��ġ ����� 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/*
* maxHeap, minHeap
* 1�� �켱���� ť�� �̿��Ͽ� �� ���� �ۼ��ϱ�
*/

bool myless(int a, int b)
{
	return a < b;
}

bool myGreater(int a, int b)
{
	return a > b;
}

// k��°�� ���� �� ���ϱ�, k��°�� ū �� ���ϱ⸦ �켱���� ť�� ����ϸ� ���� ǥ���� �� �ִ�.
// logN �ð����� k ��° ���� ���� ã�� �� �ִ�. -> (���� ���� ã�´�.

#pragma region MinHeap
class MinHeap
{
private:
	priority_queue<int, vector<int>, greater<int>> pq;			// �ּڰ��� ���� ���� �ö󰡴� ����
	/*priority_queue<int> pq2;*/
public:
	MinHeap() = default;
public:
	void Push(int value)
	{
		pq.push(value);
	}

	bool isEmpty() const
	{
		return pq.empty();
	}

	const int& Top() const	// ������ �ϴ� ���� : �� ����Ǿ��ִ� ���� ���� ���� ������ �ҰŶ� &�� ���δ�.
	{
		if (isEmpty())
		{
			throw runtime_error("priority Queue is Empty");
		}

		return pq.top();
	}

	int Pop()			// ���縦 �� ��, �ڷᱸ������ �����Ѵ�.
	{
		if (isEmpty())
		{
			throw runtime_error("priority Queue is Empty");
		}
		int minValue = pq.top();
		pq.pop();
		return minValue;
	}


};
#pragma endregion

#pragma region MaxHeap
class MaxHeap
{
private:
	priority_queue<int, vector<int>, less<int>> pq2;
public:
	MaxHeap() = default;
public:
	void Push(int value)
	{
		pq2.push(value);
	}

	bool IsEmpty() const
	{

		return pq2.empty();

	}

	const int& Top() const
	{
		if (IsEmpty())
		{
			throw runtime_error("priority Queue is empty");

		}

		return pq2.top();
	}

	int Pop()
	{
		if (IsEmpty())
		{
			throw runtime_error("priority Queue is Empty");
		}
		int maxValue = pq2.top();
		pq2.pop();
		return maxValue;
	}
};
#pragma endregion

#pragma region k��° ���� ã�� �Լ�
void FindKthExample()
{
	MinHeap minheap;

	minheap.Push(11);
	minheap.Push(7);
	minheap.Push(5);
	minheap.Push(3);

	cout << "�ּ� ���� ���� ���� �� : " << minheap.Top() << endl;

	int k = 3;

	// for �ݺ����� k�� ǥ���Ͽ� k��° �� ã��

	//cout << "k��° ���� �� ����ϱ� : " << endl;

	MaxHeap maxheap;
	maxheap.Push(11);
	maxheap.Push(7);
	maxheap.Push(5);
	maxheap.Push(3);

	cout << "�ִ� ���� ���� ū �� : " << maxheap.Top() << endl;
}
#pragma endregion

/*
* rpg ���� ���̵�
* 5����
* ����, ������, �ü�, ����, ������
* �� ������ ��ų�� ����� �� ���� ���� ��׷ΰ� �����Ѵ�.
* �� 5���� ���� ���ݸ��� ������ �켱������ �����ϴ��� ã�� ���� �ۼ��ϱ�
* �̋� ������ Ư�� ������ ������ �� ���� �� ������ ��׷δ� 0���� �ʱ�ȭ�ȴ�.
*
* 5���� ����		1		2		3		4		5
* ����	:		10		5		8		7		6
* ����	:
* �ü�	:
* ����	:
* ������	:
*
* ������ ��ų�� �����ϴ� ����
* ���� : ��Ƽ�ȿ��� ���� ���� �������ΰ�? ���� ���� �� �������ΰ�?
*
* 1. n���� ���� ���� �켱������ ���ϰ� ���� ū ������ ����Ѵ�.
* 2. heap �ڷᱸ���� ����ؼ� k��° ������ ã�´�.
*
* ������ ������ �������� 1�� ����� ȿ�����̴�.
* 2���� ����ؾ��ϴ�
*/


class Character
{
	string name;
	vector<int> threatLv;	//{10, 5, 8, 7, 6}
	int currentTurn;

public:
	Character() = default;
	Character(string name, vector<int> TLV) : name(name), threatLv(TLV), currentTurn(0) {}
	int GetCurrentThreat()
	{
		if (threatLv.size() <= currentTurn) return -1;		// -1�� �����ϸ� ������ �ǹ� 
		return threatLv[currentTurn];		// �迭�� �ִ� �� ��ȯ�ϱ� 
	}

	void NextTurn()
	{
		currentTurn++;		// ���� ������ �Ѿ������ 1�� ����
	}

	void PrintStat()
	{
		cout << name << "(���� ������ : " << GetCurrentThreat() << ")" << endl;
	}

	
};

class Boss
{
public:
	string name;
	int currentTurn;
	priority_queue<int> threatQ;
	Boss(string name) : currentTurn(0) {}

	void clear()
	{
		
		while (!threatQ.empty())
		{
			threatQ.pop();
		}
	}

	void UpdateThreatQ(vector<Character>& party)
	{
		clear();

		for (auto& character : party)
		{
			int threat = character.GetCurrentThreat();
			threatQ.push(threat);
			character.NextTurn();
		}
	}

	

	int FindMostThreatCharacter(vector<Character>* party)
	{
		//Character* target = nullptr;
		int MostThreatvalue = threatQ.top();

		return MostThreatvalue;

	}

};

void ThreatSystem()
{
	Character a("����", { 1,2,3,4,5 });
	Character b("�ü�", { 1,8,3,6,5 });
	Character c("����", { 3,3,3,3,3 });
	Character d("����", { 2,4,6,8,10 });
	Character e("������", { 1,3,5,7,9 });

	vector<Character> party;
	party.push_back(a);
	party.push_back(b);
	party.push_back(c);
	party.push_back(d);
	party.push_back(e);

	// Boss�� ���� �������� ���� ���ڸ� ã��
	Boss boss("���");
	boss.UpdateThreatQ(party);
	int value = boss.FindMostThreatCharacter(party);
	cout << "ù��° �Ͽ��� �������� ���� ū ��ġ : " << value << endl;

	cout << endl;

	boss.UpdateThreatQ(party);
	int value = boss.FindMostThreatCharacter(party);
	cout << "ù��° �Ͽ��� �������� ���� ū ��ġ : " << value << endl;

	for (auto& character: party)
	{
		character.PrintStat();
	}

	int nextTurnValue = 3;

	int CurrentThreat = 0;
	for (int i = 0; i < nextTurnValue; i++)
	{
		CurrentThreat += a.GetCurrentThreat();
		a.NextTurn();
	}

	cout << "������ 3��° �� �� ������" << CurrentThreat << endl;
	//a.PrintStat();
}




int main()
{

	return 0;
}