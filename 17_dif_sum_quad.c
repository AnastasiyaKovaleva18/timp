#include <stdio.h>
#include <math.h>

int main(void)
{
	int N, t, sum;
	scanf("%d", &N);
	sum = 0;

	for(int i = 1; i <= N; i++) 
	{
		scanf("%d", &t);
		sum += pow((-1), i) * pow(t, 2);
	}

	printf("%d\n", sum);

	return 0;
}