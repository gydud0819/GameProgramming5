/*
* ����	: Ʈ�� ���� 
*/
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/*
* ����
* 
* vector : ���� Ž��, ���� Ž�� 
* ���� : ����ϴ� �����̳ʰ� ������ �Ǿ��־�� �Ѵ�.
* ������� �����̳��� Ư¡ : ������ ���� �ٷ� �����ϰų� �����ؾ� �� ��쿡�� ��ȿ�����̴�. 
* 
* list : ������ ���� ������ ��� �� �� �ִ�. 
* mid index�� ���� target ��
* 0-> mid ���������� Ž���� mid ���� ��ȯ�Ѵ�. 
* 
* ���� : log N �ð��� Ȯ��������, ����ϱ� ���� �ڷᱸ���� �������� �ʴ�. 
* ���� �����̳� : set, map (Ʈ�������� �����Ǿ� �ִ�.)
* 
*/

/*
* Ʈ�� �ڷ� ����
* ��� ���·� �����͸� �����Ѵ�. value, ����Ǿ� �ִ� Node �ּҸ� �����Ѵ�. 
*/

/*
* Ʈ�� ��ȸ ���
* ���� ���� ���� ��ȸ 3������ ����
* 
* ���� ��ȸ - pre order	: NLR ������ �д°�
* ���� ��ȸ - in order	: LNR 
* ���� ��ȸ - post order	: LRN ������ ����
*/

/*
* BST ���̳ʸ� ��ġ Ʈ�� = ���� Ž�� Ʈ��
* - �ڱ� �ڽŰ�, ����, �������� �����ϴ� ��带 ������ ����
* - Node�� �������� ���ʰ� ������ ���� ���� �� �֤�.
* - �������� ���� ū���� ���������� �����ϸ� ��Ģ���� ���´�
* - Ư���� ��Ģ�� ���� Ŭ������ ���� ������ ����ϱ�
*/

/*
* BST ����
* ���� �����̳� ��� - Ž�� �� ������ ȿ�������� �ʴٴ� ������ ����
* ���� �����̳� ��� - "Tree �ڷ� ����"
* BST - ���� �˻� �˰������� �ڷᱸ���� ǥ���� ��
* ���� : ��尡 �������� ġ��ĥ ��� n��ŭ �ð��� �ɸ� 
*/

struct Node
{
	int value;
	Node* leftNode;
	Node* rightNode;

public:
	Node(int val) : value(val), leftNode(nullptr), rightNode(nullptr) {}
};

#pragma region Tree ��ȸ ���
class Tree
{

public:
	void PreOrder(Node* root)	// ���� ��ȸ ���
	{
		if (root == nullptr) { return; }	// root�� ���̻� �ƹ��͵� ����Ű�� �ʴ´ٸ�
		cout << root->value << " ";
		PreOrder(root->leftNode);							// L�� �ִ� ���� ���� PreOrder ����
		PreOrder(root->rightNode);							// R�� �ִ� ���� ���� PreOrder ����
	}

	void InOrder(Node* root)	// ���� ��ȸ ���		LNR
	{
		if (root == nullptr) { return; }
		InOrder(root->leftNode);
		cout << root->value << " ";
		InOrder(root->rightNode);
	}

	void PostOrder(Node* root)	// ���� ��ȸ ���
	{
		if (root == nullptr) { return; }
		PostOrder(root->leftNode);
		PostOrder(root->rightNode);
		cout << root->value << " ";
	}
};
#pragma endregion

#pragma region Node ���� ���� �ϱ�

void NodeConnect()
{
	Node* root = new Node(4);

	root->leftNode = new Node(2);
	root->leftNode->leftNode = new Node(9);
	root->leftNode->rightNode = new Node(7);

	root->rightNode = new Node(6);
	root->rightNode->leftNode = new Node(1);


	cout << "���� ��ȸ ���" << endl;
	Tree tree;
	tree.PreOrder(root);

	cout << endl;

	cout << "���� ��ȸ ���" << endl;
	Tree tree2;
	tree2.InOrder(root);
	cout << endl;


	cout << "���� ��ȸ ���" << endl;
	Tree tree3;
	tree3.PostOrder(root);
	
}
#pragma endregion

#pragma region ���� Ž�� Ʈ�� ����
/*
* root�������� ������ ����
* root���� ������ ����, ũ�� ���������� ����
* ��� �����͸� ������ ���� ��ȸ(LNR)�� ������ �������� �����ͷ� ���ĵ� 
*/

class BST
{
private:
	Node* root;		// ���� ���ϰ� private�� ����

	Node* insert(Node* node, int value)
	{
		// �����Ͱ� 0���� �� 
		if (node == nullptr)
		{
			return new Node(value);
		}

		// node���� ������ ���� ũ�� ������

		if (node->value > value)
		{
			node->leftNode = insert(node->leftNode, value);		// ���ε��� ���� ������ ���ʿ� ����
		}
		else if (node->value < value)
		{
			node->rightNode = insert(node->rightNode, value);	// ���ε��� ���� ũ�� �����ʿ� ����
		}
		return node;
	}

	void inorder(Node* node)	// L->N->R
	{
		if (node == nullptr) { return; }		// node�� nullptr�̸� ��ȯ
		inorder(node->leftNode);
		cout << node->value << " ";
		inorder(node->rightNode);

	}

public:
	BST()	// ������ ���鶧 �ʱ�ȭ ���ֱ� (ȯ�渶�� �ٸ�)
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
	
};

#pragma endregion


int main()
{
	NodeConnect();
	cout << endl;

	cout << "���� Ž�� Ʈ�� ����" << endl;		

	BST bst;
	bst.insert(1);
	bst.insert(6);
	bst.insert(4);
	bst.insert(3);
	bst.insert(9);
	bst.insert(7);

	bst.inorder();

}