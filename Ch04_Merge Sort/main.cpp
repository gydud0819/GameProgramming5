/*
* �ۼ���	: 2025-06-17
* ����	: ���� ����
*/
#include "Merge.h"

// sorted 4������ right ������ŭ arr���� �����ϴ� �ڵ� ����� �ϼ��ϱ�

int main()
{
	cout << "���� ���� ����" << endl;
	int arr[6] = { 5,3,1,6,9,8 };
	MergeSort(arr, 6, 0, 5);
	for (int i = 0; i < 6; i++)
	{
		cout << arr[i] << " ";
	}

	cout << endl;
	cout << endl;

	cout << "���� ���� ���� ����" << endl;
}