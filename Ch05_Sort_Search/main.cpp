/*
* 작성일	: 2025-06-18
* 주제	: 탐색과 이진 탐색
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

/*
* 복습
* 정렬을 다양한 방법으로 직접 구현함
* 정렬을 해야하는 이유
* 새로운 아이템이 컨테이너에 추가될 때 정렬된 상태로 들어가는 경우가 있음
*/

/*
* 탐색 : 컨테이너 안에 데이터가 있는지 없는지 찾는다.
* 탐색을 프로그래밍 코드로 구현해본다.
*
* 1. 앞에서부터 데이터를 비교하여 있는지 없는지 확인하는 코드 만들기 - 선형(순차?) 탐색
* 2. 이진 탐색(binary Search)
* - 컨테이너가 정렬되어 있을 때 중앙 값을 기준으로 데이터를 나누어서 찾는 방법
*/

#pragma region 선형 탐색
/*
* 선형 탐색의 경우 최선의 경우일 때 O(1), 최악의 경우일 때 n의 시간이 걸린다.
* 평균 시간 : O(n)
* 데이터 갯수가 100만을 넘어가면 비효율적이다. (데이터 갯수가 많으면 많을수록)
*
* 분할 정복 알고리즘 : 범위를 나눠서 작은 범위를 해결하는 방식으로 문제를 해결한다.
*/
void LinearSearch(int arr[], int n, int target)	// target은 찾고자 하는 데이터
{
	// 전체 개수를 반복해서 (for문)
	for (int i = 0; i < n; i++)
	{
		// target과 같은 데이터가 존재하면 (if문)
		if (target == arr[i])
		{
			cout << "해당하는 데이터 : " << target << "을(를) 찾았다." << endl;
			return;
		}
	}
	cout << "데이터를 찾지 못했다." <<  endl;

}

// 내가 벡터로 구현을 못하는 이유가 nums로 선언하고 나서 for문안에 일반 nums를 써야할지 nums.함수()를 써야하는지 그래서 헷갈리는거 같은데 될듯말듯하니까 답답하네 ㅇㅅㅇ
// 이거 아닌거 같은데 
void LinearSearch(vector<int>& nums, int arr[], int target)		// 선형 탐색을 벡터로도 구현하기 
{
	int n = nums.size();

	for (int i = 0; i < nums.size(); i++)
	{
		if (target == arr[i])
		{
			cout << "해당하는 데이터 : " << nums.size() << "을(를) 찾았다." << endl;
			return;
		}
	}
	cout << "데이터를 찾지 못했다" << endl;
	
}


#pragma endregion

#pragma region 이진 탐색
/*
* iterator 방식으로 구현한 이진 탐색
*
*/ 
void BinarySearch(int arr[], int n, int target)
{
	// int mid = (left + right) / 2;			20억 + 20억 =  음수가 될수도 있음
	// int mid = left + (right - left) / 2;		왼쪽과 오른쪽거리를 /2 하고 더한다.
	int i = 0;		// 왼쪽
	int j = n - 1;	// 오른쪽
	while (i <= j)	// 왼쪽이 오른쪽보다 작거나 같을 때
	{
		int mid = i + (j - i) / 2;		// 루프를 돌 때마다 데이터를 찾을 때 까지 중앙값을 변경해준다. 
		// mid와 target을 비교하기
		
		// target을 찾은 경우
		if (arr[mid] == target)
		{
			cout << "해당하는 데이터 : " << target << "을(를) 찾았다." << endl;
			return;
		}
		// target이 작은 경우	왼쪽에서 다시 찾기
		else if (arr[mid] > target)
		{
			//mid의 기준으로 j 바꾸기
			j = mid - 1;
		}
		// target이 큰 경우
		else	// (arr[mid] < target)
		{
			// 왼쪽 i가 mid를 기준으로 어떻게 바뀌면 될지 
			i = mid + 1;
		}
	}
}

void BinarySearchRecursive(int arr[], int n, int target, int left, int right)		// 재귀함수로 만들면 문제풀때 
{
	// 재귀 함수가 탈출할 수 있는 조건 만들기
	// left = 왼쪽, right = 오른쪽
	if (left > right)		// 왼쪽이 오른쪽보다 크면
	{
		cout << "데이터를 찾지 못했다." << endl;
		return;				// 반환한다. 
	}
	int mid = (left + right) / 2;
	if (arr[mid] == target)
	{
		cout<< "해당하는 데이터 : " << target << "을(를) 찾았다." << endl;
		return;
	}
	else if (arr[mid] > target)	// 중앙값이 target보다 크면  왼쪽(right = mid - 1)
	{
		BinarySearchRecursive(arr, n, target, left, mid - 1);
	}
	else	// 오른쪽(left = mid + 1)
	{
		BinarySearchRecursive(arr, n, target, mid + 1, right);
	}
	// 자기 자신 함수를 호출하기
}

// 내가 벡터로 구현을 못하는 이유가 nums로 선언하고 나서 for문안에 일반 nums를 써야할지 nums.함수()를 써야하는지 그래서 헷갈리는거 같은데 될듯말듯하니까 답답하네 ㅇㅅㅇ
void BinarySearch(vector<int> nums, int n, int target, int left, int right)		// 벡터로 구현하기 
{
	int i = 0;		// 왼쪽
	int j = n - 1;	// 오른쪽
	while (i <= j)	// 왼쪽이 오른쪽보다 작거나 같을 때
	{
		int mid = i + (j - i) / 2;		// 루프를 돌 때마다 데이터를 찾을 때 까지 중앙값을 변경해준다. 
		// mid와 target을 비교하기

		// target을 찾은 경우
		if (nums[mid] == target)
		{
			cout << "해당하는 데이터 : " << target << "을(를) 찾았다." << endl;
			return;
		}
		// target이 작은 경우	왼쪽에서 다시 찾기
		else if (nums[mid] > target)
		{
			//mid의 기준으로 j 바꾸기
			j = mid - 1;
		}
		// target이 큰 경우
		else	// (arr[mid] < target)
		{
			// 왼쪽 i가 mid를 기준으로 어떻게 바뀌면 될지 
			i = mid + 1;
		}
	}
}
#pragma endregion

/*
* pair<int, 클래스이름>
* 
* vector<pair<int, string>> data;
* pair 타입 선언 방법
* pair.push_back({0, "AAA"});
* 해당하는 인덱스가 있으면 그 인덱스에 저장되어 있는 문자를 출력하는 코드 만들기
* 
* 유저의 ID에 유저가 가진 정보를 저장하고 서버에유저의 ID를 기준으로 해당 유저의 정보(닉네임)을 검색하는 기능 구현하기
*/

// pair를 직접 만들어 구현한 것
template <typename T1, typename T2>
struct Mypair
{
	T1 first;
	T2 second;
};

class Item
{
	int price;
	bool operator < (const Item& other)
	{
		return price < other.price;
	}

public:

};

void UserDataSearch(vector<pair<int, string>> data, int ID)
{
	
}

void Example()
{
	// pair :  데이터 하나를 표현하는 방식
	// key, value 값을 구분해서 저장하는 방식 
	// 연산자 오버로딩, 클래스를 비교하는 재정의 
	vector<pair<int, string>> data;

	data.push_back({ 1, "AAA" });
	data.push_back({ 2, "BBB" });
	data.push_back({ 3, "CCC" });
	data.push_back({ 4, "DDD" });
	data.push_back({ 5, "EEE" });

	make_pair(1, "AAA");

	// 선형 탐색 또는 이진 탐색을 이용하여 결과값 찾기

	// 함수를 이용하게 되면 타입이 다르기 때문에 해당하는 타입으로 다시 만들어야 한다. 
	vector<int> temp;
	for (int i = 0; data.size(); i++)
	{
		temp.push_back(data[i].first);
	}

	LinearSearch(temp, 4);		// 값이 존재 한다면
	cout << "데이터가 존재한다 : (" << data[4].second << ")" << endl;

	/*
	* 1. 반환하는 값을 bool 타입으로 변경하기
	* 2. LinearSearch(vector<int> -> vector<pair<int, string>>으로 바꿔보기
	* 3. UserID를 사용해서 유저의 닉네임을 출력하는 코드 완성하기 
	*/
}

int main()
{
	cout << "배열을 이용한 선형 탐색" << endl;
	int arr[5] = { 44, 37, 2, 23, 31 };
	LinearSearch(arr, 5, 31);

	cout << endl;

	cout << "벡터를 이용한 선형 탐색" << endl;
	vector<int> data = { 44, 37, 2, 23, 31 };
	//LinearSearch(data);

	cout << "배열을 이용한 재귀 함수 탐색" << endl;
	int arr2[5] = { 44, 37, 2, 23, 31 };
	LinearSearch(arr2, 5, 31);


	cout << "배열을 이용한 이진 탐색" << endl;
	//int arr2[5] = { 44, 37, 2, 23, 31 };
	int arr3[5] = { 2, 23, 31, 37, 44 };
	LinearSearch(arr3, 5, 2);

	cout << endl;
}