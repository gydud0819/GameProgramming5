/*
* 작성일	: 2025-06-27
* 주제	: 그래프로 게임 노드 표현하기
*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
#pragma region Spire 만들기
/*
* 사용할 자료구조
1. 그래프
2. 위치를 표현하는 코드 (x,y) (x,y,z) + 노드 정보(이름, 아이디)
*/
class Spire
{
	//enum RoomInfo {};
	struct Node
	{
		int x, y;		// 좌표
		int id;
		string name;

		// 시작, 일반, 엘리트, 보스, 상점, 휴식, 이벤트

		Node(string _name, int _id, int _x, int _y) : name(_name), id(_id), x(_x), y(_y) {}
	};
private:
	// 가변 배열 노드를 저장하는 컨테이너 선언하기
	vector<Node> nodes;
	vector<vector<int>> adj;	// 인접 행렬(각 점이 어디에 연결되어 있는지 저장하는 컨테이너)
	vector<bool> visited;

	int nodeCount;
	const int CONSOLEHEIGHT = 40;		// 세로
	const int CONSOLEWIDTH = 80;		// 가로

public:
	Spire() : nodeCount(0) {}

	void AddNode(string _name, int x = 0, int y = 0)		// id와 nodeCount가 일치하게 만든다. 초기화때문에 0으로 일치하게 만드는건가? 
	{
		nodes.emplace_back(_name, nodeCount, x, y);			// nodes 컨테이너 데이터를 추가한다.
		adj.push_back(vector<int>());						// node를 추가할 때 인접 행렬의 공간도 생성한다. 
		visited.push_back(false);							// 방문 체크 공간을 생성한다.
		nodeCount++;										// 노드의 숫자를 증가시킨다.

	}

	void AddEdge(int start, int end)
	{
		adj[start].push_back(end);		// 방향이 있는 벡터이기 때문에 역순으로 연결을 하지 않는다.

	}

	void printGraph()
	{
		for (int i = 0; i < nodeCount; i++)
		{
			cout << "노드 : " << i << "(" << nodes[i].name << ")" << endl;
			cout << "연결된 노드 : ";

			if (adj[i].empty())
			{
				cout << "없음";
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

	vector<int> ReFindPath(vector<int>& parent, int start, int end)		// 길을 삭제 하는 함수
	{
		vector<int> path;

		if (parent[end] == -1 && start != end)		// parent의 데이터를 -1로 초기화 했는데 접근하지 못했다면 길을 찾지 못했다는 뜻
		{
			return path;							// 경로(길)가 없는 데이터를 반환한다. 
		}

		int current = end;
		while (current != -1)
		{
			path.insert(path.begin(), current);
			current = parent[current];
		}

		return path;
	}
	vector<int> FindShortTestPath(int start, int end)		// 최단 거리 순서, 목적지가 반드시 있어야 함 
	{
		if (start == end) return { start };

		fill(visited.begin(), visited.end(), false);
		vector<int> parent(nodeCount, -1);		// 최소 거리를 저장하는 배열
		vector<int> distance(nodeCount, -1);
		queue<int> q;

		q.push(start);
		visited[start] = true;
		distance[start] = 0;

		while (!q.empty())
		{
			int c = q.front();
			q.pop();
			// while을 강제 종료 해야하는 조건이 필요함
			if (end == c) break;	// 길을 찾았다면 (노드가 목표 지점에 도착했을 때)

			// 도착을 안했다면 
			for (int e : adj[c])
			{
				if (!visited[e])
				{
					visited[e] = true;
					q.push(e);
					parent[e] = c;		// 
					distance[e] = distance[c] + 1;		// 1칸 이동할때마다 1을 증가 시켜줌 (가중치가 없기 때문)
				}
			}

		}

		return ReFindPath(parent, start, end);
	}
	// 그래프를 그래픽으로 표현하는 코드
private:

	void CalculateNodePos()		// 노드 좌표 계산 코드, 추가해준 노드들을 레벨별로 좌표를 설정한다.
	{
		if (nodeCount == 0) return;

		vector<vector<int>> levels;		// 던전의 층을 저장하는 컨테이너 
		vector<bool> processed(nodeCount, false);			// 지역 변수로 선언(매번 초기화 가능(?), 방문한 노드를 기록하는 데이터

		levels.push_back({ 0 });		// 시작지점 0층은 항상 0이다
		processed[0] = true;			// 시작지점을 방문함, 한 번 거친 곳은 못가게 한다.

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
			currentLevel++;			// 다음 층 계산하도록 
		}

		// 모든 층의 레벨을 계산 했다면 각 노드가 몇 층에 있고 몇번째에 있는지 위 코드를 통해 기록이 된다.
		for (int level = 0; level < levels.size(); level++)		// 0층부터 마지막 층까지 반복한다.
		{
			int nodeLevel = levels[level].size();				// 각 층의 방의 개수
			int spacing = CONSOLEWIDTH / (nodeLevel + 1);					// const ConsoleWIDTH = 80; 가로 콘솔 크기 = 80

			for (int i = 0; i < nodeLevel; i++)
			{
				int nodeId = levels[level][i];
				nodes[nodeId].x = spacing * (i + 1);			// i가 0부터 시작하기 때문에 1을 더해서 계산한다.
				nodes[nodeId].y =level * 2 + 2;					// 각 층의 여백 크기를 설정한다. (x,y 좌표를 설정)

			}
		}
	}

	void DrawCircle(vector<vector<char>>& screen, int x, int y)
	{
		screen[y][x] = '0';
	}

	void DrawLine(vector<vector<char>>& screen, int x1, int x2, int y1, int y2)		// 정수 사이의 픽셀을 그리는 알고리즘		Bresenham 찾아보기 
	{
		int dx = abs(x2 - x1);
		int dy = abs(y2 - y1);

		int sx = (x1 < x2) ? 1 : -1;
		int sy = (y1 < y2) ? 1 : -1;

		int err = dx - dy;		// 미분 방정식 같은데 

		int x = x1;				// x, y 좌표를 알고리즘 공식에 의해 다음 위치로 변경해준다. 
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
		DrawEdge(screen);				// 선을 먼저 그리고
		DrawNode(screen);				// 선 위에 점을 찍는다. 
		printScreen(screen);
	}
};
#pragma endregion

int main()
{
	Spire spire;
	cout << "슬레이더 스파이어의 맵 구현" << endl;

	spire.AddNode("시작");			// 0
	spire.AddNode("1층 전투방");		// 1
	spire.AddNode("1층 전투방");		// 2
	spire.AddNode("1층 전투방");		// 3
	spire.AddNode("1층 전투방");		// 4
	spire.AddNode("1층 전투방");		// 5

	spire.AddNode("2층 엘리트방");	// 6
	spire.AddNode("2층 전투방");		// 7
	spire.AddNode("2층 전투방");		// 8
	spire.AddNode("2층 이벤트");		// 9
	spire.AddNode("2층 휴식");		// 10

	spire.AddNode("3층 휴식");
	spire.AddNode("3층 이벤트");
	spire.AddNode("3층 휴식");
	spire.AddNode("3층 이벤트");

	spire.AddNode("4층 휴식");
	spire.AddNode("5층 보스");

	// node 선 정의하기
	spire.AddEdge(0, 1); spire.AddEdge(1, 6); spire.AddEdge(6, 11); spire.AddEdge(11, 15); spire.AddEdge(15, 16);

	spire.AddEdge(0, 2); spire.AddEdge(2, 7); spire.AddEdge(7, 11);

	spire.AddEdge(0, 3); spire.AddEdge(3, 8); spire.AddEdge(8, 12); spire.AddEdge(12, 15);
	spire.AddEdge(3, 9); spire.AddEdge(9, 12);

	spire.AddEdge(0, 4); spire.AddEdge(4, 9); spire.AddEdge(9, 13); spire.AddEdge(13, 15);

	spire.AddEdge(0, 5); spire.AddEdge(5, 10); spire.AddEdge(10, 14); spire.AddEdge(14, 15);

	// 1~2층


	spire.printGraph();

	spire.DrawGraph();

	vector<int> temp = spire.FindShortTestPath(0, 13);

	for (auto& e : temp)
	{
		cout << e << " -> ";
	}
	return 0;
}
