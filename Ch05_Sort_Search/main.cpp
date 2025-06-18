/*
* �ۼ���	: 2025-06-18
* ����	: Ž���� ���� Ž��
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

/*
* ����
* ������ �پ��� ������� ���� ������
* ������ �ؾ��ϴ� ����
* ���ο� �������� �����̳ʿ� �߰��� �� ���ĵ� ���·� ���� ��찡 ����
*/

/*
* Ž�� : �����̳� �ȿ� �����Ͱ� �ִ��� ������ ã�´�.
* Ž���� ���α׷��� �ڵ�� �����غ���.
*
* 1. �տ������� �����͸� ���Ͽ� �ִ��� ������ Ȯ���ϴ� �ڵ� ����� - ����(����?) Ž��
* 2. ���� Ž��(binary Search)
* - �����̳ʰ� ���ĵǾ� ���� �� �߾� ���� �������� �����͸� ����� ã�� ���
*/

#pragma region ���� Ž��
/*
* ���� Ž���� ��� �ּ��� ����� �� O(1), �־��� ����� �� n�� �ð��� �ɸ���.
* ��� �ð� : O(n)
* ������ ������ 100���� �Ѿ�� ��ȿ�����̴�. (������ ������ ������ ��������)
*
* ���� ���� �˰��� : ������ ������ ���� ������ �ذ��ϴ� ������� ������ �ذ��Ѵ�.
*/
void LinearSearch(int arr[], int n, int target)	// target�� ã���� �ϴ� ������
{
	// ��ü ������ �ݺ��ؼ� (for��)
	for (int i = 0; i < n; i++)
	{
		// target�� ���� �����Ͱ� �����ϸ� (if��)
		if (target == arr[i])
		{
			cout << "�ش��ϴ� ������ : " << target << "��(��) ã�Ҵ�." << endl;
			return;
		}
	}
	cout << "�����͸� ã�� ���ߴ�." <<  endl;

}

// ���� ���ͷ� ������ ���ϴ� ������ nums�� �����ϰ� ���� for���ȿ� �Ϲ� nums�� ������� nums.�Լ�()�� ����ϴ��� �׷��� �򰥸��°� ������ �ɵ����ϴϱ� ����ϳ� ������
// �̰� �ƴѰ� ������ 
void LinearSearch(vector<int>& nums, int arr[], int target)		// ���� Ž���� ���ͷε� �����ϱ� 
{
	int n = nums.size();

	for (int i = 0; i < nums.size(); i++)
	{
		if (target == arr[i])
		{
			cout << "�ش��ϴ� ������ : " << nums.size() << "��(��) ã�Ҵ�." << endl;
			return;
		}
	}
	cout << "�����͸� ã�� ���ߴ�" << endl;
	
}


#pragma endregion

#pragma region ���� Ž��
/*
* iterator ������� ������ ���� Ž��
*
*/ 
void BinarySearch(int arr[], int n, int target)
{
	// int mid = (left + right) / 2;			20�� + 20�� =  ������ �ɼ��� ����
	// int mid = left + (right - left) / 2;		���ʰ� �����ʰŸ��� /2 �ϰ� ���Ѵ�.
	int i = 0;		// ����
	int j = n - 1;	// ������
	while (i <= j)	// ������ �����ʺ��� �۰ų� ���� ��
	{
		int mid = i + (j - i) / 2;		// ������ �� ������ �����͸� ã�� �� ���� �߾Ӱ��� �������ش�. 
		// mid�� target�� ���ϱ�
		
		// target�� ã�� ���
		if (arr[mid] == target)
		{
			cout << "�ش��ϴ� ������ : " << target << "��(��) ã�Ҵ�." << endl;
			return;
		}
		// target�� ���� ���	���ʿ��� �ٽ� ã��
		else if (arr[mid] > target)
		{
			//mid�� �������� j �ٲٱ�
			j = mid - 1;
		}
		// target�� ū ���
		else	// (arr[mid] < target)
		{
			// ���� i�� mid�� �������� ��� �ٲ�� ���� 
			i = mid + 1;
		}
	}
}

void BinarySearchRecursive(int arr[], int n, int target, int left, int right)		// ����Լ��� ����� ����Ǯ�� 
{
	// ��� �Լ��� Ż���� �� �ִ� ���� �����
	// left = ����, right = ������
	if (left > right)		// ������ �����ʺ��� ũ��
	{
		cout << "�����͸� ã�� ���ߴ�." << endl;
		return;				// ��ȯ�Ѵ�. 
	}
	int mid = (left + right) / 2;
	if (arr[mid] == target)
	{
		cout<< "�ش��ϴ� ������ : " << target << "��(��) ã�Ҵ�." << endl;
		return;
	}
	else if (arr[mid] > target)	// �߾Ӱ��� target���� ũ��  ����(right = mid - 1)
	{
		BinarySearchRecursive(arr, n, target, left, mid - 1);
	}
	else	// ������(left = mid + 1)
	{
		BinarySearchRecursive(arr, n, target, mid + 1, right);
	}
	// �ڱ� �ڽ� �Լ��� ȣ���ϱ�
}

// ���� ���ͷ� ������ ���ϴ� ������ nums�� �����ϰ� ���� for���ȿ� �Ϲ� nums�� ������� nums.�Լ�()�� ����ϴ��� �׷��� �򰥸��°� ������ �ɵ����ϴϱ� ����ϳ� ������
void BinarySearch(vector<int> nums, int n, int target, int left, int right)		// ���ͷ� �����ϱ� 
{
	int i = 0;		// ����
	int j = n - 1;	// ������
	while (i <= j)	// ������ �����ʺ��� �۰ų� ���� ��
	{
		int mid = i + (j - i) / 2;		// ������ �� ������ �����͸� ã�� �� ���� �߾Ӱ��� �������ش�. 
		// mid�� target�� ���ϱ�

		// target�� ã�� ���
		if (nums[mid] == target)
		{
			cout << "�ش��ϴ� ������ : " << target << "��(��) ã�Ҵ�." << endl;
			return;
		}
		// target�� ���� ���	���ʿ��� �ٽ� ã��
		else if (nums[mid] > target)
		{
			//mid�� �������� j �ٲٱ�
			j = mid - 1;
		}
		// target�� ū ���
		else	// (arr[mid] < target)
		{
			// ���� i�� mid�� �������� ��� �ٲ�� ���� 
			i = mid + 1;
		}
	}
}
#pragma endregion

/*
* pair<int, Ŭ�����̸�>
* 
* vector<pair<int, string>> data;
* pair Ÿ�� ���� ���
* pair.push_back({0, "AAA"});
* �ش��ϴ� �ε����� ������ �� �ε����� ����Ǿ� �ִ� ���ڸ� ����ϴ� �ڵ� �����
* 
* ������ ID�� ������ ���� ������ �����ϰ� ������������ ID�� �������� �ش� ������ ����(�г���)�� �˻��ϴ� ��� �����ϱ�
*/

// pair�� ���� ����� ������ ��
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
	// pair :  ������ �ϳ��� ǥ���ϴ� ���
	// key, value ���� �����ؼ� �����ϴ� ��� 
	// ������ �����ε�, Ŭ������ ���ϴ� ������ 
	vector<pair<int, string>> data;

	data.push_back({ 1, "AAA" });
	data.push_back({ 2, "BBB" });
	data.push_back({ 3, "CCC" });
	data.push_back({ 4, "DDD" });
	data.push_back({ 5, "EEE" });

	make_pair(1, "AAA");

	// ���� Ž�� �Ǵ� ���� Ž���� �̿��Ͽ� ����� ã��

	// �Լ��� �̿��ϰ� �Ǹ� Ÿ���� �ٸ��� ������ �ش��ϴ� Ÿ������ �ٽ� ������ �Ѵ�. 
	vector<int> temp;
	for (int i = 0; data.size(); i++)
	{
		temp.push_back(data[i].first);
	}

	LinearSearch(temp, 4);		// ���� ���� �Ѵٸ�
	cout << "�����Ͱ� �����Ѵ� : (" << data[4].second << ")" << endl;

	/*
	* 1. ��ȯ�ϴ� ���� bool Ÿ������ �����ϱ�
	* 2. LinearSearch(vector<int> -> vector<pair<int, string>>���� �ٲ㺸��
	* 3. UserID�� ����ؼ� ������ �г����� ����ϴ� �ڵ� �ϼ��ϱ� 
	*/
}

int main()
{
	cout << "�迭�� �̿��� ���� Ž��" << endl;
	int arr[5] = { 44, 37, 2, 23, 31 };
	LinearSearch(arr, 5, 31);

	cout << endl;

	cout << "���͸� �̿��� ���� Ž��" << endl;
	vector<int> data = { 44, 37, 2, 23, 31 };
	//LinearSearch(data);

	cout << "�迭�� �̿��� ��� �Լ� Ž��" << endl;
	int arr2[5] = { 44, 37, 2, 23, 31 };
	LinearSearch(arr2, 5, 31);


	cout << "�迭�� �̿��� ���� Ž��" << endl;
	//int arr2[5] = { 44, 37, 2, 23, 31 };
	int arr3[5] = { 2, 23, 31, 37, 44 };
	LinearSearch(arr3, 5, 2);

	cout << endl;
}