/*
* �ۼ���	: 2025-06-16
* �ۼ���	: ��ȿ��
* ����	: ���� ���İ� �� ����
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#pragma region ���� ����(Insert Sort)
/*
* Ư�� ���� ���ĵ� ��ġ�� �ű�� ���
* �տ������� �����͸� �����Ѵ�.
* log n��ŭ 
* ex. 3 5 1 7 2 9 4
*
* ���� 
* - ������ �Ǿ��ִٸ� ���� �ʾƵ� �ȴ�.
* - Ư�� �����϶��� swap�� �����Ѵ�. (while ���ǿ� �ش��� ���� swap�� �߻��Ѵ�.) �񱳸� �ϰ� ���� ���� ���̸� �׶� swap�Ѵ�?
* - �����̳� �����Ͱ� ���ĵǾ� �֤������� ���� �ӵ��� ������.
* ����Ŭ : n
* �ּ��� ��� O(n) ���, �־��� ���(O(N^2))
* 
* ����
* ���� �Ǿ� ���� ���� ��� n�� ������ ����ϱ� ������ �ð��� �ɸ���. 
*/

/*
* log �ð��� �󸶳� ������
* 2^10 = 1024		// �� 1000
* 2^10 * 2^10		// 1,000,000
* log292^20) = 20;	// n��(�鸸 ��), log n��(20��) log n�� ������.
* 
* �ð��� �����ϱ� ���ؼ� log n���� ǥ���ϴ� ����� ã�´�.
* logn = "���� ����" �˰���
* 
*/

/*

*/
void InsertSort(int arr[], int n)
{
	// ����Ŭ�� ��� ���ƾ� �ϴ���
	for (int i = 1; i < n; i++)
	{
		// ���� key ���� ��������
		int key = arr[i];

		// key���� ���� ������ ���ؾ���
		int j = i - 1;

		// while() ���� ������ true�϶� �߰�ȣ�� �����Ѵ�.
		while (j >= 0 && arr[j] > key)	// j�� ����ִ� ������ key ������ ���� ��, �ε��� ���� 0���� Ŭ�� swap
		{
			arr[j + 1] = arr[j];		// ������ �����Ϳ� ���� ���� �������� ��ġ�� �ٲ۴�.
			j--;						// ���� Ű�� ��ġ
		}

		arr[j + 1] = key;
	}
}

void InsertSort(vector<int>& nums)
{
	// ����Ŭ�� ��� ���ƾ� �ϴ���	
	int n = nums.size();

	for (int i = 0; i < n; i++)
	{
		// ���� Ű ���� ����
		int key = nums[i];

		int j = i - 1;
		// Ű ���ʿ� �ִ� ��� �����͵�� ���ؼ� ��ġ�� ã�� ���� �� ��ġ�� �ִ´�.

		while (j >= 0 && nums[j] > key)		// j�� ���� 0���� ũ�ų� ������, key ���� ���ʺ��� ���� ������
		{
			nums[j + 1] = nums[j];
			j--;
			// ������ �����̶� Ű ���� �ٲٰ� 
		}
		nums[j + 1] = key;
	}
}
#pragma endregion

#pragma region �� ����(Quick Sort)
/*
* Ư¡
* ������ �Ǻ��� ���Ѵ�.	���� ������ ���� �Ǻ����� �Ѵ�. 
* pivot(�Ǻ�) : ������
* ���� ���� �˰��򿡼� ������ �ϱ� ���� �����̴�. 
* 
* ��� O(n *log n) �ð��� ���´�.
* O(n^) ���� ������� �˰����� ���϶�(����, ����, ����)
* 
* �Ǻ��� �������� ���� ������ ���� swap�Ѵ�.
* ���ʰ� : �Ǻ� ������ ū ���� ã�ƶ�.
* ������ ��: �Ǻ� ������ ���� ���� ã�ƶ�.
* 
* 
* ����
* - 
* 
* ���� ����ϴ���
* - data�� ������ 10������ �Ѿ �� ex. 10�� x 10�� ~ ����
* - �������� ������ ���� �� ���ȴ�.
*
* ���� : ������ �Ǿ� �ִ� �����Ϳ��� �� ������ ����Ұ�� O(n^2)�� �ð��� �ɸ���.
*/

void QuickSort(int data[], int start, int end)		// ����Լ��� ����. ���۰� ���� ������� �Ѵ�. 
{
	if (start >= end)		// �����Ͱ� �ϳ��� ���� ��, ��� �Լ��� ������ ���� ������ return���� ǥ���Ѵ�.
	{
		return;
	}

	int pivot = start;		// ������ �Ǵ� ��
	int i = start + 1;		// ���ʿ��� ������ ��ġ
	int j = end;			// �����ʿ��� ���� �� ��ġ
	int temp;				// swap�� ���� �����ϱ� ���� �ӽ� ����

	while (i <= j)			// ���� �ε����� ������ �ε����� �߿����� ������ �ݺ��Ѵ�.
	{
		while (data[i] <= data[pivot]) // �Ǻ����� ū ���� ���� �� (i�� ���� �������ִ� �ڵ�), (������ i�� ��� �����϶�� �ǹ�)
		{
			i++;
		}

		while (j < start && data[j] >= data[pivot]) // �Ǻ����� ���� ���� ���� �� (j�� ���� �������ִ� �ڵ�) (Ŭ�� i�� �����϶�� �ǹ�) j�� start���� ���� Ŀ���Ѵ�.
		{
			j--;
		}
		
		// i > j // ���� ���� ������ ������ ũ�� �����ȴ�.
		if (i < j)	// �������� 
		{
			/*temp = data[j];
			data[j] = data[pivot];
			data[pivot] = temp;*/

			swap(data[j], data[pivot]);;
		}
		// �������� ���� �� (j�� i�� ����)
		else
		{
			/*temp = data[j];
			data[j] = data[i];
			data[i] = temp;*/

			swap(data[i], data[j]);;
		}

		// ��� �Լ�

		// QuickSort(���� ��Ʈ) QuickSort(������ ��Ʈ)

		QuickSort(data, start, j - 1);	// ����
		QuickSort(data, i + 1, end);	// ������
		
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
* ���� ���� - ���� �ִ� ���Ҹ� ���ؼ� ũ�� ���������� ������
* ���� ���� - ���� ���� ���� �������� ������.
*/

int main()
{
	cout << "���� ���� �迭 ����" << endl;
	int arr1[10] = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };

	InsertSort(arr1, 10);

	for (int i = 0; i < 10; i++)
	{
		cout << " " << arr1[i];
	}

	cout << endl;
	cout << endl;

	cout << "���� ���� ���� ����" << endl;
	vector<int> nums1 = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };

	InsertSort(nums1);

	for (int num : nums1)
	{
		cout << " " << num;
	}

	cout << endl;
	cout << endl;

	cout << "�� ���� �迭 ����" << endl;
	int arr2[10] = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };
	QuickSort(arr2, 1, 10);

	for (int i = 0; i < 10; i++)
	{
		cout << " " << arr2[i];
	}
	

	cout << endl;
	cout << endl;

	/*cout << "�� ���� ���� ����" << endl;
	vector<int> nums2 = { 3, 6, 9, 1, 7, 5, 8, 4, 10, 2 };

	QuickSort(nums1, 0, nums2.size()-1);

	for (int num : nums2)
	{
		cout << " " << num;
	}*/
}