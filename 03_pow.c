#include <stdio.h>
#include <math.h>

int main(void)
{
	int x, y;

	scanf("%d%d", &x, &y);

	if(pow(x, y) > 2147483647 || pow(x, y) < -2147483648) 
	{
		puts("Выход за диапазон");
	} 
	else 
		printf("%f\n", pow(x, y));

	return 0;
}