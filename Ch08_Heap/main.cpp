/*
* �ۼ���	: 2025-06-23, 24
* ����	: Heap
*/

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

void PriorityQueue()		// �켱���� ť
{
	priority_queue<int> pq;

	// heap �ڷᱸ���� ������� Ŭ�����̴�.
}

/*
* ��ǥ
* 0. k��° ���� ã�� ���� ���� ��, delete temp �����ϱ�
* 1. Heap�� Ư���ѱ�Ģ�� ������ �ִ� �ڷᱸ�� ���� �����ϱ�
* 2. k��° �����ϴ� ���� ���� ������ Ǯ���
*/

// 
/*
* k��° ���� ã��
*
* 1. vector, array ���ڸ� ���Ľ�Ų �Ŀ� ���� ũ�ų�(����) ���� ã�´�. (���� �˰��� �ð� ����ϱ�)
* 2. ��ü ������ n���� �Ǹ� n-1 �� �񱳸� �ؾ��Ѵ�. (��� ����� ���� Ž��, ���� Ž���� �Ѵ�)
* 3. �ð��� log n�� �ɸ��� ��� ã�� == ���ڸ� ã�� ��찡 100���� �̻� (ó���ؾ� �� �����Ͱ� ������) �϶� ��� �ؾ��ϴ���
*
* �ݴ�� ó���ؾ� �� �����Ͱ� ���ٸ� (10 ~ 1)
*/

/*
* tree (���������� �����Ͱ� ����� ��� ȿ�������� ����) == �������� ���� ġ��ĥ ��
* 1. ������ �ذ��ϱ� ���� �ϳ��� ������� Ʈ�� ���·� ���� ������ �ӽ÷� �����͸� �ִ´�. (Ʈ���� ���ʴ�� �����Ѵ�) == ���� ���� �z��
* 2. root �������� ���� ū�� �Ǵ� ���� ���� �����ϵ��� ��Ģ�� �����Ѵ�. (�̷��� ��Ģ�� ���� �ڷᱸ���� Heap�̶�� �Ѵ�, minHeap, maxHeap)
* 3.
*/

// MaxHeap �����Ѱ� ���� MinHeap�� ���� �����غ��� 

#pragma region MaxHeap
class MaxHeap	// 
{
private:
	struct Node
	{
		int value;
		Node* leftnode;
		Node* rightnode;
		Node* parrentNode;		// �ڱ� �ڽ� ��� �ٷ� ���� �ִ� �θ� ��� 

		Node(int value) : value(value), leftnode(nullptr), rightnode(nullptr), parrentNode(nullptr) {}
	};

	Node* root;
	int size;	// ��Ʈ�� �����ϱ��� ����

	/*
	* heap�� Ư¡ : �����Ͱ� ���� �� heap�� ������ �����ϰ� �ִٰ� ������ ��
	* ���� ���� �����͸� ��Ģ�� �µ��� �����ϸ� ��
	*/

	void heapifyUp(Node* node)		// ���� �߰��� ��尡 ����Ǿ��ְ� ����� �θ� ��带 �����ͷ� ����Ű�� ����. node->parrentNode->value node->value
	{
		// 1. �߰��� ���� �θ� ����� ���� ���ϴ� �ڵ� ����� (���� �߰��� ��尡 �� Ŭ��)
		// 2. ���� �߰��� ����� �θ� ��尡 �����ϸ� ��� �����ϱ�	-> if�� �Ƚᵵ�ǳ�? while�� �̹� �Ѱǰ� �׷� �Ȱǰ�? 

		while (node->parrentNode != nullptr && node->value > node->parrentNode->value)		// �����ϱ� ���� ����
		{

			// �˰��� ����� �߰��Ͽ� �θ� ���� �ڱ� ��� swap �ϱ� (value�� swap)
			// swap�� �� ��带 �θ� ���� �������ش�. (�ּҸ� swap)
			swap(node->value, node->parrentNode->value);
			node = node->parrentNode;
		}
	}

	Node* findLastNode()	// ��带 ������ �� ��Ģ 1�� ������Ű�� ���� ���� ������ ��带 ã�´�. 
	{
		if (!root) return nullptr;	// ��Ʈ�� �����Ͱ� ������ nullptr�� ��ȯ�Ѵ�. 

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
		// root�� �ø� ������ ��带 �ڽ� ��� �߿��� ū ���� ���Ѵ� (���ʰ� ������ �� �ϳ�)
		// �ڽ��� ����, ������ ��庸�� ũ�ų� �ڽ��� ���� �� ���� �ݺ��ϱ�
		while (node)
		{
			Node* largest = node;	// ���� ��尡 ���� ũ�ٰ� �����ϱ�
			if (node->leftnode && node->leftnode->value > largest->value)
			{
				largest = node->leftnode;
			}
			if (node->rightnode && node->rightnode->value > largest->value)
			{
				largest = node->rightnode;
			}

			// ���ʰ� �������߿��� ū ���� �ٲ��. 
			if (largest == node)		// Ȥ�ö� ������ ���� �ʾҴٸ� 
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

		if (!root)				// �����Ͱ� 0���� ��� ���� ���� �����Ͱ� ��Ʈ�� ��
		{
			root = newNode;
			size = 1;
			return;
		}

		// ��Ʈ�� ������ ��� ��Ģ1�� ���� ������� ��尡 ����� �� �ְ� ���� �ۼ��ϱ�
		// ���ʿ� �����Ͱ� ������ -> ���� �����Ϳ� �ֱ�
		// �����ʿ� �����Ͱ� ������ -> ������ �����Ϳ� �ֱ�

		queue<Node*> q;		// queue�� ���Լ��� ����
		q.push(root);		// ��Ʈ �ֱ� 

		while (!q.empty())	// �����Ͱ� �ƹ��͵� ���������� while�� ��� ������. q �����Ͱ��������� ������ 
		{
			Node* currentNode = nullptr;
			q.pop();
			if (!currentNode->leftnode)		// ���� ��忡 �����Ͱ� ������ ���� ��忡 �ֱ�						// 171��°���� ���� �߻�
			{
				currentNode->leftnode = newNode;		// ���� ����� ���� �ڽĿ� ���ο� ������ �ִ´�. 
				newNode->parrentNode = currentNode;		// �ڽ��� �θ� �����Ѵ�.
				break;
			}

			if (!currentNode->rightnode)	// ���ʰ� ���������� ������ ��忡 �����Ͱ� ���� �� ������ ��忡 ������ �ֱ�
			{
				currentNode->rightnode = newNode;
				newNode->parrentNode = currentNode;
				break;
			}

			// root�� ���̻� ����� ��尡 ���� �� ���� �ݺ��ϱ� ���� ����� ������ �߰����ִ� ��� 
			q.push(currentNode->leftnode);	// currentNode�� ���� �տ� �ִ� ������
			q.push(currentNode->rightnode);	// currentNode�� ���� �տ� �ִ� ������
		}
		size++;
		heapifyUp(newNode);

		//heapifyDown();
		// ���� �� ���� �θ��� ��� ���ؼ� ū ���� �������� ������
		// heapifyup


	}

	int exractMax()		// �ִ밪�� �����϶�� �Լ�
	{
		if (!root) return -1;		// -1�� �����ϸ� ������ �ִٴ� �� �˸���.

		int maxValue = root->value;

		if (size == 1)
		{
			delete root;	// root�� �����ϰ�
			root = nullptr;	// ������ ��Ʈ�� nullptr�� �����Ѿ� �ϰ�
			size = 0;		// size�� 0���� �ǰ�
			return maxValue;	// ���� ��ȯ
		}

		// 1. ������ ��� ã��
		Node* lastNode = findLastNode();
		if (!lastNode) return -2;	// �ڵ� �̽� �Ǵ��� ���� �ۼ��Ѵ�. 

		// 2. ������ ��带 root ���� �̵���Ų �ڿ� �ٽ� heap ������ ������ �����ϱ�
		root->value = lastNode->value;		// ���� �����ִ� ��忡 ������ ��带 �ø���. ���� root���� ������ ���� ����ִ�. ������ ����� ���� �ƴϰ���? 

		// ����� ���ؼ� ����Ű�� �ִ� ���� ������ ���
		if (lastNode->parrentNode)
		{
			// �θ� ��忡�� ���ʰ� ������ �� ū���� �θ� ��� ���� �ø��� ���� ��
			// lastNode�� ���� root�� �ö󰬰� ���� lastNode�� �ִ� �ּҸ� nullptr�� �ٲٱ� 
			if (lastNode->parrentNode->leftnode == lastNode)
			{
				lastNode->parrentNode->leftnode = nullptr;
			}
			else // ������ ��尡 �θ� ����� �����ʿ� ���� ��
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
		// heap ���� ������ �ڷᱸ���� vector�� ��ȯ�ϱ�
		// while queue �ڷ����� ����ؼ� �����͸� Ž���ϴ� ������ �ڵ� �ۼ��ϱ�

		if (root = nullptr) return result;
		
		queue<Node*> q;
		q.push(root);

		while (!q.empty())	// q�� �����Ͱ� ����ִ� �� Ȯ���Ҷ����� ��� ������
		{
			Node* node = q.front();		// ������ �ӽ�����
			q.pop();
			result.push_back(node->value);		// node�� �����ͷ� ǥ���ϴ� ���� : 

			if (node->leftnode)			// ���ʿ� ���� ��� ��
			{
				q.push(node->leftnode);
			}	
			if (node->rightnode)		// �����ʿ� ���� ��� ��
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
		Node* parrentNode;		// �ڱ� �ڽ� ��� �ٷ� ���� �ִ� �θ� ��� 

		Node(int value) : value(value), leftnode(nullptr), rightnode(nullptr), parrentNode(nullptr) {}
	};

	Node* root;
	int size;	// ��Ʈ�� �����ϱ��� ����
};
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

int main()
{
	MaxHeap mheap;
	cout << "���� ū ���� ã�� Heap ������ �Է�" << endl;
	mheap.Insert(7);
	mheap.Insert(3);
	mheap.Insert(5);
	mheap.Insert(11);

	cout << "Heap �ڷᱸ���� Ʈ������ ������� ����ϴ� ����" << endl;
	vector<int> temp = mheap.toArray();
	for (auto& data : temp)
	{
		cout << data << " " <<  endl;
	}

	cout << endl;

	cout << "���� ū ���� ��ȯ�ϰ� �ٽ� Heap ������ �ϴ� ����" << endl;
	int maxValue = mheap.exractMax();		// 1��°�� ū ��
	int k = 2;	// 2��°�� ū�� 
	int kitValue;
	for (int i = 0; i < 2; i++)
	{
		kitValue = mheap.exractMax();		// 2��°�� ū ���� kitValue ����ȴ�.
	}

	// k������ ū �� ã�� 


	return 0;
}