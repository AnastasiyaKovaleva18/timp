#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Сортировка расческой
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

// Сортировка Шелла
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

// Быстрая сортировка
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

// Функция формирования кучи
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

// Пирамидальная сортировка
int pyramid_sort(int *array, int size)
{  
    int operation = 0;
    
    for (int i = (size / 2) - 1; i >= 0; i--)
       operation += siftDown(array, i, size - 1);
   
    for (int i = size - 1; i >= 1; i--)
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
	 int i, j, z, operation = 0, res_operation = 0;
	 double average_time = 0;
	 const int sizeArr[15] = {1, 2, 3, 4, 5, 10, 15, 20, 25, 30, 50, 75, 100, 250, 500};

	 // ----------------------------------------------------------------------------------------------------------------------------

     printf("%s\n","\n\nСОРТИРОВКА РАСЧЕСКОЙ");
     printf("%s %s %s %s %s\n","Длина массива\t","Среднее время\t","Среднее количество операций\t","Лучшее время   ","Худшее время");   
	 for (i = 0; i < 15; i++)
	 {
	 	average_time = 0; res_operation = 0;

	 	for (j = 0; j < 1000; j++)
	 	{	
	 		// Создаем массив нужной длины
	 		int *arr = (int *)malloc(sizeof(int) * sizeArr[i]);

	 		// Заполняем массив рандомными числами
	 		srand(time(NULL));
            for (z = 0; z < sizeArr[i]; z++) {
                arr[z] = rand() %1000;
            }

            // Вычисляем время сортировки одного массива
            double t1 = clock();
			operation = comb_sort(arr, sizeArr[i]);
			double t2 = clock();
			double t3 = (t2 - t1) / CLOCKS_PER_SEC;

			//Суммируем общее время всех массивов и общее количество операций
			average_time += t3;
			res_operation += operation;

			free(arr);
	 	}

	 	// Вычисляем средние значения времени и количества операций
	 	average_time = average_time / 1000;
	 	res_operation = res_operation / 1000;

	 	// Массивы хранят лучшее и худшее время 
	 	int *bestTime = malloc(sizeof(int) * sizeArr[i]);
        int *worstTime = malloc(sizeof(int) * sizeArr[i]);

        // Заполняем массивы
        for (j = 0; j < sizeArr[i]; j++){
            bestTime[j] = j;
            worstTime[j] = sizeArr[i] - j;
        }

        // Вычисляем лучшее время
		double t1 = clock();
		comb_sort(bestTime, sizeArr[i]);
		double t2 = clock();
		double best = (t2 - t1) / CLOCKS_PER_SEC;
		free(bestTime);

		// Вычисляем худшее время
        t1 = clock();
		comb_sort(worstTime, sizeArr[i]);
		t2 = clock();
		double worst = (t2 - t1) / CLOCKS_PER_SEC;
        free(worstTime);

        // Выводим результат
        printf("%d%s %f%s %d%s %f%s %f\n", sizeArr[i],"\t\t", average_time, "\t",
        	res_operation, "\t\t\t\t", best, "\t", worst);
	 }

	 // ----------------------------------------------------------------------------------------------------------------------------

	 printf("%s\n","\n\nСОРТИРОВКА ШЕЛЛА");
     printf("%s %s %s %s %s\n","Длина массива\t","Среднее время\t","Среднее количество операций\t","Лучшее время   ","Худшее время");   
	 for (i = 0; i < 15; i++)
	 {
	 	average_time = 0; res_operation = 0;

	 	for (j = 0; j < 1000; j++)
	 	{	
	 		// Создаем массив нужной длины
	 		int *arr = (int *)malloc(sizeof(int) * sizeArr[i]);

	 		// Заполняем массив рандомными числами
	 		srand(time(NULL));
            for (z = 0; z < sizeArr[i]; z++) {
                arr[z] = rand() %1000;
            }

            // Вычисляем время сортировки одного массива
            double t1 = clock();
			operation = shell_sort(arr, sizeArr[i]);
			double t2 = clock();
			double t3 = (t2 - t1) / CLOCKS_PER_SEC;

			//Суммируем общее время всех массивов и общее количество операций
			average_time += t3;
			res_operation += operation;

			free(arr);
	 	}

	 	// Вычисляем средние значения времени и количества операций
	 	average_time = average_time / 1000;
	 	res_operation = res_operation / 1000;

	 	// Массивы хранят лучшее и худшее время 
	 	int *bestTime = malloc(sizeof(int) * sizeArr[i]);
        int *worstTime = malloc(sizeof(int) * sizeArr[i]);

        // Заполняем массивы
        for (j = 0; j < sizeArr[i]; j++){
            bestTime[j] = j;
            worstTime[j] = sizeArr[i] - j;
        }

        // Вычисляем лучшее время
		double t1 = clock();
		shell_sort(bestTime, sizeArr[i]);
		double t2 = clock();
		double best = (t2 - t1) / CLOCKS_PER_SEC;
		free(bestTime);

		// Вычисляем худшее время
        t1 = clock();
		shell_sort(worstTime, sizeArr[i]);
		t2 = clock();
		double worst = (t2 - t1) / CLOCKS_PER_SEC;
        free(worstTime);

        // Выводим результат
        printf("%d%s %f%s %d%s %f%s %f\n", sizeArr[i],"\t\t", average_time, "\t",
        	res_operation, "\t\t\t\t", best, "\t", worst);
	 }

	 // ----------------------------------------------------------------------------------------------------------------------------

	 printf("%s\n","\n\nБЫСТРАЯ СОРТИРОВКА");
     printf("%s %s %s %s %s\n","Длина массива\t","Среднее время\t","Среднее количество операций\t","Лучшее время   ","Худшее время");   
	 for (i = 0; i < 15; i++)
	 {
	 	average_time = 0; res_operation = 0;

	 	for (j = 0; j < 1000; j++)
	 	{	
	 		// Создаем массив нужной длины
	 		int *arr = (int *)malloc(sizeof(int) * sizeArr[i]);

	 		// Заполняем массив рандомными числами
	 		srand(time(NULL));
            for (z = 0; z < sizeArr[i]; z++) {
                arr[z] = rand() %1000;
            }

            // Вычисляем время сортировки одного массива
            double t1 = clock();
			operation = q_Sort(arr, 0, sizeArr[i] - 1);
			double t2 = clock();
			double t3 = (t2 - t1) / CLOCKS_PER_SEC;

			//Суммируем общее время всех массивов и общее количество операций
			average_time += t3;
			res_operation += operation;

			free(arr);
	 	}

	 	// Вычисляем средние значения времени и количества операций
	 	average_time = average_time / 1000;
	 	res_operation = res_operation / 1000;

	 	// Массивы хранят лучшее и худшее время 
	 	int *bestTime = malloc(sizeof(int) * sizeArr[i]);
        int *worstTime = malloc(sizeof(int) * sizeArr[i]);

        // Заполняем массивы
        for (j = 0; j < sizeArr[i]; j++){
            bestTime[j] = j;
            worstTime[j] = sizeArr[i] - j;
        }

        // Вычисляем лучшее время
		double t1 = clock();
		q_Sort(bestTime, 0, sizeArr[i] - 1);
		double t2 = clock();
		double best = (t2 - t1) / CLOCKS_PER_SEC;
		free(bestTime);

		// Вычисляем худшее время
        t1 = clock();
		q_Sort(worstTime, 0, sizeArr[i] - 1);
		t2 = clock();
		double worst = (t2 - t1) / CLOCKS_PER_SEC;
        free(worstTime);

        // Выводим результат
        printf("%d%s %f%s %d%s %f%s %f\n", sizeArr[i],"\t\t", average_time, "\t",
        	res_operation, "\t\t\t\t", best, "\t", worst);
	 }

	 // ----------------------------------------------------------------------------------------------------------------------------

	 printf("%s\n","\n\nПИРАМИДАЛЬНАЯ СОРТИРОВКА");
     printf("%s %s %s %s %s\n","Длина массива\t","Среднее время\t","Среднее количество операций\t","Лучшее время   ","Худшее время");   
	 for (i = 0; i < 15; i++)
	 {
	 	average_time = 0; res_operation = 0;

	 	for (j = 0; j < 1000; j++)
	 	{	
	 		// Создаем массив нужной длины
	 		int *arr = (int *)malloc(sizeof(int) * sizeArr[i]);

	 		// Заполняем массив рандомными числами
	 		srand(time(NULL));
            for (z = 0; z < sizeArr[i]; z++) {
                arr[z] = rand() %1000;
            }

            // Вычисляем время сортировки одного массива
            double t1 = clock();
			operation = pyramid_sort(arr, sizeArr[i]);
			double t2 = clock();
			double t3 = (t2 - t1) / CLOCKS_PER_SEC;

			//Суммируем общее время всех массивов и общее количество операций
			average_time += t3;
			res_operation += operation;

			free(arr);
	 	}

	 	// Вычисляем средние значения времени и количества операций
	 	average_time = average_time / 1000;
	 	res_operation = res_operation / 1000;

	 	// Массивы хранят лучшее и худшее время 
	 	int *bestTime = malloc(sizeof(int) * sizeArr[i]);
        int *worstTime = malloc(sizeof(int) * sizeArr[i]);

        // Заполняем массивы
        for (j = 0; j < sizeArr[i]; j++){
            bestTime[j] = j;
            worstTime[j] = sizeArr[i] - j;
        }

        // Вычисляем лучшее время
		double t1 = clock();
		pyramid_sort(bestTime, sizeArr[i]);
		double t2 = clock();
		double best = (t2 - t1) / CLOCKS_PER_SEC;
		free(bestTime);

		// Вычисляем худшее время
        t1 = clock();
		pyramid_sort(worstTime, sizeArr[i]);
		t2 = clock();
		double worst = (t2 - t1) / CLOCKS_PER_SEC;
        free(worstTime);

        // Выводим результат
        printf("%d%s %f%s %d%s %f%s %f\n", sizeArr[i],"\t\t", average_time, "\t",
        	res_operation, "\t\t\t\t", best, "\t", worst);
	 }

	return 0;
}
