/*
* Dynamic Programing (동적 계획법)
* 자료형, 클래스(함수), 포인터, 자료구조
* 
* 알고리즘 시험, 코드를 작성하는 능력을 평가하기 위한 시험
* 프로그래밍 사고력을 잘 가지고 있는지 (기초 실력)
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
* 알고리즘 기출 문제
* 정렬, 탐색, 트리 순회, 그래프 순회, 탐색(DFS, BFS)
* 동적계획법, 그리디 알고리즘, 완전 탐색
* 문제를 푸는 해결 앙이디어를 개념으로 정의한 것
*/

/*
* DP 개념
* - 절차적으로 계획을 세운다.
* - 중복되는 문제를 한 번만 사용해서 해결하고 싶을 때
* - 메모리에 기억을 해서 사용하겠다.
* - 
*/

/*
* 피보나치 수열 구현
* 1, 2, 3, 5, 8, 13 .. -> 함수로 표현하기
*/ 

int Fibonacci(int n)
{
	if(n==1)
		return 1;

	if (n == 2)
		return 2;

	// 반복문 또는 재귀함수로 표현할 수 있음 
	return Fibonacci(n - 1) + Fibonacci(n - 2);
	
}

/*
* 재귀 방식의 피보나치 구현이 시간이 오래 걸리는 이유
* n의 숫자가 커지면 커질수록 Fibonacci 함수가 계속 실행된다.
* 재귀 함수를 사용하고 n이 커지면 커질수록 스택에 메모리가 쌓인다. => 스택 오버 플로우 발생
* 중복이 발생하는 문제를 해결하기 위해 메모리 공간을 확보해서 저장해두었다가 사용한다 (메모이제이션) 메모리제이션?
*/

/*
* 동적계획법의 구현 방식
* Top - down 방식 :	재귀 방식, 컨테이너 구현
* bottom - Up : 반복문 컨테이너 구현
*/
int FinoDP(int n)		// bottom - up (반복문, 컨테이너)
{
	if (n <= 1) { return n; }
	
	//vector<int> vec;

	// 임시 저장할 컨테이너 만들기
	vector<int> dp(n + 1, 0);	// 생성자로 표현, n개의 빈 공간이 있는 배열을 만들어서 생성한다.

	// bottom - up dp[n]까지 도달하기 위해서 dp[0] ~ dp[n]을 채워나가는 것
	dp[0] = 0;
	dp[1] = 1;
	//dp[2] = 2;

	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}

class FiboRecursive
{
private:
	vector<int> dp;

public:
	FiboRecursive(int n)
	{
		dp.resize(n + 1, -1);
		dp[0] = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                             
		dp[1] = 1;                                                                                                                                                                                                                                                                                                                                                                                                                                             
	}

	int FiboRecur(int n)
	{
		// dp에 값이 이미 존재 한다면, -1이 아니면 
		// 재귀함수 return 실행, 아레에 자기자신 함수를 실행한다.
		if (dp[n] != -1)
		{
			return dp[n];
		}
			dp[n] = FiboRecur(n - 1) + FiboRecur(n - 2);
			
			return dp[n];
	}
};

/*
* 계단 오르기 문재
* 
* 한 계단을 오르거나 2개 다 한번에 오르거나 두가지 방식으로 계단을 오를 수 잇다
* 예를들어 3번째 계단을 올라가기 위해선 2가지 방식이 존재 (n>1) 
* 이때 가장 최소한의 비용으로 n의 계단을 오르는 방법 구현하기 
* 핵심 아이디어 : n번째 계단을 최소한으로 올라야 한다. 1칸식 오를 때 vs 2칸씩 오를 때 비교할 수 있어야 한다.
* 

*/

/*
* 계단을 오르는 경우의 수
* 두번째 계단을 오르기위한 방법 : 한칸씩 오른다 vs 두칸 한번에올라간다.		
* CountStep(1)=1;
* CountStep(2)=2;
*/

/*
* cashe : 캐시 (임시로 저장된 데이터 디피) 삭제
* 중복되는 사항이 있을 때 데이터ㅋ를 저장해서 사용하면 빠르게 사용할 수 있다.
* 메모리 공간을 사용해야 한다. "캐싱" : 최적화 방법 중 하나이다. (시간을 확보할 수 있는)
*/

/*
* 시험 문제가 나오면 DP로 해결하라고 하지않는다.
* 계단 문제를 분석하고 그 다음에 다음 문제가 DP로 풀어야되겠구나하고 생각을 해야한다.
* (1) 각 개념마다 키워드들이 존재한다. -> 최소, 저렴하게, 가장 빠르게
* (2) 기출문제도 존재한다. (경험으로 풀어보는 것)
*/
class GaneCashe
{
private:
	unordered_map<int, int> exps;	// 해시를 이용한 자료구조, 탐색에서 매우 빠르다. 순서 없이 저장되는 컨테이너 
	unordered_map<int, int> damages;	// 공격력

	struct UserData
	{
		int level;
		int exps;
		int damage;
	};

public:
	int CalculateExp(int level)
	{
		// 5레벨까지 필요한 경험치
		if (exps.find(level) != exps.end())
		{
			cout << "캐시에서 데이터를 가져옴" << "(레벨 " << level << " : " << exps[level] << ")" << endl;
			return exps[level];
		}

		// 게임당 레벨 당 필요한 경험치를 구하는 공식이 필요하다.

		int exp = level * (level + 100);	// 101, 204, 309 등
		
		exps[level] = exp;
		return exp;
	}

	int CalculateDamage(int level)
	{
		if (damages.find(level) != damages.end())
		{
			cout << "캐시에서 데이터를 가져옴" << "(공격력 " << level << " : " << damages[level] << ")" << endl;
			return damages[level];
		}

		int damage = level * 2;
		damages[level] = damage;

		return damage;
	}

};

int CountStep(int n)
{
	return n;
	vector<int> dp(n + 1, 0);		// n+1 하는 이유 : dp[6] 0부터 시작했을 때 2번째 데이터를 사용해야한다.
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2;i <= n; i++)
	{
		dp[n] = dp[n - 1] + dp[n - 2];
	}
	return dp[n];
}

int main()
{
	cout << "피보나치 재귀 구현 예시" << endl;
	cout << "피보나치 결과 값 : " << Fibonacci(6) <<endl;

	cout << "피보나치의 25번째 숫자 출력 : " << Fibonacci(10) << endl;
	cout << endl;

	cout << "피보나치 DP bottom up 방법 구현" << endl;
	cout << "결과값 : " << FinoDP(6) << endl;

	cout << "피보나치 DP Top down" << endl;

	FiboRecursive fibo(6);
	cout << "결과값 : " << fibo.FiboRecur(6) << endl;

	//cout << "계단 오르기 경우의 수 출력" << endl;

	cout << "게임 캐싱 데이터 예제" << endl;

	GaneCashe gamecashe;
	cout << "1레벨 경험치 : " << gamecashe.CalculateExp(1) << endl;
	cout << "1레벨 경험치 : " << gamecashe.CalculateExp(1) << endl;

	cout << endl;

	cout << "1레벨일때 데미지 : " << gamecashe.CalculateDamage(1) << endl;
	cout << "1레벨일때 데미지 : " << gamecashe.CalculateDamage(1) << endl;
	
	return 0;
}