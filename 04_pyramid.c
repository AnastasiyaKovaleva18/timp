#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y)
{
    int m = *x;
    *x = *y;
    *y = m;
}

int pyramid_sort(int *array, int n)
{
    int b, s, i;

    while (1)
    {
        b = 0;
        for (i = 0; i < n; ++i)
        {
            if (i * 2 + 2 + s < n)
            {
                if (array[i + s] > array[i * 2 + 1 + s] || array[i + s] > array[i * 2 + 2 + s])
                {
                    if (array[i * 2 + 1 + s] < array[i * 2 + 2 + s])
                    {
                        swap(&array[i + s], &array[i * 2 + 1 + s]);
                        b = 1;
                    }
                    else if (array[i * 2 + 2 + s] < array[i * 2 + 1 + s])
                    {
                        swap(&array[i + s], &array[i * 2 + 2 + s]);
                        b = 1;
                    }
                }
            }
            else if (i * 2 + 1 + s < n)
            {
                if (array[i + s] > array[i * 2 + 1 + s])
                {
                    swap(&array[i + s], &array[i * 2 + 1 + s]);
                    b = 1;
                }
            }
        }
        if (!b)
            s++;
        if (s + 2 == n)
            break;
    }
    return 0;
}

int main()
{
    int n, i;
    scanf("%d",&n);

    int *array = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
        scanf("%d",&array[i]);
    int first = 0, last = n - 1;

    pyramid_sort(array, n);

    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n");
    free(array);

    return 0;
}