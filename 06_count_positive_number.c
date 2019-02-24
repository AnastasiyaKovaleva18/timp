#include <stdio.h>

int main(void)
{
	int N, t, count;
	scanf("%d", &N);
	count = 0;

	for(int i = 0; i < N; i++) 
	{
		scanf("%d", &t);
		if (t > 0) count++;	
	}

	printf("%d\n", count);

	return 0;
}