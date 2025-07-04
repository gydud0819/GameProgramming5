#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

/*
* 1. � ���̵� � ������� �����ߴ���
* 2. �ڷᱸ���� � ������ ����ߴ��� ������ �����ϱ�
*/

#pragma region Q1 ATM ����
// ATM ���� (���� 11399��)
// ATM�� ������� �� �� ���� n���� ����� ��� ��ٸ� �ð��� �ּҰ� �Ƿ��� ��� �ؾ����� �� �ð��� �� ������ �� ����ϱ�
struct Client
{
	int waitID;
	int waitTimes;

};
void Slove1()
{
	int n = 5;
	int totalTime = 0;
	// 1. ���͸� ����� ������ ���� �߰��ϱ�
	vector<int> waitTimeTable = { 3, 1, 4, 3, 2 };	// �̰� �� �̴� �ð��̾� ��� ������ 
	vector<int> clients(waitTimeTable.size());

	// clients���� ��ٸ� �ð� �����ϱ� 
	// �־��� �����ʹ�� ���� ����..�ð��� �ɸ�����..
	// ���� ���� ������ �����͸� ���� ��Ų��.
	// ���Ľ�Ű�� �ݺ������� �����ش�.


	sort(waitTimeTable.begin(), waitTimeTable.end());

	// ó�� ����ϴ� ��� 
	clients[0] = waitTimeTable[0];

	for (int i = 1; i < waitTimeTable.size(); i++)
	{
		clients[i] = clients[i - 1] + waitTimeTable[i];

	}

	for (int& t : clients)
	{
		totalTime += t;
	}


	// 2. ���� Ǯ�� ��� �����ϱ�
	cout << n << "���� ������� ��� ��ٸ��� �ð��� �ּҰ� �Ǵ� �ð��� " << totalTime << "��" << endl;

}

#pragma endregion

#pragma region Q2
// �賶�� ���� ��� ���� (���� 12865��)
// ������ n�� ���� �� �ִ� ���԰� k��ŭ �־�����. ���Ը� �ִ������� ����� �� �ִ��� ��ġ�� ������ ���� ���� ����ϱ�

void Slove2()
{
	cout << "�賶���� Ǯ��" << endl;

	// 4���� ������ ����. ������ ���ǿ��� ���Կ� ��ġ�� ǥ����
	// �̶� k�� ���Ը�ŭ �賶 �ȿ� �ִ������� ���� �� ��ġ�� ���� ũ���� �����ϴ� ��� �����ϱ�

	// 1. n = 4 (����?), k = 7(��ġ?)		[6,13] [4,8] [3,6] [5, 12]
	// ���� ��ġ�ִ� ���ǵ鸸 ��� ���� ��� �ؾ��ϴ��� 

	// ��� �ᵵ�ɰŰ����ѵ� 
	int n = 4;
	int k = 7;
	vector<pair<int, int>> items = { {6,13}, {4,8}, {3,6}, {5,12} };

	//sort(items.begin(), items.end());

	// ���Ժ� ��ġ �� 
	// �賶�� 1�� �� �ִ�� ���� �� �ִ� ��ġ
	vector<int> dp(k + 1, 0);		// dp[0] ~ [7]���� 

	for (int i = 0; i < 4; i++)
	{
		int weight = items[i].first;	// ����
		int value = items[i].second;	// ��ġ

		for (int w = k; w >= weight; w--)		// w�� 6���� Ŭ������ �ݺ�
		{
			dp[w] = max(dp[w], dp[w - weight] + value);
		}
	}

	// ���԰� 0 �϶� �� ���Կ��� �ִ�� ���� �� �ֵ��� ���Ժ� �ְ� ��ġ �����ϱ�
	//dp[0] = 0;
	//dp[1] = 0;
	//dp[2] = 0;
	//dp[3] = 6;
	//dp[4] = 8;		// ���� ������ ��ġ + ���� ���� �� �ִ� ��ġ �ϳ��� ��ġ �� �ϱ�
	//dp[5] = 12;		
	//dp[6] = 13;		
	//dp[7] = 14;		// 1+6 = 13, 2+5 = 12, 3+4 = 14	

	cout << "������ ���԰� 7���� ���� �� ���� �� �ִ� ��ġ : " << dp[7] << endl;
}
#pragma endregion

// �κ��丮 - ���� �ý���, user�� ���Ǽ��� ���� �ڵ�
// 1. �̸��� Ŭ������ ����� -> ������ Ŭ����, ���Զ�� ��ġ�� ���Եǵ��� �����
// 2. �������� �����ϴ� �����̳�, �κ��丮. ���԰� �����ϴ� �κ��丮 �����ϱ�

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

class InventoryW	// ItemW �ڷ����� �����̳ʷ� �����ϱ�
{
private:
	vector<ItemW> Items;
	int maxWeight;
	int currentWeight;
public:
	// ������ �����
	InventoryW(int max) : maxWeight(max), currentWeight(0) {}

	// ������ �߰��ϱ�
	void AddItem(const ItemW& addItem)
	{
		if (CheckWeight(addItem))
		{
			Items.push_back(addItem);
			currentWeight += addItem.GetWeight();
		}
	}

	// �ִ� ���԰� �������� ���Ժ��� ���ſ�� true, false ��ȯ
	bool CheckWeight(const ItemW& addItem)
	{
		return maxWeight >= currentWeight + addItem.GetWeight();
	}

	/*
	* 2025-07-03
	* Todo
	* 1. ������ �����۵� �߿��� ���� ū ��ġ, ������ ���õ� �����۵��� (�ڷᱸ��)
	* ��ȯ ���� pair�� �����ϱ� pair<T1, T2>
	*/

	pair<int, vector<ItemW>> findBestItem(int targetWeight, vector<ItemW>& selectableItems)
	{
		// ���� �������� ���Կ� ���ο� ������ ������ ������ �� �� �������� ������ �����̳� �����ϱ�
		vector<int> dp(targetWeight + 1, 0);		// ��ġ�� 1 ���ϰ� 0���� �ʱ�ȭ �ϱ� 

		// selectableItems�� ����ִ� ����
		// selectableItems�� ����ִ� ��ġ ǥ���ϱ�

		vector<vector<bool>> selected(selectableItems.size(), vector<bool>(targetWeight + 1, false));	// �ִ밳������ 1�� �� ������ �������� �ʱ�ȭ 

		for (int i = 0; i < selectableItems.size(); i++)
		{
			int weight = selectableItems[i].GetWeight();
			int value = selectableItems[i].GetValue();

			for (int w = targetWeight; w >= weight; w--)
			{
				if (dp[w - weight] + value > dp[w])
				{
					dp[w] = dp[w - weight] + value;
					selected[i][w] = true;				// dp[w - weight] > dp[w] �� ������ ���϶�
				}

			}
		}
		// ����� ������ ������ �����ؼ� �ٽ� vector�� �����ϱ�
		// while(weight - ����)

		vector<ItemW> bestItmes;
		int w = targetWeight;

		for (int i = selectableItems.size() - 1; i >= 0 && w > 0; i--)
		{
			if (selected[i][w])		// ������ ���� ��
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
	// �κ��丮 ��ü? �����ϰ� ȣ���ϱ�, 4���� �������� �賶�� �����ϱ� (�ִ빫�԰� 7�̰� ������ 4�� �����ϱ�)
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

	int i = 0;
	for (auto& item : ItemC)		// �ڵ� �߷� 
	{
		i++;
		cout << i << "��° �������� �̸� : " << item.GetName() << ", ���� " << item.GetWeight() << ", ��ġ " << item.GetValue() << endl;
		// ������ ������� �� �����ϵ��� (���� �Է� �ڵ�)
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
		cout << index << "��° " << item.GetName() << ", ���� " << item.GetWeight() << ", ��ġ " << item.GetValue() << endl;
	}
}
