/*
* �ۼ���	: 2025-06-13
* �ۼ���	: ��ȿ��
* ����	: �⺻ ����
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
* nums �迭���� �׽�Ʈ ���̽��� ���´�.
* nums vector�� 1,3, 8,2,9 �� ������ ������ ���� �� ���ڸ� ������������ �����ϰ�, ������ ���� answer�� �����ؼ� ��ȯ�ض�.
*/

/*
* �ڵ带 ���� �� �ִٴ� �� �� ���� �˰��� �ڵ尡 �����Ѵٴ� ���̴�.
* �ð� ���⵵, ���� ���⵵
* �ּ��� ����� �ڵ尡 ������ ������ ���� ����ϴ� �ڵ��̴�.
*
* �ð��� ������ ������ �����ϰ� �ð��� ������ ������ �������� �ʴ�.
*/

/*
* �ð� ���⵵
* Big O ǥ���
*				O(1)		O(log n)		O(n)		O(n^2)
* n�� ũ��		1			10				100			1000	1000,000
* O(1)			1			1				1			1		1
* O(log n)		0			1				2			3		6
* O(n)			1			10				100			1000	1000,000
* O(n^2)		1
*
* ���� : ��κ��� �˰��� ������ �׽�Ʈ ���̽��� ������ ���� ��츦 �����Ѵ�.
*/

/*
* �ð� ���⵵�ε� �� ���� �ð��� ���ϴ� �� �ƴ� ���� Ƚ���� ���ϴ°�?
* - ȯ�濡 ���� ������� �޶�����.
* - ���� Ƚ���� ������ ����� ���� ū ������ �񱳸� �Ѵ�.
* - O(n)
*/
#pragma region �ð� ���⵵ ����ϱ�

void Test1()
{
	// 1���� 5���� ���� ���� �� ����ϱ�
	// int sum, for�� �Ἥ sum�� �����ϱ�

	int sum = 0;		// int Ÿ�Կ� sum�� �� 0�� �Ҵ��Ѵ�.

	int n = 0;
	cin >> n;

	for (int i = 1; i <= 5; i++)
	{
		sum += i;		// 5�� ����
	}

	// �ڵ� ���� Ƚ�� : n + 3

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sum += i * j;	// n * n ����
		}
	}

	// �ڵ� ���� Ƚ�� : (n * n) + n + 3 
}
#pragma endregion


// ���͸� �̿��� ����
vector<int> solution(vector<int> nums)
{
	vector<int> answer;
	sort(nums.begin(), nums.end());		// STL�� �����Ǿ� �ִ� ���� ��� 
	answer = nums;
	return answer;
}

// ���ĵǾ� ���� ���� ���ڸ� �迭�� �޾ƿͼ� ���ڸ� �����ϴ� �Լ��� �����

// ����, ����, ���� ����

#pragma region ���� ���� -> �ð� ���⵵ = n^2
// �ð� ���⵵ = n^2
// ������ ���������� �ð��� ���� �ɸ���. 
// vector<int> nums = { 1,5,3,4,2 };
void BubbleSort(int arr[], int n)		// ����
{
	/*
	* ���� : ����Ŭ�� �� �� ���ƾ� �ϴ���, ����Ŭ���� �� �ؾ� �ϴ���, for ����ϳ�?
	* 1. �迭 ��ҳ��� ���Ѵ�.
	* 2. (k��°) (k+1) ���ؼ� ū ��� �迭 ��Ҹ� �����Ѵ�.
	*/


	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])	// ���� ���Ұ� �ٷ� ���� ������ ũ�� ���� �����Ѵ�.
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

// �ð� ���⵵ : O(n^2)
// � ��Ȳ������ ���� �ּ�, �־�, ������� ������.

/*
* ���� ���� : �ּ� - O(n), �־� - O(n^2), ��� - O(n^2)
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

#pragma region ���� ����
// ���� ���� ���� �����ϰ� ���� ������ ������ ������� �����Ѵ�.
// ���� ���� : �ּ� - O(n), �־� - O(n^2), ��� - O(n^2)
// ����Ŭ ���� ���� ���� ���� ����� ��ġ�� ã�ƾ� �Ѵ�.

void Selectionsort(int arr[], int n)
{
	// �� ���� ����Ŭ�� ���ƾ� �ϴ���
	for (int i = 0; i < n - 1; i++)
	{
		int min_idx = i;
	// arr[j]�� ���� ���� ���� ��(Index) arr[min]
		for (int j = i + 1; j < n; j++)	// �� �ʿ䰡 �����ʳ�? �� �����ϳ� -> �� �ʿ� ���� �� ����
		{
			if (arr[min_idx] > arr[j])	// min_idx�� j�� ���ؼ� ������ �� ���� �ּڰ�
			{
				min_idx = j;
			}
		}

		if (i != min_idx)	// �� ���� ���ؼ� ���� ������ �����Ѵ�.
		{
			swap(arr[i], arr[min_idx]);
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << n << endl;
	}

	// arr[��] arr[min]


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

#pragma region ���� ����

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
	cout << "���� ���� ����" << endl;
	int arr[6] = { 2,6,1,3,7,4 };
	BubbleSort(arr, 6);

	cout << "���� ���� ����2" << endl;
	vector<int> nums = { 1,5,3,4,2 };
	BubbleSort(nums);

	cout << "���� ���� ����" << endl;
	int arr2[6] = { 2,6,1,3,7,4 };
	Selectionsort(arr2, 6);
}