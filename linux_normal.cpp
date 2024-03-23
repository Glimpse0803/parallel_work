#include <iostream>
#include <sys/time.h>
using namespace std;

const int N = 5000;
int b[N][N];
int a[N], sum[N];

void init(int b[N][N], int a[N], int sum[N])
{
	//使用循环展开技术降低循环操作对时间的影响
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
//平凡算法：按列访问二维数组b（不连续空间访问）
//外层循环不进行循环展开，为了和优化后的算法对应
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
//cache优化算法：按行访问二维数组b（连续空间访问）
//第一层循环不进行循环展开是因为如果用i+=2则并不算完全的cache优化，内层循环注释掉的代码需加入，但这部分还是跨行访问效率低
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