#include <stdio.h>
#include <stdlib.h>

int q_Sort(int *array, int first, int last)
{
    int c, count;
    int f = first, l = last;
    c = array[(f + l) / 2];
   
    for (;f < l;) 
    {
        while (array[f] < c)
            f++;
        while (array[l] > c)
            l--;
        if (f <= l)
        {
            count = array[f];
            array[f] = array[l];
            array[l] = count;
            f++;
            l--;
        }
    }

    if (first < l) q_Sort(array, first, l);
    if (f < last) q_Sort(array, f, last);

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

    q_Sort(array, first, last);

    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n");
    free(array);

    return 0;
}