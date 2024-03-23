#include <iostream>
#include <sys/time.h>
using namespace std;

const int N = 5000;
int b[N][N];
int a[N], sum[N];

void init(int b[N][N], int a[N], int sum[N])
{
	//ʹ��ѭ��չ����������ѭ��������ʱ���Ӱ��
	for (int i = 0; i < N; i += 2)
	{
		a[i] = i;
		a[i + 1] = i + 1;
		sum[i] = 0;
		sum[i + 1] = 0;
	}
	for (int i = 0; i < N; i += 2)
	{
		for (int j = 0; j < N; j += 2)
		{
			b[i][j] = i + j;
			b[i][j + 1] = i + j + 1;
			b[i + 1][j] = i + j + 1;
			b[i + 1][j + 1] = i + j + 2;
		}
	}
}
//ƽ���㷨�����з��ʶ�ά����b���������ռ���ʣ�
//���ѭ��������ѭ��չ����Ϊ�˺��Ż�����㷨��Ӧ
void normal_inner_product(int b[N][N], int a[N], int sum[N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j += 2)
		{
			sum[i] += a[j] * b[j][i];
			sum[i] += a[j + 1] * b[j + 1][i];
			//sum[i + 1] += a[j] * b[j][i + 1];
			//sum[i + 1] += a[j + 1] * b[j + 1][i + 1];
		}
	}
}
//cache�Ż��㷨�����з��ʶ�ά����b�������ռ���ʣ�
//��һ��ѭ��������ѭ��չ������Ϊ�����i+=2�򲢲�����ȫ��cache�Ż����ڲ�ѭ��ע�͵��Ĵ�������룬���ⲿ�ֻ��ǿ��з���Ч�ʵ�
void cache_inner_product(int b[N][N], int a[N], int sum[N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j += 2)
		{
			sum[j] += a[i] * b[i][j];
			//sum[j] += a[i + 1] * b[i + 1][j];
			sum[j + 1] += a[i] * b[i][j + 1];
			//sum[j + 1] += a[i + 1] * b[i + 1][j + 1];
		}
	}
}
int main()
{
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	init(b, a, sum);
	gettimeofday(&start, NULL);
	normal_inner_product(b, a, sum);
	//cache_inner_product(b, a, sum);
	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	cout << timer << endl;
	//print(sum);
}