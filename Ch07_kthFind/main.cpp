/*
* �ۼ���	: 2025-06-20, 23
* ����	: �˰������� ���� �����ϰ� Ž���ϱ�
*/
#include <iostream>
#include <vector>
#include <utility>
#include <map>		// Ʈ���� ���� �� Ʈ���� �����Ǿ� ���� ���� Ʈ���� ����� // insert {people �ε���, ��} �ֱ�
#include <algorithm>

using namespace std;

/*
* �˰��� ��ǥ ����
* ���� �����ϰ� Ž���ϱ�
* ��� : �����͸� ���Ľ�Ų��.
* k��° ���� �� -> ���ʺ��� �ϳ��� ���
* k��° ū �� -> �����ʺ��� �ϳ��� ���
*/

/*
* ���� ȯ�� ���� ���� -> vector<int>
* ���� ���� �����ؾ��ϴ� ȯ�ڰ� 1��
* 
* Ʈ���� ���� ����� �����Ͽ� ���� ū���� ã�� ���� �����ϱ�
*/

void EmergencyExample()
{
	vector<int> people = { 14, 23, 2, 5, 31, 37 };

	vector<int> answer;
	map<int, int> sheets;

	for (int i = 0; i < people.size(); i++)
	{
		sheets.insert({ i, people[i] });
	}

	sort(people.begin(), people.end());
	
	// answer�� ����ִ� ���� ū ��
	//int key = sheets.find(answer[answer.size() - 2])->first;
	//answer[key] = 2;

	/*
	* Tree ��� ���� 
	* Tree ������ �������� ���� ���
	* Idea1 - Ʈ���� �����͸� �־��� �� ���� ������ �ֱ� -> ä�� ���� ���� ���� Ʈ������ �ϳ��� ��Ģ�� ������ �ϱ� == Heap
	* 
	* Heap : ���� Ʈ���� �θ� ��尡 ���� ū ������ �Ѵ�.  
	* -> ���� ���� �ִ� ��尡 ���� ū �� == maxHeap
	* -> ���� ���� �ִ� ��尡 ���� ���� �� == minHeap
	* heapify() - Ʈ���� �� ������ �������ϴ� �ڵ� �Լ�
	* heapsort() - �� ����
	*/

	for (int i = 0; i < people.size(); i++)		// 
	{
		auto it = sheets.find(people[people.size() - 1 -i])->first;
		int index
		answer[key] = i + 1;
	}

	//answer = people;
	// answer.push_back() �ε��� ���� +1�� �ǵ���
	cout << "[";
	for (int i = 0; i < answer.size(); i++)
	{
		cout << answer[i] << " ";
	}
	cout << "]" << endl;
}



int main()
{
	EmergencyExample();

	return 0;
}