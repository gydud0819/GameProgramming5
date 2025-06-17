/*
* 작성일	: 2025-06-17
* 주제	: 병합 정렬
*/
#include "Merge.h"

// sorted 4번으로 right 개수만큼 arr값에 복사하는 코드 만들어 완성하기

int main()
{
	cout << "병합 정렬 예시" << endl;
	int arr[6] = { 5,3,1,6,9,8 };
	MergeSort(arr, 6, 0, 5);
	for (int i = 0; i < 6; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
	cout << endl;

	cout << "병합 정렬 벡터 예시" << endl;
}