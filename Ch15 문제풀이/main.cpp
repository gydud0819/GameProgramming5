#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


using namespace std;

/*
* 1. 어떤 아이디어를 어떤 방식으로 결정했는지
* 2. 자료구조를 어떤 것으로 사용했는지 이유를 생각하기
*/

#pragma region Q1 ATM 문제
// ATM 문제 (백준 11399번)
// ATM에 사람들이 줄 서 있음 n명의 사람이 모두 기다린 시간이 최소가 되려면 어떻게 해야할지 그 시간이 몇 초인지 값 출력하기
struct Client
{
	int waitID;
	int waitTimes;

};
void Slove1()
{
	int n = 5;
	int totalTime = 0;
	// 1. 벡터를 사용해 문제의 예제 추가하기
	vector<int> waitTimeTable = { 3, 1, 4, 3, 2 };	// 이게 돈 뽑는 시간이야 사람 순서야 
	vector<int> clients(waitTimeTable.size());

	// clients들이 기다린 시간 측정하기 
	// 주어진 데이터대로 줄을 서면..시간이 걸리겠지..
	// 값이 적은 순으로 데이터를 정렬 시킨다.
	// 정렬시키고 반복적으로 더해준다.


	sort(waitTimeTable.begin(), waitTimeTable.end());

	// 처음 사용하는 사람 
	clients[0] = waitTimeTable[0];

	for (int i = 1; i < waitTimeTable.size(); i++)
	{
		clients[i] = clients[i - 1] + waitTimeTable[i];

	}

	for (int& t : clients)
	{
		totalTime += t;
	}


	// 2. 문제 풀이 방식 선택하기
	cout << n << "명의 사람들이 모두 기다리는 시간이 최소가 되는 시간은 " << totalTime << "초" << endl;

}

#pragma endregion

#pragma region Q2
// 배낭에 물건 담기 문제 (백준 12865번)
// 물건을 n개 담을 수 있는 무게가 k만큼 주어진다. 무게를 최대한으로 담았을 때 최대의 가치를 저장할 때의 값을 출력하기

void Slove2()
{
	cout << "배낭문제 풀이" << endl;

	// 4개의 물건이 들어옴. 각각의 물건에는 무게와 가치가 표현됨
	// 이때 k의 무게만큼 배낭 안에 최대한으로 담을 때 가치가 가장 크도록 저장하는 방법 구현하기

	// 1. n = 4 (무게?), k = 7(가치?)		[6,13] [4,8] [3,6] [5, 12]
	// 가장 가치있는 물건들만 담기 위해 어떻게 해야하는지 

	// 페어 써도될거같긴한데 
	int n = 4;
	int k = 7;
	vector<pair<int, int>> items = { {6,13}, {4,8}, {3,6}, {5,12} };

	//sort(items.begin(), items.end());

	// 무게별 가치 평가 
	// 배낭이 1일 때 최대로 담을 수 있는 가치
	vector<int> dp(k + 1, 0);		// dp[0] ~ [7]까지 

	for (int i = 0; i < 4; i++)
	{
		int weight = items[i].first;	// 무게
		int value = items[i].second;	// 가치

		for (int w = k; w >= weight; w--)		// w가 6보다 클때까지 반복
		{
			dp[w] = max(dp[w], dp[w - weight] + value);
		}
	}

	// 무게가 0 일때 각 무게에서 최대로 담을 수 있도록 무게별 최고 가치 갱신하기
	//dp[0] = 0;
	//dp[1] = 0;
	//dp[2] = 0;
	//dp[3] = 6;
	//dp[4] = 8;		// 이전 무게의 가치 + 새로 담을 수 있는 가치 하나의 가치 비교 하기
	//dp[5] = 12;		
	//dp[6] = 13;		
	//dp[7] = 14;		// 1+6 = 13, 2+5 = 12, 3+4 = 14	

	cout << "가방의 무게가 7까지 담을 수 있을 때 최대 가치 : " << dp[7] << endl;
}
#pragma endregion

// 인벤토리 - 무게 시스템, user의 편의성을 위한 코드
// 1. 이름을 클래스로 만들기 -> 아이템 클래스, 무게라는 가치가 포함되도록 만들기
// 2. 아이템을 저장하는 컨테이너, 인벤토리. 무게가 존재하는 인벤토리 구현하기

class ItemW
{
private:
	string name;
	int weight;
	int value;
public:
	ItemW(string _name, int _weight, int _value) : name(_name), weight(_weight), value(_value) {}

	int GetWeight() const { return weight; }
	string GetName() const { return name; }
	int GetValue() const { return value; }
};

class InventoryW	// ItemW 자료형을 컨테이너로 저장하기
{
private:
	vector<ItemW> Items;
	int maxWeight;
	int currentWeight;
public:
	// 생성자 만들기
	InventoryW(int max) : maxWeight(max), currentWeight(0) {}

	// 아이템 추가하기
	void AddItem(const ItemW& addItem)
	{
		if (CheckWeight(addItem))
		{
			Items.push_back(addItem);
			currentWeight += addItem.GetWeight();
		}
	}

	// 최대 무게가 아이템의 무게보다 무거우면 true, false 반환
	bool CheckWeight(const ItemW& addItem)
	{
		return maxWeight >= currentWeight + addItem.GetWeight();
	}

	/*
	* 2025-07-03
	* Todo
	* 1. 선택한 아이템들 중에서 가장 큰 가치, 실제로 선택된 아이템들을 (자료구조)
	* 반환 값을 pair로 설정하기 pair<T1, T2>
	*/

	pair<int, vector<ItemW>> findBestItem(int targetWeight, vector<ItemW>& selectableItems)
	{
		// 현재 아이템의 무게에 새로운 아이템 조합을 가져올 때 그 아이템을 저장할 컨테이너 선언하기
		vector<int> dp(targetWeight + 1, 0);		// 가치를 1 더하고 0으로 초기화 하기 

		// selectableItems에 들어있는 무게
		// selectableItems에 들어있는 가치 표현하기

		vector<vector<bool>> selected(selectableItems.size(), vector<bool>(targetWeight + 1, false));	// 최대개수보다 1개 더 많은걸 거짓으로 초기화 

		for (int i = 0; i < selectableItems.size(); i++)
		{
			int weight = selectableItems[i].GetWeight();
			int value = selectableItems[i].GetValue();

			for (int w = targetWeight; w >= weight; w--)
			{
				if (dp[w - weight] + value > dp[w])
				{
					dp[w] = dp[w - weight] + value; 
					selected[i][w] = true;				// dp[w - weight] > dp[w] 이 조건이 참일때
				}

			}
		}
		// 계산한 최적의 조합을 역산해서 다시 vector에 저장하기
		// while(weight - 무게)

		vector<ItemW> bestItmes;
		int w = targetWeight;

		for (int i = selectableItems.size() -1; i >= 0 && w > 0; i--)
		{
			if(selected[i][w])		// 조건이 참일 때
			{
				bestItmes.push_back(selectableItems[i]);
				w -= selectableItems[i].GetWeight();		
			}
		}

		return make_pair(dp[targetWeight], bestItmes);
	}

	vector<ItemW>& GetInventory()
	{
		return Items;
	}
};

void InventoryWieghtSystem()
{
	// 인벤토리 객체? 생성하고 호출하기, 4개의 아이템을 배낭에 저장하기 (최대무게가 7이고 아이템 4개 생성하기)
	InventoryW inventory(7);

	ItemW A("A", 6, 13);
	ItemW B("B", 4, 8);
	ItemW C("C", 3, 6);
	ItemW D("D", 5, 12);

	vector<ItemW> selectable{ A,B,C,D };
	//cout << "주어진 아이템의 최대 가치 : " << inventory.findBestItem(7, selectable);
	pair<int,vector<ItemW>> bestItems = inventory.findBestItem(7, selectable);

	cout << "주어진 아이템의 최대 가치 : " << bestItems.first << endl;
	vector<ItemW> ItemC = bestItems.second;

	int i = 0;
	for (auto& item : ItemC)		// 자동 추론 
	{
		i++;
		cout << i << "번째 아이템의 이름 : " << item.GetName() << ", 무게 " << item.GetWeight() << ", 가치 " << item.GetValue() << endl;
		// 유저가 허락했을 때 실행하도록 (유저 입력 코드)
		inventory.AddItem(item);
	}

	inventory.AddItem(A);
	inventory.AddItem(B);
	inventory.AddItem(C);
	inventory.AddItem(D);

	int index = 0;

	for (auto& item : inventory.GetInventory())
	{
		index++;
		cout << index << "번째 " << item.GetName() << ", 무게 " << item.GetWeight() << ", 가치 " << item.GetValue() << endl;
	}
}

int main()
{
	Slove1();

	cout << endl;
	Slove2();
	cout << endl;

	InventoryWieghtSystem();
}