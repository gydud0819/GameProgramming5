/*
* 작성일	: 2025-06-24
* 주제	: 우선순위 큐를 이용하여 minHeap, maxHeap 구조 작성하기, rpg 보스레이드 턴제 수치 만들기 
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

/*
* maxHeap, minHeap
* 1번 우선순위 큐를 이용하여 힙 구조 작성하기
*/

bool myless(int a, int b)
{
	return a < b;
}

bool myGreater(int a, int b)
{
	return a > b;
}

// k번째로 작은 수 구하기, k번째로 큰 수 구하기를 우선순위 큐를 사용하면 쉽게 표현할 수 있다.
// logN 시간으로 k 번째 작은 수를 찾을 수 있다. -> (작은 수를 찾는다.

#pragma region MinHeap
class MinHeap
{
private:
	priority_queue<int, vector<int>, greater<int>> pq;			// 최솟값이 가장 위로 올라가는 형태
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

	const int& Top() const	// 참조로 하는 이유 : 얜 저장되어있는 가장 위의 값을 참조만 할거라서 &를 붙인다.
	{
		if (isEmpty())
		{
			throw runtime_error("priority Queue is Empty");
		}

		return pq.top();
	}

	int Pop()			// 복사를 한 뒤, 자료구조에서 삭제한다.
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

#pragma region k번째 숫자 찾기 함수
void FindKthExample()
{
	MinHeap minheap;

	minheap.Push(11);
	minheap.Push(7);
	minheap.Push(5);
	minheap.Push(3);

	cout << "최소 힙의 가장 작은 값 : " << minheap.Top() << endl;

	int k = 3;

	// for 반복문을 k로 표현하여 k번째 수 찾기

	//cout << "k번째 작은 수 출력하기 : " << endl;

	MaxHeap maxheap;
	maxheap.Push(11);
	maxheap.Push(7);
	maxheap.Push(5);
	maxheap.Push(3);

	cout << "최대 힙의 가장 큰 값 : " << maxheap.Top() << endl;
}
#pragma endregion

/*
* rpg 보스 레이드
* 5인팟
* 전사, 마법사, 궁수, 도적, 성직자
* 각 직업은 스킬을 사용할 때 마다 보스 어그로가 증가한다.
* 총 5번의 보스 공격마다 누구를 우선적으로 공격하는지 찾는 로직 작성하기
* 이떄 보스가 특정 직업을 공격할 때 마다 그 직업의 어그로는 0으로 초기화된다.
*
* 5번의 턴제		1		2		3		4		5
* 전사	:		10		5		8		7		6
* 도적	:
* 궁수	:
* 법사	:
* 성직자	:
*
* 보스의 스킬을 결정하는 로직
* 보스 : 파티안에서 누가 가장 위협적인가? 누가 가장 덜 위협적인가?
*
* 1. n개의 직업 마다 우선순위를 비교하고 가장 큰 순위를 출력한다.
* 2. heap 자료구조를 사용해서 k번째 순위를 찾는다.
*
* 갯수가 적으면 적을수록 1번 방식이 효율적이다.
* 2번을 사용해야하는
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
		if (threatLv.size() <= currentTurn) return -1;		// -1을 리턴하면 에러를 의미 
		return threatLv[currentTurn];		// 배열에 있는 값 반환하기 
	}

	void NextTurn()
	{
		currentTurn++;		// 다음 턴으로 넘어갈때마다 1씩 증가
	}

	void PrintStat()
	{
		cout << name << "(현재 위협도 : " << GetCurrentThreat() << ")" << endl;
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
	Character a("전사", { 1,2,3,4,5 });
	Character b("궁수", { 1,8,3,6,5 });
	Character c("법사", { 3,3,3,3,3 });
	Character d("도적", { 2,4,6,8,10 });
	Character e("성직자", { 1,3,5,7,9 });

	vector<Character> party;
	party.push_back(a);
	party.push_back(b);
	party.push_back(c);
	party.push_back(d);
	party.push_back(e);

	// Boss가 가장 위협도가 높은 숫자를 찾기
	Boss boss("고블린");
	boss.UpdateThreatQ(party);
	int value = boss.FindMostThreatCharacter(party);
	cout << "첫번째 턴에서 위협도가 가장 큰 수치 : " << value << endl;

	cout << endl;

	boss.UpdateThreatQ(party);
	int value = boss.FindMostThreatCharacter(party);
	cout << "첫번째 턴에서 위협도가 가장 큰 수치 : " << value << endl;

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

	cout << "전사의 3번째 턴 후 위협도" << CurrentThreat << endl;
	//a.PrintStat();
}




int main()
{

	return 0;
}