/*
* 작성일	: 2025-06-19, 20
* 주제	: 트리 구조 
*/
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/*
* 정리
* 
* vector : 선형 탐색, 이진 탐색 
* 조건 : 사용하는 컨테이너가 정렬이 되어있어야 한다.
* 사용중인 컨테이너의 특징 : 임의의 값을 바로 접근하거나 수정해야 할 경우에는 비효율적이다. 
* 
* list : 랜덤한 값의 수정을 즉시 할 수 있다. 
* mid index의 값과 target 비교
* 0-> mid 순차적으로 탐색후 mid 값을 반환한다. 
* 
* 단점 : log N 시간을 확보했지만, 사용하기 위한 자료구조가 적합하지 않다. 
* 연관 컨테이너 : set, map (트리구조로 구현되어 있다.)
* 
*/

/*
* 트리 자료 구조
* 노드 형태로 데이터를 저장한다. value, 연결되어 있는 Node 주소를 저장한다. 
*/

/*
* 트리 순회 방법
* 전위 중위 후위 순회 3가지가 있음
* 
* 전위 순회 - pre order	: NLR 순으로 읽는것
* 중위 순회 - in order	: LNR 
* 후위 순회 - post order	: LRN 순으로 읽음
*/

/*
* BST 바이너리 서치 트리 = 이진 탐색 트리
* - 자기 자신과, 왼쪽, 오른쪽을 저장하는 노드를 가지고 있음
* - Node를 기준으로 왼쪽과 오른쪽 값을 비교할 수 있ㄸ.
* - 작은값을 왼쪽 큰값을 오른쪽으로 저장하면 규칙성을 갖는다
* - 특정한 규칙을 갖는 클래스를 만들어서 데이터 출력하기
*/

/*
* BST 정리
* 순차 컨테이너 방식 - 탐색 및 수정이 효율적이지 않다는 단점이 존재
* 연관 컨테이너 방식 - "Tree 자료 구조"
* BST - 이진 검색 알고리즘으로 자료구조를 표현한 것
* 단점 : 노드가 한쪽으로 치우칠 경우 n만큼 시간이 걸림 
*/

/*
* tree 용어 정리
* 노드 : (값(value), 왼쪽 노드 주소, 오른쪽 노드 주소) 3가지를 가지는 데이터
* 부모 노드 : 자식 노드와 직접 연결된 노드
* 자식 노드 : 부모 노드와 직접 연결된 노드
* 조상 노드 : 특정 노드에서 루트까지의 경로에 있는 모든 노드들 (가지친거?) 
* 후손 노드 : 특정 노드의 모든 자식들을 포함하는 노드
* 루트 노드 : 트리에 있는 최상위 노드, 부모 노드가 없음
* 
* 알고리즘 트리 코드 구현시 사용되는 용어
* 레벨(level) : 루트로부터의 거리 / 루트는 0을 반환함
* 높이(high) : 트리에서 가장 깊은 레벨
* 깊이 : 특정 노드에서 루트까지의 길이 
* 서브 트리  : 트리 내부에 후손들로 구성된 또 다른 트리 
*/

struct Node
{
	int value;
	Node* leftNode;
	Node* rightNode;

public:
	Node(int val) : value(val), leftNode(nullptr), rightNode(nullptr) {}
};

#pragma region Tree 순회 방식
class Tree
{

public:
	void PreOrder(Node* root)	// 전위 순회 방식
	{
		if (root == nullptr) { return; }	// root가 더이상 아무것도 가리키지 않는다면
		cout << root->value << " ";
		PreOrder(root->leftNode);							// L에 있는 노드로 가서 PreOrder 실행
		PreOrder(root->rightNode);							// R에 있는 노드로 가서 PreOrder 실행
	}

	void InOrder(Node* root)	// 중위 순회 방식		LNR
	{
		if (root == nullptr) { return; }
		InOrder(root->leftNode);
		cout << root->value << " ";
		InOrder(root->rightNode);
	}

	void PostOrder(Node* root)	// 후위 순회 방식 LRN
	{
		if (root == nullptr) { return; }
		PostOrder(root->leftNode);
		PostOrder(root->rightNode);
		cout << root->value << " ";
	}
};
#pragma endregion

#pragma region Node 직접 연결 하기

void NodeConnect()
{
	Node* root = new Node(4);

	root->leftNode = new Node(2);
	root->leftNode->leftNode = new Node(9);
	root->leftNode->rightNode = new Node(7);

	root->rightNode = new Node(6);
	root->rightNode->leftNode = new Node(1);


	cout << "전위 순회 출력" << endl;
	Tree tree;
	tree.PreOrder(root);

	cout << endl;

	cout << "중위 순회 출력" << endl;
	Tree tree2;
	tree2.InOrder(root);
	cout << endl;


	cout << "후위 순회 출력" << endl;
	Tree tree3;
	tree3.PostOrder(root);
	
}
#pragma endregion

#pragma region 이진 탐색 트리 구현
/*
* root에서부터 데이터 삽입
* root보다 작으면 왼쪽, 크면 오른쪽으로 저장
* 모든 데이터를 저장후 중위 순회(LNR)로 읽으면 오름차순 데이터로 정렬됨 
*/

class BST
{
private:
	Node* root;		// 수정 못하게 private로 선언

	Node* insert(Node* node, int value)
	{
		// 데이터가 0개일 때 
		if (node == nullptr)
		{
			return new Node(value);
		}

		// node보다 작으면 왼쪽 크면 오른쪽

		if (node->value > value)
		{
			node->leftNode = insert(node->leftNode, value);		// 새로 들어가는 값이 작으면 왼쪽에 저장
		}
		else if (node->value < value)
		{
			node->rightNode = insert(node->rightNode, value);	// 새로 들어가는 값이 크면 오른쪽에 저장
		}
		return node;
	}

	Node* FindMin(Node* node)		// 오른쪽에서 가장 작은 값을 찾을 때
	{
		// 재귀함수로 표현
		if (node == nullptr || node->leftNode == nullptr)
		{
			return node;
		}

		return FindMin(node->leftNode);
	}

	Node* FindMax(Node* node)		// 왼쪽에서 가장 큰 값을 찾을 때
	{
		if (node == nullptr || node->rightNode == nullptr)
		{
			return node;
		}
		return FindMax(node->rightNode);
	}

	Node* deleteNode(Node* node, int target)	// 삭제 노드		// 데이터를 먼저 찾은 다음 있으면 지운다.
	{
		if (node == nullptr) { return nullptr; }	// 노드가 아무것도 가리키지 않으면 nullptr를 반환한다. 

		if (node->value > target)	// 노드에 있는 값이 타겟보다 크면 왼쪽으로 이동
		{
			node->leftNode = deleteNode(node->leftNode, target);
		}
		else if (node->value < target)	// 노드에 있는 값이 타겟보다 작으면 오른쪽으로 이동
		{
			node->rightNode = deleteNode(node->rightNode, target);
		}
		else		
		{
			// 지울 데이터를 찾았을 때 노드 삭제 하기
			if (node->leftNode == nullptr && node->rightNode == nullptr);		
			if (node->leftNode == nullptr);	// 오른쪽 노드가 없을 때
			if (node->rightNode == nullptr);	// 오른쪽 노드가 없을 때

			if (node->leftNode == nullptr || node->rightNode == nullptr)
			{
				Node* temp = node->leftNode != nullptr ? node->leftNode : node->rightNode;	// 왼쪽 노드가 nullptr이 아니면 왼쪽노드 값을, 맞으면 오른쪽 노드

				if (temp == nullptr)		// 자식 노드가 없을 때
				{
					temp = node;
					node = nullptr;
				}
				else
				{
					node = temp;
				}
			}
			else	// 자식이 2개인 경우 
			{
				// 오른쪽에서 가장 작은 값을 찾거나 왼쪽에서 가장 큰 값을 찾는다. 왼쪽에서 가장 큰 데이터 값이 올라가는거 아닌가? 
				Node* temp = FindMin(node->rightNode);	// 나는 왼쪽에서 찾을거임
				node->value = temp->value;
				node->rightNode = deleteNode(node->rightNode, temp->value);
			}
		}
		return node;
	}

	void inorder(Node* node)	// L->N->R
	{
		if (node == nullptr) { return; }		// node가 nullptr이면 반환
		inorder(node->leftNode);
		cout << node->value << " ";
		inorder(node->rightNode);

	}

public:
	BST()	// 생성자 만들때 초기화 해주기 (환경마다 다름)
	{
		root = nullptr;
	}

	void insert(int value)
	{
		root = insert(root, value);
	}

	void inorder()	// L->N->R
	{
		inorder(root);
		cout << endl;
	}

	void DeleteNode(int value)
	{
		root = deleteNode(root, value);
	}
	
};

#pragma endregion


int main()
{
	NodeConnect();
	cout << endl;

	cout << "이진 탐색 트리 실행" << endl;		

	BST bst;
	bst.insert(1);
	bst.insert(6);
	bst.insert(4);
	bst.insert(3);
	bst.insert(9);
	bst.insert(7);

	bst.inorder();

	cout << "데이터 1 삭제 후 결과" << endl;
	bst.DeleteNode(1);
	bst.inorder();


}