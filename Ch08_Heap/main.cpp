/*
* 작성일	: 2025-06-23, 24
* 주제	: Heap
*/

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void PriorityQueue()		// 우선순위 큐
{
	priority_queue<int> pq;

	// heap 자료구조로 만들어진 클래스이다.
}

/*
* 목표
* 0. k번째 문제 찾기 오류 수정 및, delete temp 삭제하기
* 1. Heap의 특정한규칙을 가지고 있는 자료구조 직접 구현하기
* 2. k번째 존재하는 수를 게임 예제로 풀어보기
*/

// 
/*
* k번째 숫자 찾기
*
* 1. vector, array 숫자를 정렬시킨 후에 가장 크거나(작은) 수를 찾는다. (정렬 알고리즘 시간 사용하기)
* 2. 전체 개수가 n개가 되면 n-1 번 비교를 해야한다. (모든 경우의 수를 탐색, 완전 탐색을 한다)
* 3. 시간이 log n이 걸리는 방법 찾기 == 숫자를 찾는 경우가 100만개 이상 (처리해야 할 데이터가 많으면) 일때 어떻게 해야하는지
*
* 반대로 처리해야 할 데이터가 적다면 (10 ~ 1)
*/

/*
* tree (편향적으로 데이터가 저장될 경우 효율적이지 못함) == 한쪽으로 많이 치우칠 때
* 1. 단점을 해결하기 위한 하나의 방법으로 트리 형태로 균형 잡히게 임시로 데이터를 넣는다. (트리를 차례대로 저장한다) == 완전 이진 틑리
* 2. root 방향으로 가장 큰수 또는 작은 수를 저장하도록 규칙을 설정한다. (이러한 규칙을 갖는 자료구조를 Heap이라고 한다, minHeap, maxHeap)
* 3.
*/

// MaxHeap 구현한걸 토대로 MinHeap을 따로 구현해보기 

#pragma region MaxHeap
class MaxHeap	// 
{
private:
	struct Node
	{
		int value;
		Node* leftnode;
		Node* rightnode;
		Node* parrentNode;		// 자기 자신 노드 바로 위에 있는 부모 노드 

		Node(int value) : value(value), leftnode(nullptr), rightnode(nullptr), parrentNode(nullptr) {}
	};

	Node* root;
	int size;	// 루트를 저장하기한 변수

	/*
	* heap의 특징 : 데이터가 들어올 떄 heap의 성질을 만족하고 있다고 가정할 때
	* 새로 들어온 데이터만 규칙에 맞도록 수정하면 됨
	*/

	void heapifyUp(Node* node)		// 새로 추가된 노드가 저장되어있고 노드의 부모 노드를 포인터로 가리키고 있음. node->parrentNode->value node->value
	{
		// 1. 추가된 노드와 부모 노드의 값을 비교하는 코드 만들기 (새로 추가된 노드가 더 클때)
		// 2. 새로 추가된 노드의 부모 노드가 존재하면 계속 실행하기	-> if문 안써도되나? while로 이미 한건가 그럼 된건가? 

		while (node->parrentNode != nullptr && node->value > node->parrentNode->value)		// 변경하기 위한 조건
		{

			// 알고리즘 헤더를 추가하여 부모 노드와 자기 노드 swap 하기 (value를 swap)
			// swap한 뒤 노드를 부모 노드와 변경해준다. (주소를 swap)
			swap(node->value, node->parrentNode->value);
			node = node->parrentNode;
		}
	}

	Node* findLastNode()	// 노드를 삭제할 때 규칙 1을 만족시키기 위한 가장 마지막 노드를 찾는다. 
	{
		if (!root) return nullptr;	// 루트에 데이터가 없으면 nullptr을 반환한다. 

		queue<Node*> q;
		q.push(root);

		Node* lastNode = nullptr;
		while (!q.empty())
		{
			lastNode = q.front();
			q.pop();

			if (lastNode->leftnode)
			{
				q.push(lastNode->leftnode);

			}
			if (lastNode->rightnode)
			{
				q.push(lastNode->rightnode);
			}

		}
		return lastNode;
	}

	void heapifyDown(Node* node)
	{
		// root에 올린 마지막 노드를 자식 노드 중에서 큰 값과 비교한다 (왼쪽과 오른쪽 중 하나)
		// 자식의 왼쪽, 오른쪽 노드보다 크거나 자식이 없을 때 까지 반복하기
		while (node)
		{
			Node* largest = node;	// 현재 노드가 가장 크다고 가정하기
			if (node->leftnode && node->leftnode->value > largest->value)
			{
				largest = node->leftnode;
			}
			if (node->rightnode && node->rightnode->value > largest->value)
			{
				largest = node->rightnode;
			}

			// 왼쪽과 오른쪽중에서 큰 수로 바뀐다. 
			if (largest == node)		// 혹시라도 변경이 되지 않았다면 
			{
				break;
			}

			swap(node->value, largest->value);
			node = largest;
		}
	}

	void DeleteNode(Node* node)
	{
		if (!node) return;

		DeleteNode(node->leftnode);
		DeleteNode(node->rightnode);

		delete node;
	}

public:
	MaxHeap() : root(nullptr), size(0) {}
	void Insert(int value)
	{
		Node* newNode = new Node(value);

		if (!root)				// 데이터가 0개일 경우 새로 들어온 데이터가 루트가 됨
		{
			root = newNode;
			size = 1;
			return;
		}

		// 루트가 존재할 경우 규칙1을 따라서 순서대로 노드가 저장될 수 있게 조건 작성하기
		// 왼쪽에 데이터가 없으면 -> 왼쪽 데이터에 넣기
		// 오른쪽에 데이터가 없으면 -> 오른쪽 데이터에 넣기

		queue<Node*> q;		// queue는 선입선출 구조
		q.push(root);		// 루트 넣기 

		while (!q.empty())	// 데이터가 아무것도 없을때까지 while로 계속 돌린다. q 데이터가있을때만 돌린다 
		{
			Node* currentNode = nullptr;
			q.pop();
			if (!currentNode->leftnode)		// 현재 노드에 데이터가 없으면 왼쪽 노드에 넣기						// 171번째에서 예외 발생
			{
				currentNode->leftnode = newNode;		// 현재 노드의 왼쪽 자식에 새로운 데이터 넣는다. 
				newNode->parrentNode = currentNode;		// 자식의 부모를 설정한다.
				break;
			}

			if (!currentNode->rightnode)	// 왼쪽과 마찬가지로 오른쪽 노드에 데이터가 없을 때 오른쪽 노드에 데이터 넣기
			{
				currentNode->rightnode = newNode;
				newNode->parrentNode = currentNode;
				break;
			}

			// root에 더이상 연결된 노드가 없을 때 까지 반복하기 위해 연결된 노드들을 추가해주는 노드 
			q.push(currentNode->leftnode);	// currentNode가 가장 앞에 있는 데이터
			q.push(currentNode->rightnode);	// currentNode가 가장 앞에 있는 데이터
		}
		size++;
		heapifyUp(newNode);

		//heapifyDown();
		// 현재 들어간 노드와 부모의 노드 비교해서 큰 수를 위쪽으로 보내기
		// heapifyup


	}

	int exractMax()		// 최대값을 제거하라는 함수
	{
		if (!root) return -1;		// -1을 리턴하면 에러가 있다는 걸 알린다.

		int maxValue = root->value;

		if (size == 1)
		{
			delete root;	// root를 삭제하고
			root = nullptr;	// 삭제된 루트는 nullptr을 가리켜야 하고
			size = 0;		// size는 0으로 되고
			return maxValue;	// 값을 반환
		}

		// 1. 마지막 노드 찾기
		Node* lastNode = findLastNode();
		if (!lastNode) return -2;	// 코드 미스 판단을 위해 작성한다. 

		// 2. 마지막 노드를 root 노드로 이동시킨 뒤에 다시 heap 성질을 갖도록 정렬하기
		root->value = lastNode->value;		// 가장 위에있는 노드에 마지막 노드를 올린다. 현재 root에는 마지막 값이 들어있다. 마지막 노드의 값은 아니겠지? 

		// 지우기 위해서 가리키고 있는 가장 마지막 노드
		if (lastNode->parrentNode)
		{
			// 부모 노드에서 왼쪽과 오른쪽 중 큰수를 부모 노드 위로 올리고 싶을 때
			// lastNode의 값은 root로 올라갔고 현재 lastNode에 있는 주소를 nullptr로 바꾸기 
			if (lastNode->parrentNode->leftnode == lastNode)
			{
				lastNode->parrentNode->leftnode = nullptr;
			}
			else // 마지막 노드가 부모 노드의 오른쪽에 있을 때
			{
				lastNode->parrentNode->rightnode = nullptr;
			}
			delete lastNode;
			size--;
			heapifyDown(root);

			return maxValue;
		}
	}
	vector<int> toArray()
	{
		vector<int> result;
		// heap 으로 저장한 자료구조를 vector로 변환하기
		// while queue 자료형을 사용해서 데이터를 탐색하는 형태의 코드 작성하기

		if (root = nullptr) return result;
		
		queue<Node*> q;
		q.push(root);

		while (!q.empty())	// q에 데이터가 비어있는 걸 확인할때까지 계속 돌리기
		{
			Node* node = q.front();		// 데이터 임시저장
			q.pop();
			result.push_back(node->value);		// node를 포인터로 표현하는 이유 : 

			if (node->leftnode)			// 왼쪽에 넣을 노드 값
			{
				q.push(node->leftnode);
			}	
			if (node->rightnode)		// 오른쪽에 넣을 노드 값
			{
				q.push(node->rightnode);
			}
			
		}

		return result;
	}
};
#pragma endregion




#pragma region MinHeap
class MinHeap	// 
{
private:
	struct Node
	{
		int value;
		Node* leftnode;
		Node* rightnode;
		Node* parrentNode;		// 자기 자신 노드 바로 위에 있는 부모 노드 

		Node(int value) : value(value), leftnode(nullptr), rightnode(nullptr), parrentNode(nullptr) {}
	};

	Node* root;
	int size;	// 루트를 저장하기한 변수
};
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

int main()
{
	MaxHeap mheap;
	cout << "가장 큰 수를 찾는 Heap 데이터 입력" << endl;
	mheap.Insert(7);
	mheap.Insert(3);
	mheap.Insert(5);
	mheap.Insert(11);

	cout << "Heap 자료구조의 트리저장 순서대로 출력하는 예제" << endl;
	vector<int> temp = mheap.toArray();
	for (auto& data : temp)
	{
		cout << data << " " <<  endl;
	}

	cout << endl;

	cout << "가장 큰 수를 반환하고 다시 Heap 정렬을 하는 예제" << endl;
	int maxValue = mheap.exractMax();		// 1번째로 큰 수
	int k = 2;	// 2번째로 큰수 
	int kitValue;
	for (int i = 0; i < 2; i++)
	{
		kitValue = mheap.exractMax();		// 2번째로 큰 수가 kitValue 저장된다.
	}

	// k번쨰로 큰 수 찾기 


	return 0;
}