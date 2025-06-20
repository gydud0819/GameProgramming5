/*
* 작성일	: 2025-06-20, 23
* 주제	: 알고리즘으로 수를 정렬하고 탐색하기
*/
#include <iostream>
#include <vector>
#include <utility>
#include <map>		// 트리의 레드 블랙 트리로 구현되어 있음 이진 트리와 비슷함 // insert {people 인덱스, 값} 넣기
#include <algorithm>

using namespace std;

/*
* 알고리즘 대표 문제
* 수를 정렬하고 탐색하기
* 방법 : 데이터를 정렬시킨다.
* k번째 작은 수 -> 왼쪽부터 하나씩 출력
* k번째 큰 수 -> 오른쪽부터 하나씩 출력
*/

/*
* 응급 환자 순서 제공 -> vector<int>
* 가장 먼저 진료해야하는 환자가 1번
* 
* 트리의 저장 방식을 응용하여 가장 큰수를 찾는 형태 구현하기
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
	
	// answer에 들어있는 가장 큰 수
	//int key = sheets.find(answer[answer.size() - 2])->first;
	//answer[key] = 2;

	/*
	* Tree 노드 삭제 
	* Tree 균형이 잡혀있지 않은 경우
	* Idea1 - 트리에 데이터를 넣었을 때 균형 잡히게 넣기 -> 채워 넣은 다음 서브 트리들이 하나의 규칙을 갖도록 하기 == Heap
	* 
	* Heap : 서브 트리의 부모 노드가 가장 큰 수여야 한다.  
	* -> 가장 위에 있는 노드가 제일 큰 수 == maxHeap
	* -> 가장 위에 있는 노드가 제일 작은 수 == minHeap
	* heapify() - 트리를 힙 순서로 재정렬하는 코드 함수
	* heapsort() - 힙 정렬
	*/

	for (int i = 0; i < people.size(); i++)
	{
		int key = sheets.find(people[people.size() - 1 -i])->first;
		answer[key] = i + 1;
	}

	//answer = people;
	// answer.push_back() 인덱스 값에 +1이 되도록
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