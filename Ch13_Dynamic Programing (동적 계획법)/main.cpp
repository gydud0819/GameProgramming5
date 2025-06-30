/*
* Dynamic Programing (���� ��ȹ��)
* �ڷ���, Ŭ����(�Լ�), ������, �ڷᱸ��
* 
* �˰��� ����, �ڵ带 �ۼ��ϴ� �ɷ��� ���ϱ� ���� ����
* ���α׷��� ������ �� ������ �ִ��� (���� �Ƿ�)
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
* �˰��� ���� ����
* ����, Ž��, Ʈ�� ��ȸ, �׷��� ��ȸ, Ž��(DFS, BFS)
* ������ȹ��, �׸��� �˰���, ���� Ž��
* ������ Ǫ�� �ذ� ���̵� �������� ������ ��
*/

/*
* DP ����
* - ���������� ��ȹ�� �����.
* - �ߺ��Ǵ� ������ �� ���� ����ؼ� �ذ��ϰ� ���� ��
* - �޸𸮿� ����� �ؼ� ����ϰڴ�.
* - 
*/

/*
* �Ǻ���ġ ���� ����
* 1, 2, 3, 5, 8, 13 .. -> �Լ��� ǥ���ϱ�
*/ 

int Fibonacci(int n)
{
	if(n==1)
		return 1;

	if (n == 2)
		return 2;

	// �ݺ��� �Ǵ� ����Լ��� ǥ���� �� ���� 
	return Fibonacci(n - 1) + Fibonacci(n - 2);
	
}

/*
* ��� ����� �Ǻ���ġ ������ �ð��� ���� �ɸ��� ����
* n�� ���ڰ� Ŀ���� Ŀ������ Fibonacci �Լ��� ��� ����ȴ�.
* ��� �Լ��� ����ϰ� n�� Ŀ���� Ŀ������ ���ÿ� �޸𸮰� ���δ�. => ���� ���� �÷ο� �߻�
* �ߺ��� �߻��ϴ� ������ �ذ��ϱ� ���� �޸� ������ Ȯ���ؼ� �����صξ��ٰ� ����Ѵ� (�޸������̼�) �޸����̼�?
*/

/*
* ������ȹ���� ���� ���
* Top - down ��� :	��� ���, �����̳� ����
* bottom - Up : �ݺ��� �����̳� ����
*/
int FinoDP(int n)		// bottom - up (�ݺ���, �����̳�)
{
	if (n <= 1) { return n; }
	
	//vector<int> vec;

	// �ӽ� ������ �����̳� �����
	vector<int> dp(n + 1, 0);	// �����ڷ� ǥ��, n���� �� ������ �ִ� �迭�� ���� �����Ѵ�.

	// bottom - up dp[n]���� �����ϱ� ���ؼ� dp[0] ~ dp[n]�� ä�������� ��
	dp[0] = 0;
	dp[1] = 1;
	//dp[2] = 2;

	for (int i = 2; i <= n; i++)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}

class FiboRecursive
{
private:
	vector<int> dp;

public:
	FiboRecursive(int n)
	{
		dp.resize(n + 1, -1);
		dp[0] = 0;                                                                                                                                                                                                                                                                                                                                                                                                                                             
		dp[1] = 1;                                                                                                                                                                                                                                                                                                                                                                                                                                             
	}

	int FiboRecur(int n)
	{
		// dp�� ���� �̹� ���� �Ѵٸ�, -1�� �ƴϸ� 
		// ����Լ� return ����, �Ʒ��� �ڱ��ڽ� �Լ��� �����Ѵ�.
		if (dp[n] != -1)
		{
			return dp[n];
		}
			dp[n] = FiboRecur(n - 1) + FiboRecur(n - 2);
			
			return dp[n];
	}
};

/*
* ��� ������ ����
* 
* �� ����� �����ų� 2�� �� �ѹ��� �����ų� �ΰ��� ������� ����� ���� �� �մ�
* ������� 3��° ����� �ö󰡱� ���ؼ� 2���� ����� ���� (n>1) 
* �̶� ���� �ּ����� ������� n�� ����� ������ ��� �����ϱ� 
* �ٽ� ���̵�� : n��° ����� �ּ������� �ö�� �Ѵ�. 1ĭ�� ���� �� vs 2ĭ�� ���� �� ���� �� �־�� �Ѵ�.
* 

*/

/*
* ����� ������ ����� ��
* �ι�° ����� ���������� ��� : ��ĭ�� ������ vs ��ĭ �ѹ����ö󰣴�.		
* CountStep(1)=1;
* CountStep(2)=2;
*/

/*
* cashe : ĳ�� (�ӽ÷� ����� ������ ����) ����
* �ߺ��Ǵ� ������ ���� �� �����ͤ��� �����ؼ� ����ϸ� ������ ����� �� �ִ�.
* �޸� ������ ����ؾ� �Ѵ�. "ĳ��" : ����ȭ ��� �� �ϳ��̴�. (�ð��� Ȯ���� �� �ִ�)
*/

/*
* ���� ������ ������ DP�� �ذ��϶�� �����ʴ´�.
* ��� ������ �м��ϰ� �� ������ ���� ������ DP�� Ǯ��ߵǰڱ����ϰ� ������ �ؾ��Ѵ�.
* (1) �� ���丶�� Ű������� �����Ѵ�. -> �ּ�, �����ϰ�, ���� ������
* (2) ���⹮���� �����Ѵ�. (�������� Ǯ��� ��)
*/
class GaneCashe
{
private:
	unordered_map<int, int> exps;	// �ؽø� �̿��� �ڷᱸ��, Ž������ �ſ� ������. ���� ���� ����Ǵ� �����̳� 
	unordered_map<int, int> damages;	// ���ݷ�

	struct UserData
	{
		int level;
		int exps;
		int damage;
	};

public:
	int CalculateExp(int level)
	{
		// 5�������� �ʿ��� ����ġ
		if (exps.find(level) != exps.end())
		{
			cout << "ĳ�ÿ��� �����͸� ������" << "(���� " << level << " : " << exps[level] << ")" << endl;
			return exps[level];
		}

		// ���Ӵ� ���� �� �ʿ��� ����ġ�� ���ϴ� ������ �ʿ��ϴ�.

		int exp = level * (level + 100);	// 101, 204, 309 ��
		
		exps[level] = exp;
		return exp;
	}

	int CalculateDamage(int level)
	{
		if (damages.find(level) != damages.end())
		{
			cout << "ĳ�ÿ��� �����͸� ������" << "(���ݷ� " << level << " : " << damages[level] << ")" << endl;
			return damages[level];
		}

		int damage = level * 2;
		damages[level] = damage;

		return damage;
	}

};

int CountStep(int n)
{
	return n;
	vector<int> dp(n + 1, 0);		// n+1 �ϴ� ���� : dp[6] 0���� �������� �� 2��° �����͸� ����ؾ��Ѵ�.
	dp[0] = 0;
	dp[1] = 1;

	for (int i = 2;i <= n; i++)
	{
		dp[n] = dp[n - 1] + dp[n - 2];
	}
	return dp[n];
}

int main()
{
	cout << "�Ǻ���ġ ��� ���� ����" << endl;
	cout << "�Ǻ���ġ ��� �� : " << Fibonacci(6) <<endl;

	cout << "�Ǻ���ġ�� 25��° ���� ��� : " << Fibonacci(10) << endl;
	cout << endl;

	cout << "�Ǻ���ġ DP bottom up ��� ����" << endl;
	cout << "����� : " << FinoDP(6) << endl;

	cout << "�Ǻ���ġ DP Top down" << endl;

	FiboRecursive fibo(6);
	cout << "����� : " << fibo.FiboRecur(6) << endl;

	//cout << "��� ������ ����� �� ���" << endl;

	cout << "���� ĳ�� ������ ����" << endl;

	GaneCashe gamecashe;
	cout << "1���� ����ġ : " << gamecashe.CalculateExp(1) << endl;
	cout << "1���� ����ġ : " << gamecashe.CalculateExp(1) << endl;

	cout << endl;

	cout << "1�����϶� ������ : " << gamecashe.CalculateDamage(1) << endl;
	cout << "1�����϶� ������ : " << gamecashe.CalculateDamage(1) << endl;
	
	return 0;
}