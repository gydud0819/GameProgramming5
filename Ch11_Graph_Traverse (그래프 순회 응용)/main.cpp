/*
* 작성일	:
* 주제	: 그래프를 이용한 노드의 최단 거리 구하기 
*/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

/*
* 1. DFS
* - 그래프가 모두 연결되어 있는지 connected Graph
* - 핵심 아이디어 : 그래프 (점, 선)
* - 점의 개수가 고정되어 있다.
* - 만약 점 사이에 연결된 길이 없다면 순회하면서 점의 개수를 증가시키는 결과 값, 점의 수가 다르게 나올 것이다.
*/

class Graph
{
private:
	int V;		// 점의 개수 (도시, 노드)
	//int[y][x];		// 밑의 방법으로 표현 가능
	vector<vector<int>> adj;		// 이중벡터			// 각 점에서 인접한 점을 연결하는 2차원 배열

	vector<bool> visited;				// 한번 지나간 길은 들린 걸로 간주하기

	void DFS(int v)
	{
		// v를 방문하면 visited를 true로 바꾸기
		visited[v] = true;
		cout << v << " ";

		for (auto& i : adj[v])
		{
			// adj에 B C D가 있음 그중 B를 실행할 거임 == 재귀함수 방식

			if (visited[i] == false) // 단 방문했던 지점은 다시 방문을 해서는 안되기에 if문으로 조건 걸기
				DFS(i);		// DFS(B) -> DFS(C) -> DFS(D)
		}
	}

	void DFSIter(int v)		// 반복자 iterator를 사용한 함수
	{
		// 방문한 visited를 true로 변환하기
		// 재귀 함수 방식을 사용하지 않고 반복문을 사용해서 표현하기
		stack<int> stack;		// stack을 사용한 깊이 우선 탐색 
		visited[v] = true;
		// push - pop 함수 사용하기
		stack.push(v);
		cout << v << " ";
		// while(empty()) 사용하기
		while (!stack.empty())
		{
			// top(), pop() 함수 사용하기
			int Cvertex = stack.top();
			stack.pop();
			// 방문하지 않았을 때만

			// stack : 데이터 삽입 후, 가장 마지막에 들어온 데이터를 먼저 실행
			// 반복문을 사용하여 역순으로 데이터를 실행하게 만든다.

			if (visited[Cvertex] == false)
			{
				visited[Cvertex] = true;
				cout << v << " ";
			}

			// 이웃 노드
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
		q.push(start);				// 그래프의 시작 노드 삽입하기

		while (!q.empty())
		{
			int c = q.front();
			q.pop();

			cout << c << " ";

			for (auto& e : adj[c])	// c에 연결되어있는 노드를 접근하는 코드 adj[c]
			{
				if (visited[e] == false)
				{
					visited[e] = true;		// 방문 안했으면 트루로 한다. 
					q.push(e);

				}


			}
		}
	}

	void BFSRecursive(queue<int>& q)
	{
		// 1. 재귀 함수의 탈출조건 쓰기 ( q가 (empty) 비엇을때)
		if (q.empty()) { return; }

		int c = q.front();
		q.pop();

		cout << c << " ";

		// 2. BFS 반복방식 코드 가져오기 
		for (auto& e : adj[c])
		{
			if (visited[e] == false)
			{
				visited[e] = true;
				q.push(e);
			}
		}
		// 3. 자기 자신 함수 호출하기 (재귀 호출)
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
	// 점의 개수를 생성자로 초기화 하기
	Graph(int vertices) : V(vertices)
	{
		adj.resize(V);	// 점 개수만큼 
		visited.resize(V, false);
	}

	void addEdge(int u, int v)		// 쌍방향, 단방향 연결
	{
		adj[u].push_back(v);		// u가 1, v가 2		1번 점에 연결된 값 : 2
		adj[v].push_back(u);		// v가 1, u가 2		1번 점에 연결된 값 : 1
	}

	void printEdge()
	{
		for (int i = 0; i < V; i++)
		{
			cout << "정점" << i << "의 인접한 리스트 : ";
			for (auto& elem : adj[i])
			{
				cout << "→ " << elem;
			}
			cout << endl;
		}
	}

	void DFSTraverse(int startV)
	{
		// 방문한 경험을 초기화한다.
		fill(visited.begin(), visited.end(), false);

		cout << "DFS 탐색 결과 (시작 지점 : " << startV << ")" << endl;
		DFS(startV);
		cout << endl;

	}

	void DFSIterTraverse(int startV)
	{
		fill(visited.begin(), visited.end(), false);

		cout << "DFSIter 탐색 결과 (시작 지점 : " << startV << ")" << endl;
		DFSIter(startV);
		cout << endl;
	}

	void BFSTraverse(int startV)
	{
		fill(visited.begin(), visited.end(), false);		// 방문한 경험을 초기화 하는 코드

		cout << "BFS 탐색 결과 (시작 지점 : " << startV << ")" << endl;
		BFS(startV);
		cout << endl;
	}

	void BFSIterTraverse(int startV)
	{
		fill(visited.begin(), visited.end(), false);		// 방문한 경험을 초기화 하는 코드

		cout << "BFSIter 탐색 결과 (시작 지점 : " << startV << ")" << endl;
		BFSIter(startV);
		cout << endl;
	}

	// 모든 그래프가 연결되어 있는지?

	void DFSCount(int& count, int startV)
	{
		// 재귀 함수 방식으로 하기 
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
		// DFS 방식으로 순회하면서 출력대신 카운트 수 증가시키기 
		DFSCount(count, startV);
		return count == V;		// 순회하면서 모든 곳이 연결됐다면 1 아니면 0
	}

	void CheckGraphConnected()
	{
		if (IsConnected(0))
		{
			cout << "모든 그래프가 연결되었다." << endl;
		}
		else
		{
			cout << "연결되지 않은 그래프가 존재한다." << endl;
			cout << "-1" << endl;

		}
	}

#pragma region 경로 찾기 (최단 거리 찾기)
	/*
	* BFS : 비용이 없을 때 길을 찾는 방법
	* 다익스트라(BFS에서 파생된 것) : 비용이 있을 때 길을 찾는 방법
	* 프림 :
	*/

	/*
	*
	*/

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
		vector<int> parent(V, -1);		// 최소 거리를 저장하는 배열
		vector<int> distance(V, -1);
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

	cout << "0에서 5로 이동하는 최소 거리" << endl;
	for (auto& e : temp)
	{
		cout << "->" << e;
	}

	return 0;
}