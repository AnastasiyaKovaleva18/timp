#include <stdio.h>
#include <stdlib.h>

int shell_sort(int *array, int size)
{
    int i, j, step, operation = 0;
    int tmp;

    for (step = size / 2; step > 0; step /= 2) 
    {
    	for (i = step; i < size; i++)
        {
            tmp = array[i];
            for (j = i; j >= step; j -= step)
            {   
                operation++;
                if (tmp < array[j - step]) 
                {   
                    array[j] = array[j - step];
                    operation++;
                }
                else
                    break;
            }
            array[j] = tmp;
        }
    }
    return operation;
}

int main()
{
    int n, i, operation = 0;
    scanf("%d", &n);

    int *array = (int*)malloc(sizeof(int)*n);

    for (i = 0; i < n; i++)
        scanf("%d",&arr[i]);

    operation += shell_sort(array, n);

    for (i = 0; i < n; i++)
		printf("%d ", array[i]);

	printf("\n");
    printf("%d\n", operation);
    free(array);

    return 0;
}