/*
* 작성일	: 2025-06-13
* 작성자	: 박효영
* 주제	: 기본 정렬
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
* nums 배열에는 테스트 케이스가 들어온다.
* nums vector에 1,3, 8,2,9 등 랜덤한 정수가 들어올 때 숫자를 오름차순으로 정렬하고, 정렬한 값을 answer에 저장해서 반환해라.
*/

/*
* 코드를 평가할 수 있다는 건 더 좋은 알고리즘 코드가 존재한다는 것이다.
* 시간 복잡도, 공간 복잡도
* 최선의 방법은 코드가 빠르고 공간을 적게 사용하는 코드이다.
*
* 시간이 빠르면 공간이 복잡하고 시간이 느리면 공간이 복잡하지 않다.
*/

/*
* 시간 복잡도
* Big O 표기법
*				O(1)		O(log n)		O(n)		O(n^2)
* n의 크기		1			10				100			1000	1000,000
* O(1)			1			1				1			1		1
* O(log n)		0			1				2			3		6
* O(n)			1			10				100			1000	1000,000
* O(n^2)		1
*
* 정리 : 대부분의 알고리즘 문제는 테스트 케이스의 갯수가 많은 경우를 상정한다.
*/

/*
* 시간 복잡도인데 왜 실행 시간을 비교하는 게 아닌 실행 횟수를 비교하는가?
* - 환경에 따라 결과값이 달라진다.
* - 실행 횟수를 식으로 만들어 가장 큰 차수로 비교를 한다.
* - O(n)
*/
#pragma region 시간 복잡도 계산하기

void Test1()
{
	// 1부터 5까지 전부 더한 값 출력하기
	// int sum, for문 써서 sum에 저장하기

	int sum = 0;		// int 타입에 sum의 값 0을 할당한다.

	int n = 0;
	cin >> n;

	for (int i = 1; i <= 5; i++)
	{
		sum += i;		// 5번 실행
	}

	// 코드 실행 횟수 : n + 3

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sum += i * j;	// n * n 실행
		}
	}

	// 코드 실행 횟수 : (n * n) + n + 3 
}
#pragma endregion


// 벡터를 이용한 정렬
vector<int> solution(vector<int> nums)
{
	vector<int> answer;
	sort(nums.begin(), nums.end());		// STL에 구현되어 있는 정렬 사용 
	answer = nums;
	return answer;
}

// 정렬되어 있지 않은 숫자를 배열로 받아와서 숫자를 정렬하는 함수로 만들기

// 버블, 선택, 삽입 정렬

#pragma region 버블 정렬 -> 시간 복잡도 = n^2
// 시간 복잡도 = n^2
// 구현은 간단하지만 시간이 오래 걸린다. 
// vector<int> nums = { 1,5,3,4,2 };
void BubbleSort(int arr[], int n)		// 보류
{
	/*
	* 조건 : 사이클이 몇 번 돌아야 하는지, 사이클마다 뭘 해야 하는지, for 써야하나?
	* 1. 배열 요소끼리 비교한다.
	* 2. (k번째) (k+1) 비교해서 큰 경우 배열 요소를 변경한다.
	*/


	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])	// 왼쪽 원소가 바로 뒤의 값보다 크면 값을 변경한다.
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << endl;
	}

}

// 시간 복잡도 : O(n^2)
// 어떤 상황인지에 따라 최선, 최악, 평균으로 나뉜다.

/*
* 버블 정렬 : 최선 - O(n), 최악 - O(n^2), 평균 - O(n^2)
*/
void BubbleSort(vector<int> nums)		// 
{
	for (int i = 0; i < nums.size() - 1; i++)
	{
		for (int j = 0; j < nums.size() - i - 1; j++)
		{
			if (nums[j] > nums[j + 1])
			{
				swap(nums[j], nums[j + 1]);

			}
		}
	}

	for (int n : nums)
	{
		cout << n << endl;
	}
}
#pragma endregion

#pragma region 선택 정렬
// 가장 작은 수를 선택하고 제일 앞으로 보내는 방법으로 정렬한다.
// 선택 정렬 : 최선 - O(n), 최악 - O(n^2), 평균 - O(n^2)
// 사이클 마다 가장 작은 수가 저장된 위치를 찾아야 한다.

void Selectionsort(int arr[], int n)
{
	// 몇 번의 사이클이 돌아야 하는지
	for (int i = 0; i < n - 1; i++)
	{
		int min_idx = i;
	// arr[j]의 값과 가장 작은 값(Index) arr[min]
		for (int j = i + 1; j < n; j++)	// 뺄 필요가 없지않나? 또 빼야하나 -> 뺄 필요 없는 거 맞음
		{
			if (arr[min_idx] > arr[j])	// min_idx랑 j랑 비교해서 작으면 그 값이 최솟값
			{
				min_idx = j;
			}
		}

		if (i != min_idx)	// 두 값을 비교해서 같지 않으면 스왑한다.
		{
			swap(arr[i], arr[min_idx]);
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << n << endl;
	}

	// arr[값] arr[min]


}

void Selectionsort(vector<int> nums)
{
	for (int i = 0; i < nums.size() - 1; i++)
	{
		int j = i;
		for (int j = i + 1; j < nums.size();j++)
		{
			if (nums[j] > nums[i])
			{
				j = i;
			}
		}

		if (j != i)
		{
			swap(nums[i], nums[j]);
		}
	}

	/*for (int i = 0; i < length; i++)
	{

	}*/
}

#pragma endregion

#pragma region 삽입 정렬

#pragma endregion



void Execute()
{
	vector<int> nums = { 1,5,3,4,2 };

	auto v = solution(nums);

	for (auto& elem : v)
	{
		cout << elem << " ";
	}
}

int main()
{
	//Execute();
	cout << "버블 정렬 예시" << endl;
	int arr[6] = { 2,6,1,3,7,4 };
	BubbleSort(arr, 6);

	cout << "버블 정렬 예시2" << endl;
	vector<int> nums = { 1,5,3,4,2 };
	BubbleSort(nums);

	cout << "선택 정렬 예시" << endl;
	int arr2[6] = { 2,6,1,3,7,4 };
	Selectionsort(arr2, 6);
}