#include <stdio.h>
#include <stdlib.h>

int siftDown(int *array, int first, int end)
{
    int maxChild;
    int done = 0; 
    int operation = 0;
                  
    while ((first * 2 <= end) && (!done))
    {
        if (first * 2 == end)  
            maxChild = first * 2; 

        else if (array[first * 2] > array[first * 2 + 1])
            maxChild = first * 2;
        else
            maxChild = first * 2 + 1;
        
        operation++;
        if (array[first] < array[maxChild])
        {
            int temp = array[first]; 
            array[first] = array[maxChild];
            array[maxChild] = temp;
            first = maxChild;
            operation++;
        }
        else          
            done = 1; 
    }

    return operation;
}

int pyramid_sort(int *array, int array_size)
{  
    int operation = 0;
    
    for (int i = (array_size / 2) - 1; i >= 0; i--)
       operation += siftDown(array, i, array_size - 1);
   
    for (int i = array_size - 1; i >= 1; i--)
    {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        operation++;
        operation += siftDown(array, 0, i - 1);
    }

    return operation;
}

int main()
{
    int n, i, operation = 0;
    scanf("%d", &n);

    int *array = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
        scanf("%d",&array[i]);
    
    operation = pyramid_sort(array, n);

    for (i = 0; i < n; i++)
        printf("%d ", array[i]);

    printf("\n");
    printf("%d\n", operation);
    free(array);

    return 0;
}