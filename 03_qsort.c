#include <stdio.h>
#include <stdlib.h>

int q_Sort(int *array, int first, int last)
{
    int c, temp = 0, operation = 0;
    int f = first, l = last;
    c = array[(f + l) / 2];
   
    do 
    {
        while (array[f] < c)
            f++;
        while (array[l] > c)
            l--;

        operation++;
        if (f <= l)
        {
            temp = array[f];
            array[f] = array[l];
            array[l] = temp;
            f++;
            l--;
            operation++;
        }
    } while (f <= l);

    if (first < l) 
        operation += q_Sort(array, first, l);
    if (f < last) 
        operation += q_Sort(array, f, last);

    return operation;
}

int main()
{
    int n, i, operation = 0;
    scanf("%d",&n);

    int *array = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
        scanf("%d",&array[i]);
    int first = 0, last = n - 1;

    operation = q_Sort(array, first, last);

    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n");
    printf("%d\n", operation);
    free(array);

    return 0;
}