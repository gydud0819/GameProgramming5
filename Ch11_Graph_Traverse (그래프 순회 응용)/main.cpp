/*
* �ۼ���	:
* ����	: �׷����� �̿��� ����� �ִ� �Ÿ� ���ϱ� 
*/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
* 1. DFS
* - �׷����� ��� ����Ǿ� �ִ��� connected Graph
* - �ٽ� ���̵�� : �׷��� (��, ��)
* - ���� ������ �����Ǿ� �ִ�.
* - ���� �� ���̿� ����� ���� ���ٸ� ��ȸ�ϸ鼭 ���� ������ ������Ű�� ��� ��, ���� ���� �ٸ��� ���� ���̴�.
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
		// 3. �ڱ� �ڽ� �Լ� ȣ���ϱ� (��� ȣ��)
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

	// ��� �׷����� ����Ǿ� �ִ���?

	void DFSCount(int& count, int startV)
	{
		// ��� �Լ� ������� �ϱ� 
		visited[startV] = true;
		count++;

		for (int e : adj[startV])
		{
			if (!visited[e])
			{
				visited[e] = true;
				DFSCount(count, e);
			}
		}

	}

	bool IsConnected(int startV)
	{
		fill(visited.begin(), visited.end(), false);

		int count = 0;
		// DFS ������� ��ȸ�ϸ鼭 ��´�� ī��Ʈ �� ������Ű�� 
		DFSCount(count, startV);
		return count == V;		// ��ȸ�ϸ鼭 ��� ���� ����ƴٸ� 1 �ƴϸ� 0
	}

	void CheckGraphConnected()
	{
		if (IsConnected(0))
		{
			cout << "��� �׷����� ����Ǿ���." << endl;
		}
		else
		{
			cout << "������� ���� �׷����� �����Ѵ�." << endl;
			cout << "-1" << endl;

		}
	}

#pragma region ��� ã�� (�ִ� �Ÿ� ã��)
	/*
	* BFS : ����� ���� �� ���� ã�� ���
	* ���ͽ�Ʈ��(BFS���� �Ļ��� ��) : ����� ���� �� ���� ã�� ���
	* ���� :
	*/

	/*
	*
	*/

	vector<int> ReFindPath(vector<int>& parent, int start, int end)		// ���� ���� �ϴ� �Լ�
	{
		vector<int> path;

		if (parent[end] == -1 && start != end)		// parent�� �����͸� -1�� �ʱ�ȭ �ߴµ� �������� ���ߴٸ� ���� ã�� ���ߴٴ� ��
		{
			return path;							// ���(��)�� ���� �����͸� ��ȯ�Ѵ�. 
		}

		int current = end;
		while (current != -1)
		{
			path.insert(path.begin(), current);
			current = parent[current];
		}

		return path;
	}
	vector<int> FindShortTestPath(int start, int end)		// �ִ� �Ÿ� ����, �������� �ݵ�� �־�� �� 
	{
		if (start == end) return { start };

		fill(visited.begin(), visited.end(), false);
		vector<int> parent(V, -1);		// �ּ� �Ÿ��� �����ϴ� �迭
		vector<int> distance(V, -1);
		queue<int> q;

		q.push(start);
		visited[start] = true;
		distance[start] = 0;

		while (!q.empty())
		{
			int c = q.front();
			q.pop();
			// while�� ���� ���� �ؾ��ϴ� ������ �ʿ���
			if (end == c) break;	// ���� ã�Ҵٸ� (��尡 ��ǥ ������ �������� ��)

			// ������ ���ߴٸ� 
			for (int e : adj[c])
			{
				if (!visited[e])
				{
					visited[e] = true;
					q.push(e);
					parent[e] = c;		// 
					distance[e] = distance[c] + 1;		// 1ĭ �̵��Ҷ����� 1�� ���� ������ (����ġ�� ���� ����)
				}
			}

		}

		return ReFindPath(parent, start, end);
	}

	
#pragma endregion

};

int main()
{
	Graph g(6);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 5);

	g.CheckGraphConnected();

	vector<int> temp = g.FindShortTestPath(0, 5);

	cout << "0���� 5�� �̵��ϴ� �ּ� �Ÿ�" << endl;
	for (auto& e : temp)
	{
		cout << "->" << e;
	}

	return 0;
}