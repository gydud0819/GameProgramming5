#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma region 병합 정렬
/*
* 개념 : 일단 나누고 절반씩 나눠서 1개가 나눠진 것 끼리 다시 합친다?
*/

/*
* 나누는 것 = mergesort
* 합치는 것 = merge
*/

/*
* 정리
* 
* 삽입 정렬
* 장점 : 정렬되어 있을수록 빠름
* 단점 : n의 크기가 크면 클수록 비효율적, 100만 데이터 이하, 정렬되어 있는 편향(biased)이 있을 때
* 
* 퀵 정렬
* 장점 : 대중적으로 많이 사용함 (STL sort가 정의되어 있음), 대부분의 경우 n logn 시간을 보장
* 단점 : worst case일 경우 O(n^2) 시간이 걸림
* 
* 개선한 퀵 : sort pivot - 맨 왼쪽, 알고리즘
* 
* 병합 정렬
* 장점 : 평균적으로 n logn 시간을 보장 (단, 무조건 저 시간을 보장하진 않음)
* 단점 : sorted 저장을 위한 배열을 사용하기 때문에 추가적인 메모리를 사용 
* 
* 가장 좋은 방법
* - algorithm 헤더를 통해 sort( begin(), end())를 사용하는 것이 베스트
*/

void Merge(int arr[], int n, int left, int mid, int right)	// 합치는 함수
{
	// 정렬된 데이터를 따로 저장할 배열 공간을 정의한다. (sorted array 정렬 배열)
	//int sortedArray[] = { 0 };	// 배열 안에 n을 사용할 수 없기에 사용하려면 const를 사용해야함 -> 복잡해짐
	vector<int> sorted;		// 왼쪽 오른쪽을 비교한다음 정렬시킨 값을 저장할 임시 컨테이너
	sorted.assign(n, 0);
	int i = left;			// 왼쪽에서 시작하는 인덱스 번호
	int j = mid + 1;			// 오른쪽에서 시작하는 인덱스 번호
	int k = left;			// 정렬된 인덱스에서 가장 첫번째 인덱스 번호

	// 2. arr 배열 안에 들어있는 left 인덱스 값과 right 인덱스 값을 비교하고 작은 값을 sorted에 넣기
	// left 작은 경우, right 큰 경우


	while (i <= mid && j <= right)		// 왼쪽 또는 오른쪽 인덱스가 남아있을 때만 실행
	{
		if (arr[i] <= arr[j])
		{
			sorted[k++] = arr[i++];
		}
		else
		{
			sorted[k++] = arr[j++];
		}
	}

	// 3. i가 남았을 때, j가 남았을 때 나머지를 채우기
	if (i > mid)
	{
		for (int t = j; t <= right; t++)
		{
			sorted[k] = arr[t];
			k++;
		}
	}
	else
	{
		for (int t = i; t <= mid; t++)
		{
			sorted[k] = arr[t];
			k++;
		}
	}

	// 4. sorted 현재 정렬된 상태이고 arr 원본 데이터에 정렬된 데이터를 옮겨준다.
	for (int t = left; t <= right; t++)
	{
		arr[t] = sorted[t];
	}
}

void MergeSort(int arr[], int n, int left, int right)
{
	// 재귀적으로 mergesort

	// 왼쪽부분 mergesort
	// 오른쪽부분 mergesort

	// merge
	if (left < right)	// 만약 left, right가 같다면 원소가 1개이다. 
	{
		int mid = (left + right) / 2;
		MergeSort(arr, n, left, mid);		// 왼쪽을 다시 2개로 분할한다?
		MergeSort(arr, n, mid + 1, right);	// 오른쪽 분할 

		Merge(arr, n, left, mid, right);
	}
}

void Merge(vector<int> nums, int n, int left, int right)	// 벡터로 어케 구현해야하지 
{

}
#pragma endregion