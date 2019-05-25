#include <stdio.h>
#include <stdlib.h>
#define INFINITY 100000

void dijkstra(int node, int now, int *done, int *dest, int *dist, int matrixForDijkstra[][node])
{
    done[now] = 1;

    for (int i = 0; i < node; i++)
    {
        if (matrixForDijkstra[now][i] == INFINITY)
            continue;

        int newDistance = dist[now] + matrixForDijkstra[now][i];

        if (newDistance < dist[i])
        {
            dist[i] = newDistance;
            dest[i] = now;
        }
    }

    int min = INFINITY, index;

    for (int i = 0; i < node; i++)
    {
        if (done[i])
            continue;

        if (dist[i] < min)
        {
            min = dist[i];
            index = i;
        }
    }

    if (min == INFINITY)
        return;

    dijkstra(node, index, done, dest, dist, matrixForDijkstra);
}

int TSP(int city, int path, int limit, int visited[10], int matrix[][36])
{
	visited[city] = 1;
	printf("%d ", city + 1);


	int count, near_city = 999, min = 999, temp;

	for(count = 0; count < limit; count++)
	{
		if((matrix[city][count] != 0) && (visited[count] == 0))
		{
			if(matrix[city][count] < min)
				min = matrix[count][0] + matrix[city][count];
			temp = matrix[city][count];
			near_city = count;
		}
	}

	if(min != 999)
		path = path + temp;

	if(near_city == 999)
	{
		near_city = 0;
		printf("%d", near_city + 1);
		path = path + matrix[city][near_city];
		return path;
	}
	path += TSP(near_city, path, limit, visited, matrix);
}

int main()
{	
	printf("\n\n%s\n\n", "Задача 1");
    int node;
    printf("Введите количетсво вершин: ");
    scanf("%d", &node);

    int matrixForDijkstra[node][node];
    printf("Введите матрицу смежности: \n");
    for (int i = 0; i < node; i++)
    {

        for (int j = 0; j < node; j++)
        {

            if (i == j)
            {
                matrixForDijkstra[i][j] = 0;
                continue;
            }
            printf("%d -----> %d  ", i + 1, j + 1);
            scanf("%d", &matrixForDijkstra[i][j]);
        }
    }

    int begin;
    printf("Введите начальную вершину: ");
    scanf("%d", &begin);

    // посещенный вершины
    int done[node];

    // путь
    int dest[node];

    // дистанция от начальной вершины
    int dist[node];

    // инициализация начальных значений
    for (int i = 0; i < node; i++)
    {
        done[i] = 0;
        dest[i] = -1;
        dist[i] = INFINITY;
    }
    begin--;
    dist[begin] = 0;

    dijkstra(node, begin, done, dest, dist, matrixForDijkstra);

    // ALGORITHM ENDS HERE only displaying paths below
    printf("\nПуть от %d к:\n", begin + 1);
    for (int i = 0; i < node; i++)
    {
        if (i == begin)
        {
            printf("%d: нет пути\n", i + 1);
            continue;
        }

        int now = i;
        int path[node];
        int t = node - 1;
        for (int j = 0; j < node; j++)
            path[j] = -1;

        while (now > -1)
        {
            path[t--] = now;
            now = dest[now];
        }

        printf("%d: ", i + 1);
        for (int j = 0; j < node; j++)
        {

            if (path[j] == -1)
                continue;
            printf("%d", path[j] + 1);
            if (j + 1 != node)
                printf("-->");
        }
        printf("\t\tДистанция: %d\n", dist[i]);
    }


    ////////////////////////////////
    printf("\n\n%s\n\n", "Задача 2");

    int matrix[36][36], visited[10], limit, path = 0;	
	printf("Введите количество городов: \t");
	scanf("%d", &limit);
	printf("\nВведите матрицу смежности: \n");

	for (int i = 0; i < limit; i++)
	{
		printf("\nВведите %d строки[%d]\n", limit, i + 1);
		for (int j = 0; j < limit; j++)
			scanf("%d", &matrix[i][j]);

		visited[i] = 0;
	}
	
	printf("\n\nПуть:\t");

	path = TSP(0, path, limit, visited, matrix);

	printf("\n\nМинимальное расстояние: \t");
	printf("%d\n", path);

	return 0;
}
