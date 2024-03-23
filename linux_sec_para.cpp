#include <iostream>
//#include <sys/time.h>
using namespace std;
long long N = 12;
void base_add(long long& sum)
{
	//循环展开
	for (long long i = 0; i < N; i += 2)
	{
		sum += i;
		sum += (i + 1);
	}
}
void parallel_add(long long& sum)
{
	long long sum1 = 0, sum2 = 0;
	//循环展开
	for (long long i = 0; i < N; i += 4)
	{
		sum1 += i;
		sum1 += i + 2;
		sum2 += (i + 1);
		sum2 += (i + 3);
	}
	sum = sum1 + sum2;
}
int main()
{
	long long sum = 0;
	struct timeval start;
	struct timeval end;
	unsigned long timer;
	gettimeofday(&start, NULL);
	//base_add(sum);
	parallel_add(sum);
	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	cout << timer << endl;
	cout << sum << endl;
}