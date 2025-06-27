/*
* �ۼ���	: 2025-06-27
* ����	: �׷����� ���� ��� ǥ���ϱ�
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
#pragma region Spire �����
/*
* ����� �ڷᱸ��
1. �׷���
2. ��ġ�� ǥ���ϴ� �ڵ� (x,y) (x,y,z) + ��� ����(�̸�, ���̵�)
*/
class Spire
{
	//enum RoomInfo {};
	struct Node
	{
		int x, y;		// ��ǥ
		int id;
		string name;

		// ����, �Ϲ�, ����Ʈ, ����, ����, �޽�, �̺�Ʈ

		Node(string _name, int _id, int _x, int _y) : name(_name), id(_id), x(_x), y(_y) {}
	};
private:
	// ���� �迭 ��带 �����ϴ� �����̳� �����ϱ�
	vector<Node> nodes;
	vector<vector<int>> adj;	// ���� ���(�� ���� ��� ����Ǿ� �ִ��� �����ϴ� �����̳�)
	vector<bool> visited;

	int nodeCount;
	const int CONSOLEHEIGHT = 40;		// ����
	const int CONSOLEWIDTH = 80;		// ����

public:
	Spire() : nodeCount(0) {}

	void AddNode(string _name, int x = 0, int y = 0)		// id�� nodeCount�� ��ġ�ϰ� �����. �ʱ�ȭ������ 0���� ��ġ�ϰ� ����°ǰ�? 
	{
		nodes.emplace_back(_name, nodeCount, x, y);			// nodes �����̳� �����͸� �߰��Ѵ�.
		adj.push_back(vector<int>());						// node�� �߰��� �� ���� ����� ������ �����Ѵ�. 
		visited.push_back(false);							// �湮 üũ ������ �����Ѵ�.
		nodeCount++;										// ����� ���ڸ� ������Ų��.

	}

	void AddEdge(int start, int end)
	{
		adj[start].push_back(end);		// ������ �ִ� �����̱� ������ �������� ������ ���� �ʴ´�.

	}

	void printGraph()
	{
		for (int i = 0; i < nodeCount; i++)
		{
			cout << "��� : " << i << "(" << nodes[i].name << ")" << endl;
			cout << "����� ��� : ";

			if (adj[i].empty())
			{
				cout << "����";
			}
			else
			{
				for (int j = 0; j < adj[i].size(); j++)
				{
					cout << adj[i][j] << "(" << nodes[adj[i][j]].name << ")" << endl;

					if (j < adj[i].size() - 1)
					{
						cout << ", ";
					}
				}
			}
			cout << endl;
		}
	}

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
		vector<int> parent(nodeCount, -1);		// �ּ� �Ÿ��� �����ϴ� �迭
		vector<int> distance(nodeCount, -1);
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
	// �׷����� �׷������� ǥ���ϴ� �ڵ�
private:

	void CalculateNodePos()		// ��� ��ǥ ��� �ڵ�, �߰����� ������ �������� ��ǥ�� �����Ѵ�.
	{
		if (nodeCount == 0) return;

		vector<vector<int>> levels;		// ������ ���� �����ϴ� �����̳� 
		vector<bool> processed(nodeCount, false);			// ���� ������ ����(�Ź� �ʱ�ȭ ����(?), �湮�� ��带 ����ϴ� ������

		levels.push_back({ 0 });		// �������� 0���� �׻� 0�̴�
		processed[0] = true;			// ���������� �湮��, �� �� ��ģ ���� ������ �Ѵ�.

		int currentLevel = 0;
		while (currentLevel < levels.size())
		{
			vector<int> nextLevel;

			for (int node : levels[currentLevel])
			{
				for (int neighbor : adj[node])
				{
					if (!processed[neighbor])
					{
						nextLevel.push_back(neighbor);
						processed[neighbor] = true;
					}
				}
			}
			if (!nextLevel.empty())
			{
				levels.push_back(nextLevel);
			}
			currentLevel++;			// ���� �� ����ϵ��� 
		}

		// ��� ���� ������ ��� �ߴٸ� �� ��尡 �� ���� �ְ� ���°�� �ִ��� �� �ڵ带 ���� ����� �ȴ�.
		for (int level = 0; level < levels.size(); level++)		// 0������ ������ ������ �ݺ��Ѵ�.
		{
			int nodeLevel = levels[level].size();				// �� ���� ���� ����
			int spacing = CONSOLEWIDTH / (nodeLevel + 1);					// const ConsoleWIDTH = 80; ���� �ܼ� ũ�� = 80

			for (int i = 0; i < nodeLevel; i++)
			{
				int nodeId = levels[level][i];
				nodes[nodeId].x = spacing * (i + 1);			// i�� 0���� �����ϱ� ������ 1�� ���ؼ� ����Ѵ�.
				nodes[nodeId].y =level * 2 + 2;					// �� ���� ���� ũ�⸦ �����Ѵ�. (x,y ��ǥ�� ����)

			}
		}
	}

	void DrawCircle(vector<vector<char>>& screen, int x, int y)
	{
		screen[y][x] = '0';
	}

	void DrawLine(vector<vector<char>>& screen, int x1, int x2, int y1, int y2)		// ���� ������ �ȼ��� �׸��� �˰���		Bresenham ã�ƺ��� 
	{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);

		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;

		int err = dx - dy;		// �̺� ������ ������ 

		int x = x1;				// x, y ��ǥ�� �˰��� ���Ŀ� ���� ���� ��ġ�� �������ش�. 
		int y = y1;

		while (true)
		{
			if (x >= 0 && CONSOLEWIDTH && y >= 0 && y < CONSOLEHEIGHT)
			{
				if (screen[y][x] == ' ')
				{
					screen[y][x] = '-';
				}

				if (x == x2 && y == y2)
				{
					break;
				}
				int e2 = 2 * err;
				if (e2 > -dy)
				{
					err -= dy;
					x += sx;

				}
				if (e2 < -dy)
				{
					err += dy;
					y += sy;

				}
			}
		}

	}

	void DrawEdge(vector<vector<char>>& screen)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			for (int neighbor : adj[i])
			{
				DrawLine(screen, nodes[i].x, nodes[i].y, nodes[neighbor].x, nodes[neighbor].y);
			}
		}
	}

	void DrawNode(vector<vector<char>>& screen)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			DrawCircle(screen, nodes[i].x, nodes[i].y);
		}
	}

	void printScreen(vector<vector<char>>& screen)
	{
		cout << endl;
		for (int y = 0; y < CONSOLEHEIGHT; y++)
		{
			for (int x = 0; x < CONSOLEWIDTH; x++)
			{
				cout << screen[y][x];
			}
		}
		cout << endl;
	}

public:
	void DrawGraph()
	{
		vector<vector<char>> screen(CONSOLEHEIGHT, vector<char>(CONSOLEWIDTH, ' '));
		CalculateNodePos();
		DrawEdge(screen);				// ���� ���� �׸���
		DrawNode(screen);				// �� ���� ���� ��´�. 
		printScreen(screen);
	}
};
#pragma endregion

int main()
{
	Spire spire;
	cout << "�����̴� �����̾��� �� ����" << endl;

	spire.AddNode("����");			// 0
	spire.AddNode("1�� ������");		// 1
	spire.AddNode("1�� ������");		// 2
	spire.AddNode("1�� ������");		// 3
	spire.AddNode("1�� ������");		// 4
	spire.AddNode("1�� ������");		// 5

	spire.AddNode("2�� ����Ʈ��");	// 6
	spire.AddNode("2�� ������");		// 7
	spire.AddNode("2�� ������");		// 8
	spire.AddNode("2�� �̺�Ʈ");		// 9
	spire.AddNode("2�� �޽�");		// 10

	spire.AddNode("3�� �޽�");
	spire.AddNode("3�� �̺�Ʈ");
	spire.AddNode("3�� �޽�");
	spire.AddNode("3�� �̺�Ʈ");

	spire.AddNode("4�� �޽�");
	spire.AddNode("5�� ����");

	// node �� �����ϱ�
	spire.AddEdge(0, 1); spire.AddEdge(1, 6); spire.AddEdge(6, 11); spire.AddEdge(11, 15); spire.AddEdge(15, 16);

	spire.AddEdge(0, 2); spire.AddEdge(2, 7); spire.AddEdge(7, 11);

	spire.AddEdge(0, 3); spire.AddEdge(3, 8); spire.AddEdge(8, 12); spire.AddEdge(12, 15);
	spire.AddEdge(3, 9); spire.AddEdge(9, 12);

	spire.AddEdge(0, 4); spire.AddEdge(4, 9); spire.AddEdge(9, 13); spire.AddEdge(13, 15);

	spire.AddEdge(0, 5); spire.AddEdge(5, 10); spire.AddEdge(10, 14); spire.AddEdge(14, 15);

	// 1~2��


	spire.printGraph();

	spire.DrawGraph();

	vector<int> temp = spire.FindShortTestPath(0, 13);

	for (auto& e : temp)
	{
		cout << e << " -> ";
	}
	return 0;
}
