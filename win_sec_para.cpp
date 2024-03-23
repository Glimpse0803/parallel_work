#include <iostream>
#include <Windows.h>
using namespace std;
long long N = 5000000;
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
	LARGE_INTEGER head, tail, freq;
	long long sum;
	// similar to CLOCKS_PER_SEC
	QueryPerformanceFrequency(&freq);
	// start time
	QueryPerformanceCounter(&head);
	//base_add(sum);
	parallel_add(sum);
	QueryPerformanceCounter(&tail);
	double timeOfSecond = (double)(tail.QuadPart - head.QuadPart) / (double)freq.QuadPart;
	double timeOfMicroSecond = (double)(tail.QuadPart - head.QuadPart) * 1e3 / (double)freq.QuadPart;
	cout << timeOfMicroSecond << endl;
}