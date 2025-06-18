#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma region ���� ����
/*
* ���� : �ϴ� ������ ���ݾ� ������ 1���� ������ �� ���� �ٽ� ��ģ��?
*/

/*
* ������ �� = mergesort
* ��ġ�� �� = merge
*/

/*
* ����
* 
* ���� ����
* ���� : ���ĵǾ� �������� ����
* ���� : n�� ũ�Ⱑ ũ�� Ŭ���� ��ȿ����, 100�� ������ ����, ���ĵǾ� �ִ� ����(biased)�� ���� ��
* 
* �� ����
* ���� : ���������� ���� ����� (STL sort�� ���ǵǾ� ����), ��κ��� ��� n logn �ð��� ����
* ���� : worst case�� ��� O(n^2) �ð��� �ɸ�
* 
* ������ �� : sort pivot - �� ����, �˰���
* 
* ���� ����
* ���� : ��������� n logn �ð��� ���� (��, ������ �� �ð��� �������� ����)
* ���� : sorted ������ ���� �迭�� ����ϱ� ������ �߰����� �޸𸮸� ��� 
* 
* ���� ���� ���
* - algorithm ����� ���� sort( begin(), end())�� ����ϴ� ���� ����Ʈ
*/

void Merge(int arr[], int n, int left, int mid, int right)	// ��ġ�� �Լ�
{
	// ���ĵ� �����͸� ���� ������ �迭 ������ �����Ѵ�. (sorted array ���� �迭)
	//int sortedArray[] = { 0 };	// �迭 �ȿ� n�� ����� �� ���⿡ ����Ϸ��� const�� ����ؾ��� -> ��������
	vector<int> sorted;		// ���� �������� ���Ѵ��� ���Ľ�Ų ���� ������ �ӽ� �����̳�
	sorted.assign(n, 0);
	int i = left;			// ���ʿ��� �����ϴ� �ε��� ��ȣ
	int j = mid + 1;			// �����ʿ��� �����ϴ� �ε��� ��ȣ
	int k = left;			// ���ĵ� �ε������� ���� ù��° �ε��� ��ȣ

	// 2. arr �迭 �ȿ� ����ִ� left �ε��� ���� right �ε��� ���� ���ϰ� ���� ���� sorted�� �ֱ�
	// left ���� ���, right ū ���


	while (i <= mid && j <= right)		// ���� �Ǵ� ������ �ε����� �������� ���� ����
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

	// 3. i�� ������ ��, j�� ������ �� �������� ä���
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

	// 4. sorted ���� ���ĵ� �����̰� arr ���� �����Ϳ� ���ĵ� �����͸� �Ű��ش�.
	for (int t = left; t <= right; t++)
	{
		arr[t] = sorted[t];
	}
}

void MergeSort(int arr[], int n, int left, int right)
{
	// ��������� mergesort

	// ���ʺκ� mergesort
	// �����ʺκ� mergesort

	// merge
	if (left < right)	// ���� left, right�� ���ٸ� ���Ұ� 1���̴�. 
	{
		int mid = (left + right) / 2;
		MergeSort(arr, n, left, mid);		// ������ �ٽ� 2���� �����Ѵ�?
		MergeSort(arr, n, mid + 1, right);	// ������ ���� 

		Merge(arr, n, left, mid, right);
	}
}

void Merge(vector<int> nums, int n, int left, int right)	// ���ͷ� ���� �����ؾ����� 
{

}
#pragma endregion