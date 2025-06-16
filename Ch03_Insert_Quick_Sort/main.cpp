/*
* 작성일	: 2025-06-16
* 작성자	: 박효영
* 주제	: 삽입 정렬과 퀵 정렬
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma region 삽입 정렬(Insert Sort)
/*
* 특정 수를 정렬된 위치로 옮기는 방식
* 앞에서부터 데이터를 정렬한다.
* log n만큼 
* ex. 3 5 1 7 2 9 4
*
* 장점 
* - 정렬이 되어있다면 하지 않아도 된다.
* - 특정 조건일때만 swap을 실행한다. (while 조건에 해당할 때만 swap이 발생한다.) 비교를 하고 가장 작은 값이면 그때 swap한다?
* - 컨테이너 데이터가 정렬되어 있ㅇ르수록 정렬 속도가 빠르다.
* 사이클 : n
* 최선의 경우 O(n) 평균, 최악의 경우(O(N^2))
* 
* 단점
* 정렬 되어 있지 않은 경우 n의 제곱에 비례하기 때문에 시간이 걸린다. 
*/

/*
* log 시간이 얼마나 빠른가
* 2^10 = 1024		// 약 1000
* 2^10 * 2^10		// 1,000,000
* log292^20) = 20;	// n번(백만 번), log n번(20번) log n이 빠르다.
* 
* 시간을 단축하기 위해선 log n으로 표현하는 방법을 찾는다.
* logn = "분할 정복" 알고리즘
* 
*/

/*

*/
void InsertSort(int arr[], int n)
{
	// 사이클이 몇번 돌아야 하는지
	for (int i = 1; i < n; i++)
	{
		// 현재 key 값이 무엇인지
		int key = arr[i];

		// key값과 이전 값들을 비교해야함
		int j = i - 1;

		// while() 에서 조건이 true일때 중괄호를 실행한다.
		while (j >= 0 && arr[j] > key)	// j에 들어있는 값보다 key 값보다 작을 때, 인덱스 값이 0보다 클때 swap
		{
			arr[j + 1] = arr[j];		// 왼쪽의 데이터와 새로 들어온 데이터의 위치를 바꾼다.
			j--;						// 현재 키의 위치
		}

		arr[j + 1] = key;
	}
}

void InsertSort(vector<int>& nums)
{
	// 사이클이 몇번 돌아야 하는지	
	int n = nums.size();

	for (int i = 0; i < n; i++)
	{
		// 현재 키 값이 뭔지
		int key = nums[i];

		int j = i - 1;
		// 키 왼쪽에 있는 모든 데이터들과 비교해서 위치를 찾은 다음 그 위치에 넣는다.

		while (j >= 0 && nums[j] > key)		// j의 값이 0보다 크거나 같을때, key 값이 왼쪽보다 값이 작을때
		{
			nums[j + 1] = nums[j];
			j--;
			// 작으면 왼쪽이랑 키 값을 바꾸고 
		}
		nums[j + 1] = key;
	}
}
#pragma endregion

#pragma region 퀵 정렬(Quick Sort)
/*
* 특징
* 임의의 피봇을 정한다.	가장 왼쪽의 값을 피봇으로 한다. 
* pivot(피봇) : 기준점
* 분할 정복 알고리즘에서 분할을 하기 위한 기준이다. 
* 
* 평균 O(n *log n) 시간을 갖는다.
* O(n^) 정렬 방식으로 알고리즘을 구하라(버블, 선택, 삽입)
* 
* 피봇을 기준으로 왼쪽 오른쪽 값을 swap한다.
* 왼쪽값 : 피봇 값보다 큰 값을 찾아라.
* 오른쪽 값: 피봇 값보다 작은 값을 찾아라.
* 
* 
* 장점
* - 
* 
* 언제 사용하는지
* - data의 갯수가 10만개가 넘어갈 때 ex. 10만 x 10만 ~ 몇백억
* - 데이터의 개수가 많을 때 사용된다.
*
* 단점 : 정렬이 되어 있는 데이터에서 퀵 정렬을 사용할경우 O(n^2)의 시간이 걸린다.
*/

void QuickSort(int data[], int start, int end)		// 재귀함수로 구현. 시작과 끝을 정해줘야 한다. 
{
	if (start >= end)		// 데이터가 하나만 있을 때, 재귀 함수를 끝내기 위한 조건을 return으로 표현한다.
	{
		return;
	}

	int pivot = start;		// 기준이 되는 값
	int i = start + 1;		// 왼쪽에서 변경할 위치
	int j = end;			// 오른쪽에서 변경 할 위치
	int temp;				// swap을 직접 구현하기 위한 임시 변수

	while (i <= j)			// 왼쪽 인덱스를 오른쪽 인덱스가 추월했을 때까지 반복한다.
	{
		while (data[i] <= data[pivot]) // 피봇보다 큰 값을 만날 때 (i의 값을 변경해주는 코드), (작을때 i를 계속 증가하라는 의미)
		{
			i++;
		}

		while (j < start && data[j] >= data[pivot]) // 피봇보다 작은 값을 만날 때 (j의 값을 변경해주는 코드) (클때 i를 감소하라는 의미) j는 start보다 값이 커야한다.
		{
			j--;
		}
		
		// i > j // 왼쪽 값이 오른쪽 값보다 크면 엇갈렸다.
		if (i < j)	// 엇갈리면 
		{
			/*temp = data[j];
			data[j] = data[pivot];
			data[pivot] = temp;*/

			swap(data[j], data[pivot]);;
		}
		// 엇갈리지 않을 때 (j와 i를 변경)
		else
		{
			/*temp = data[j];
			data[j] = data[i];
			data[i] = temp;*/

			swap(data[i], data[j]);;
		}

		// 재귀 함수

		// QuickSort(왼쪽 파트) QuickSort(오른쪽 파트)

		QuickSort(data, start, j - 1);	// 왼쪽
		QuickSort(data, i + 1, end);	// 오른쪽
		
	}
}

void QuickSort(vector<int>& nums, int start, int end)
{
	/*if (start >= end)
	{
		return;
	}

	int pivot = start;
	int i = start + 1;
	int j = end;

	while (i < j)
	{
		while()
	}*/
}
#pragma endregion


/*
* 버블 정렬 - 옆에 있는 원소를 비교해서 크면 오른쪽으로 보낸다
* 삽입 정렬 - 가장 작은 수를 왼쪽으로 보낸다.
*/

int main()
{
	cout << "삽입 정렬 배열 형식" << endl;
	int arr1[10] = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };

	InsertSort(arr1, 10);

	for (int i = 0; i < 10; i++)
	{
		cout << " " << arr1[i];
	}

	cout << endl;
	cout << endl;

	cout << "삽입 정렬 벡터 형식" << endl;
	vector<int> nums1 = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };

	InsertSort(nums1);

	for (int num : nums1)
	{
		cout << " " << num;
	}

	cout << endl;
	cout << endl;

	cout << "퀵 정렬 배열 형식" << endl;
	int arr2[10] = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };
	QuickSort(arr2, 1, 10);

	for (int i = 0; i < 10; i++)
	{
		cout << " " << arr2[i];
	}
	

	cout << endl;
	cout << endl;

	/*cout << "퀵 정렬 벡터 형식" << endl;
	vector<int> nums2 = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };

	QuickSort(nums1, 0, nums2.size()-1);

	for (int num : nums2)
	{
		cout << " " << num;
	}*/
}