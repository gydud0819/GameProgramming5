/*
* 작성일	: 2025-06-25
* 주제	: 그래프에 대한 이해(Graph)
*/
#include <iostream>
#include <vector>
#include <stack>	// DFS == stack으로 표현		후입 선출
#include <queue>	// BFS == queue로 표현		선입 선출
using namespace std;
/*
* 알고리즘 정리
*
* 1. 정렬 (데이터 순서대로 나열)
* 2. 탐색 (데이터의 수정 및 삭제)
*
* vector : 정렬 시키고 이진 탐색
* Tree : 자료구조, 이진 검색 트리 (한쪽으로 치우친 트리가 있으면 처리가 비효율적)
* Heap : 우선순위 큐로 구성되어 있음
*/

/*
* Graph
* 점(vertex)과 선(edge)으로 이루어진 표현한 자료구조
*
* <기준>
* 방향(direction)이 존재하는지
* 순환(cycle)이 존재하는지
* 가중치(weight)가 존재하는지
*
* Tree = DAG(방향이 존재하고, Acycle 순환이 없는, Graph 그래프)
*/

#pragma region Graph(그래프)
/*
* 그래프 표현 방법
* 1. 2차원 배열로 표현
* 2. 각 정점에서 연결된 데이터를 자료구조로 표현하는 방식
*/

/*
* 그래프를 매트릭스로 표현했을 때 실제로 어떻게 점과 선이 연결되어 있는지 알 수 있다.
* 0은 연결 안된 거 1은 연결 된거
*
*   A B C D
* A 0 1 1 1
* B 1 0 1 1
* c 1 1 0 0
* D 1 1 0 0
*/

/*
* A : (연결된 데이터) B - C - D
* B : A - C - D
* C : A - B
* D : A - B
*/

/*
* 프로그래밍으로 그래프를 표현할 수 있음
* 연결되어 있는 그래프를 탐색하는 방법
*
* 1. 깊이 우선 탐색 (Depth First Search)
* 2. 너비 우선 탐색 (Breadth First Search)
*
* 마인크래프트 업적도 그래프로 구성되어있나? -> 그래프보단 트리에 더 가깝고 트리로 표현하는 게 더 쉽다.
*/

/*
* 그래프의 탐색(순회) 방법
* DFS : 깊이 우선 탐색
* - stack :
* BFS : 너비 우선 탐색
* - queue :
*/

/*
* 언제 DFS, BFS를 사용할 수 있는가?
* - 그래프를 탐색할 때 쉽게 구현할 수 있는 것 선택하기
* - DFS : 그래프가 순회를 하고있는지 파악할 때
* - BFS : 특정 위치까지 최소의 거리로 도달하는 방법을 구할 때
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
		// 3. 자기 자신 함수 호출하기 (재귀 호출) == 얘가 어디로 가야하는겨  순서가 잘못된거같은디 
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


};

class GraphMatrix		// 인접 행렬로 표현한 그래프
{
	int V;
	vector<vector<int>> adj;

public:
	GraphMatrix(int v) : V(v), adj(v, vector<int>(v, 0)) {}

	void addEdge(int u, int v)
	{
		adj[u][v] = 1;		// 단 방향
		adj[v][u] = 1;
	}

	void printfGraph()
	{
		cout << "인접 행렬 " << endl;
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