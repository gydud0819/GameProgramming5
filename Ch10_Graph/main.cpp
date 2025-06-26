/*
* �ۼ���	: 2025-06-25
* ����	: �׷����� ���� ����(Graph)
*/
#include <iostream>
#include <vector>
#include <stack>	// DFS == stack���� ǥ��		���� ����
#include <queue>	// BFS == queue�� ǥ��		���� ����
using namespace std;
/*
* �˰��� ����
*
* 1. ���� (������ ������� ����)
* 2. Ž�� (�������� ���� �� ����)
*
* vector : ���� ��Ű�� ���� Ž��
* Tree : �ڷᱸ��, ���� �˻� Ʈ�� (�������� ġ��ģ Ʈ���� ������ ó���� ��ȿ����)
* Heap : �켱���� ť�� �����Ǿ� ����
*/

/*
* Graph
* ��(vertex)�� ��(edge)���� �̷���� ǥ���� �ڷᱸ��
*
* <����>
* ����(direction)�� �����ϴ���
* ��ȯ(cycle)�� �����ϴ���
* ����ġ(weight)�� �����ϴ���
*
* Tree = DAG(������ �����ϰ�, Acycle ��ȯ�� ����, Graph �׷���)
*/

#pragma region Graph(�׷���)
/*
* �׷��� ǥ�� ���
* 1. 2���� �迭�� ǥ��
* 2. �� �������� ����� �����͸� �ڷᱸ���� ǥ���ϴ� ���
*/

/*
* �׷����� ��Ʈ������ ǥ������ �� ������ ��� ���� ���� ����Ǿ� �ִ��� �� �� �ִ�.
* 0�� ���� �ȵ� �� 1�� ���� �Ȱ�
*
*   A B C D
* A 0 1 1 1
* B 1 0 1 1
* c 1 1 0 0
* D 1 1 0 0
*/

/*
* A : (����� ������) B - C - D
* B : A - C - D
* C : A - B
* D : A - B
*/

/*
* ���α׷������� �׷����� ǥ���� �� ����
* ����Ǿ� �ִ� �׷����� Ž���ϴ� ���
*
* 1. ���� �켱 Ž�� (Depth First Search)
* 2. �ʺ� �켱 Ž�� (Breadth First Search)
*
* ����ũ����Ʈ ������ �׷����� �����Ǿ��ֳ�? -> �׷������� Ʈ���� �� ������ Ʈ���� ǥ���ϴ� �� �� ����.
*/

/*
* �׷����� Ž��(��ȸ) ���
* DFS : ���� �켱 Ž��
* - stack :
* BFS : �ʺ� �켱 Ž��
* - queue :
*/

/*
* ���� DFS, BFS�� ����� �� �ִ°�?
* - �׷����� Ž���� �� ���� ������ �� �ִ� �� �����ϱ�
* - DFS : �׷����� ��ȸ�� �ϰ��ִ��� �ľ��� ��
* - BFS : Ư�� ��ġ���� �ּ��� �Ÿ��� �����ϴ� ����� ���� ��
*/

class Graph
{
private:
	int V;		// ���� ���� (����, ���)
	//int[y][x];		// ���� ������� ǥ�� ����
	vector<vector<int>> adj;		// ���ߺ���			// �� ������ ������ ���� �����ϴ� 2���� �迭

	vector<bool> visited;				// �ѹ� ������ ���� �鸰 �ɷ� �����ϱ�

	void DFS(int v)
	{
		// v�� �湮�ϸ� visited�� true�� �ٲٱ�
		visited[v] = true;
		cout << v << " ";

		for (auto& i : adj[v])
		{
			// adj�� B C D�� ���� ���� B�� ������ ���� == ����Լ� ���

			if (visited[i] == false) // �� �湮�ߴ� ������ �ٽ� �湮�� �ؼ��� �ȵǱ⿡ if������ ���� �ɱ�
				DFS(i);		// DFS(B) -> DFS(C) -> DFS(D)
		}
	}

	void DFSIter(int v)		// �ݺ��� iterator�� ����� �Լ�
	{
		// �湮�� visited�� true�� ��ȯ�ϱ�
		// ��� �Լ� ����� ������� �ʰ� �ݺ����� ����ؼ� ǥ���ϱ�
		stack<int> stack;		// stack�� ����� ���� �켱 Ž�� 
		visited[v] = true;
		// push - pop �Լ� ����ϱ�
		stack.push(v);
		cout << v << " ";
		// while(empty()) ����ϱ�
		while (!stack.empty())
		{
			// top(), pop() �Լ� ����ϱ�
			int Cvertex = stack.top();
			stack.pop();
			// �湮���� �ʾ��� ����

			// stack : ������ ���� ��, ���� �������� ���� �����͸� ���� ����
			// �ݺ����� ����Ͽ� �������� �����͸� �����ϰ� �����.

			if (visited[Cvertex] == false)
			{
				visited[Cvertex] = true;
				cout << v << " ";
			}

			// �̿� ���
			for (int i = adj[Cvertex].size() - 1; i >= 0; i--)
			{
				int neighbor = adj[Cvertex][i];		//
				if (visited[neighbor] == false)
				{
					stack.push(neighbor);
				}
			}


		}
	}

	void BFSIter(int start)
	{
		queue<int> q;
		visited[start] = true;
		q.push(start);				// �׷����� ���� ��� �����ϱ�

		while (!q.empty())
		{
			int c = q.front();
			q.pop();

			cout << c << " ";

			for (auto& e : adj[c])	// c�� ����Ǿ��ִ� ��带 �����ϴ� �ڵ� adj[c]
			{
				if (visited[e] == false)
				{
					visited[e] = true;		// �湮 �������� Ʈ��� �Ѵ�. 
					q.push(e);

				}


			}
		}
	}

	void BFSRecursive(queue<int>& q)
	{
		// 1. ��� �Լ��� Ż������ ���� ( q�� (empty) �������)
		if (q.empty()) { return; }

		int c = q.front();
		q.pop();

		cout << c << " ";

		// 2. BFS �ݺ���� �ڵ� �������� 
		for (auto& e : adj[c])
		{
			if (visited[e] == false)
			{
				visited[e] = true;
				q.push(e);
			}
		}
		// 3. �ڱ� �ڽ� �Լ� ȣ���ϱ� (��� ȣ��) == �갡 ���� �����ϴ°�  ������ �߸��ȰŰ����� 
		BFSRecursive(q);

	}

	void BFS(int start)
	{
		queue<int> q;
		q.push(start);
		visited[start] = true;
		BFSRecursive(q);
	}
public:
	// ���� ������ �����ڷ� �ʱ�ȭ �ϱ�
	Graph(int vertices) : V(vertices)
	{
		adj.resize(V);	// �� ������ŭ 
		visited.resize(V, false);
	}

	void addEdge(int u, int v)		// �ֹ���, �ܹ��� ����
	{
		adj[u].push_back(v);		// u�� 1, v�� 2		1�� ���� ����� �� : 2
		adj[v].push_back(u);		// v�� 1, u�� 2		1�� ���� ����� �� : 1
	}

	void printEdge()
	{
		for (int i = 0; i < V; i++)
		{
			cout << "����" << i << "�� ������ ����Ʈ : ";
			for (auto& elem : adj[i])
			{
				cout << "�� " << elem;
			}
			cout << endl;
		}
	}

	void DFSTraverse(int startV)
	{
		// �湮�� ������ �ʱ�ȭ�Ѵ�.
		fill(visited.begin(), visited.end(), false);

		cout << "DFS Ž�� ��� (���� ���� : " << startV << ")" << endl;
		DFS(startV);
		cout << endl;

	}

	void DFSIterTraverse(int startV)
	{
		fill(visited.begin(), visited.end(), false);

		cout << "DFSIter Ž�� ��� (���� ���� : " << startV << ")" << endl;
		DFSIter(startV);
		cout << endl;
	}

	void BFSTraverse(int startV)
	{
		fill(visited.begin(), visited.end(), false);		// �湮�� ������ �ʱ�ȭ �ϴ� �ڵ�

		cout << "BFS Ž�� ��� (���� ���� : " << startV << ")" << endl;
		BFS(startV);
		cout << endl;
	}

	void BFSIterTraverse(int startV)
	{
		fill(visited.begin(), visited.end(), false);		// �湮�� ������ �ʱ�ȭ �ϴ� �ڵ�

		cout << "BFSIter Ž�� ��� (���� ���� : " << startV << ")" << endl;
		BFSIter(startV);
		cout << endl;
	}


};

class GraphMatrix		// ���� ��ķ� ǥ���� �׷���
{
	int V;
	vector<vector<int>> adj;

public:
	GraphMatrix(int v) : V(v), adj(v, vector<int>(v, 0)) {}

	void addEdge(int u, int v)
	{
		adj[u][v] = 1;		// �� ����
		adj[v][u] = 1;
	}

	void printfGraph()
	{
		cout << "���� ��� " << endl;
		for (int i = 0; i < V; i++)
		{
			for (int j = 0; j < V; j++)
			{
				cout << adj[i][j] << " ";
			}
			cout << endl;
		}
	}
};
#pragma endregion


int main()
{
	Graph graph(6);

	graph.addEdge(0, 1);
	graph.addEdge(0, 2);
	graph.addEdge(1, 3);
	graph.addEdge(2, 4);
	graph.addEdge(2, 5);

	graph.DFSTraverse(2);
	cout << endl;
	graph.DFSIterTraverse(3);
	cout << endl;
	graph.BFSTraverse(0);
	cout << endl;
	graph.BFSIterTraverse(0);
	cout << endl;
	graph.printEdge();

	cout << endl;

	GraphMatrix gm(4);
	gm.addEdge(0, 1);
	gm.addEdge(0, 2);
	gm.addEdge(0, 3);

	gm.addEdge(1, 2);
	gm.addEdge(1, 3);
	gm.printfGraph();
	return 0;
}