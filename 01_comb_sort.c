#include <stdio.h>
#include <stdlib.h>

int comb_sort(int *array, int size)
{
    int step = size - 1, c, operation = 0;
    while (step >= 1)
    {
        for (int i = 0; i < size - step; i++)
        {   
            operation++;
            if (array[i] > array[i + step])
            {  
                c = array[i];
                array[i] = array[i + step];
                array[i + step] = c;
                operation++;
            }
        }
        step /= 1.24733;
    }

    return operation;
}

int main()
{
    int n, i, operation  = 0;
    scanf("%d", &n);

    int *arr = (int*)malloc(sizeof(int)*n);

    for (i = 0; i < n; i++)
        scanf("%d",&arr[i]);

    operation += comb_sort(arr, n);

    for (i = 0; i < n; i++)
		printf("%d ", arr[i]);

	printf("\n");
    printf("%d\n", operation);
    free(arr);

    return 0;
}