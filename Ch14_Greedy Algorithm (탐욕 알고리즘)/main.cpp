/*
* 작성일 : 2025-07-01
* 주제 : 탐욕 알고리즘
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <chrono>

using namespace std;


/*
* 탐욕 알고리즘
* 문제 풀이 방식의 하나
* 최적의 해를 찾기 위해서 현재 상황에서 가장 최선의 방법을 계속해서 선택하는 방식
*/

/*
* 1, 2, 3번 문제
* 동전을 거슬러 주는 문제
* n원을 동전으로만 거슬러 줘야하는데 동전의 종류
* 500원, 100원, 50원 10원이 있고, 이 때 동전을 최소한의 갯수로 거슬러주고싶ㅇ르 때
* n원을 거슬러 주기 위한 동전의 최소 갯수 n 반환하기

*/
#pragma region 동전 거슬러 주는 문제
// 1260원을 동전으로만 거슬러 줘야할 때 최소한의 동전을 주려면 어떻게 해야할까
// 현재 상황에서 가장 최선을 선택하고 싶을 때 (IDEA) (Greedy)
// 500원 a, 100원 b, 50원 c, 10원 d				a+b+c+d 반환하기 2+2+1+1
int CoinBack(int amount)		// amount 거슬러 줘야하는 총 금액
{
	// amount 각각에 정해진 수치로 분할해야 한다.
	// 몫과 나머지를 사용해서 a,b,c,d를 표현하고 그 값을 리턴하기

	// 반복되는 부분을 for문 돌려서 계산하기 

	/*
	* vector int를 저장하는 것이 아니라 coin 자료형을 만들어서 표현하기
	*/

	struct Coin
	{
		int value;
		int count;

		Coin(int _value) : value(_value), count(0) {}
	};

	// CointWallet 이름으로 Coin을 생성과 동시에 추가하기


	vector<int> coins = { 500,100,50,10 };
	// coins 자료구조는 값이 큰 순서대로 정렬이 되어야 한다. 
	// 내림차순으로 정렬시키는 코드
	int totalCount2 = 0;
	vector<Coin> coinwallet;
	for (int coin : coins)
	{
		coinwallet.emplace_back(coin);
	}

	for (auto& elem : coinwallet)
	{
		int num = amount / elem.value;
		elem.count = num;
		totalCount2 += num;
		amount = amount % elem.value;

		cout << elem.value << "원의 수 : " << elem.count << endl;
	}

	int totalCount = 0;
	for (int coin : coins)
	{
		int num = amount / coin;		// 총금액을 coin으로 나눠준다.
		totalCount += num;
		amount = amount % coin;			// 

		cout << coin << "원의 수 : " << num << endl;
	}

	cout << "동전의 총 개수 : " << totalCount << endl;

	// 직접 작성한 코드
	//int Won = amount;		// 시작 금액

	//int a = Won / 500;		// 이렇게 일일이 계산해야한다고?
	//cout << "500원의 수 : " << a << endl;

	//Won = Won - 500 * a;

	//int b = Won / 100;
	//cout << "100원의 수 : " << b << endl;
	//Won -= 100 * b;

	//int c = Won / 50;
	//cout << "50원의 수 : " << c << endl;
	//Won -= 50 * c;

	//int d = Won / 10;
	//cout << "10원의 수 : " << d << endl;
	//Won -= 10 * d;

	//int totalCount = a + b + c + d;
	//cout << "동전의 총 갯수 : " << totalCount << endl;

	return totalCount;


}
#pragma endregion


#pragma region 회의실 배정 문제
/*
* 회의실이 시작하는 시간과 끝나는 시간을 쌍으로 저장하도록 두 수가 n개 주어진다.
* 이 회의실을 최대로 배정하는 방법 찾아보기
* 최대로 배정할 때 몇개까지 배정할 수 있는지
* 어떤 방식으로 했을 때 최선으로 배정할 수 있는지
*/

/*
* 백준 1931 문제
*
* 1. 시작시간이 가장 작은 순으로 실행한다.
* 2. 끝나는 시간이 가장작은 순으로 정렬한다.
* (첫번째 원소를 사용한다)
*/

int meetingCount(int n)
{
	// 시작시간과 끝나는 시간을 앞에 넣을지 뒤에 넣을지 이유를 생각해서 표현하기

	vector<pair<int, int>> meeting = { {4,1}, {5,3}, {6,0}, { 7,5 }, {8,3}, {9,5}, {10,6}, { 11,8 }, {12,8}, {13,2}, { 14,12 } };

	// 끝나는 시간 순으로 정렬한다. 끝나는 시간을 key값을 first에 저장했다.
	sort(meeting.begin(), meeting.end());

	// 정렬 시키고 난 후의 결과값

	for (auto& i : meeting)
	{
		cout << i.first << "," << i.second << "||";
	}

	// (끝나는 시간, 시작 시간)
	// count을 1씩 증가시킨다.
	// time 현재 회의에서 시작하는 시간
	// 현재 선택된 회의와 끝나는 시간으로 변경해주기 
	// time을 선택된 회의와 끝나는 시간으로 변경해주면 된다.

	int count = 1;
	int time = meeting[0].first;	// 첫번째 시간이 끝나는 시간 

	for (int i = 1; i < n; i++)
	{
		// 현재 선택된 시간 비교하기 (나머지 원소중에서 시작시간이 현재 선택된 시간)
		if (time <= meeting[i].second)
		{
			// 갯수 1증가 시키기
			count++;
			// time을 선택된 시간으로 갱신하기
			time = meeting[i].first;
		}

	}

	return count;
}

#pragma endregion

#pragma region 
/*
* 시작시간, 끝나는 시간을 '초'단위로 계산하기		3600-1800-1800
* 계산된 초를 다시 '시' '분' '초'로 변환해서 출력하는 코드 만들기
* [n시 n분 n초] 만들어주는 코드 작성하기
*/

void FormatTime(int value)
{
	// 2167 -> 시 분 초로 변환하는 코드 만들기 

	struct Time
	{
		int value;
		int count;

		Time(int _value) : value(_value) {}
	};

	// value -> 시 분 초 나누어서 저장하기
	vector<int> times;		// 시 : 3600초==1시간 분
		times.emplace_back(3600);
		times.emplace_back(60);
		times.emplace_back(1);
	
	for (auto& time : times)
	{
		int num = value / time.value;
	}



	cout << "시" << "분" << "초" << endl;
}
#pragma endregion



int main()
{
	cout << "동전 거슬러주기 문제 : 1260원을 반환하기" << endl;
	cout << "결과값" << endl;
	CoinBack(1260);

	cout << endl;

	cout << "회의실 최대 개수 문제" << endl;
	meetingCount(11);

	cout << "값을 시간으로 변환하는 문제" << endl;
	//FormatTime
	return 0;
}