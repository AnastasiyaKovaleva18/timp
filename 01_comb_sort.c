#include <stdio.h>
#include <stdlib.h>

int comb_sort(int *array, int size)
{
    int step = size - 1, c;
    while (step >= 1)
    {
        for (int i = 0; i < size - step; i++)
        {
            if (array[i] > array[i + step])
            {
                c = array[i];
                array[i] = array[i + step];
                array[i + step] = c;
            }
        }
        step /= 1.24733;
    }

    return 0;
}

int main()
{
    int n, i;
    scanf("%d", &n);

    int *arr = (int*)malloc(sizeof(int)*n);

    for (i = 0; i < n; i++)
        scanf("%d",&arr[i]);

    comb_sort(arr, n);

    for (i = 0; i < n; i++)
		printf("%d ", arr[i]);

	printf("\n");

    return 0;
}