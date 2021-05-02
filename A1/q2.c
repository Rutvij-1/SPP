#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define BILLION 1000000000L
#define INF 1000000000

int **malloc_mat(int x, int y)
{
	int **a = (int **)malloc(x * sizeof(int *));
	register int i;
	for (i = 0; i < x; ++i)
		a[i] = (int *)malloc(y * sizeof(int));
	return a;
}

void free_mat(int **restrict a, int x)
{
	register int i;
	for (i = 0; i < x; ++i)
		free(a[i]);
	free(a);
}

int main()
{
	// struct timespec begin, end;
	// if (clock_gettime(CLOCK_REALTIME, &begin) == -1)
	// {
	// 	perror("clock gettime");
	// 	return EXIT_FAILURE;
	// }
	int v, e;
	scanf("%d%d", &v, &e);
	int **adjm = malloc_mat(v, v);
	register int i, j, k;
	for (i = 0; i < v; ++i)
	{
		for (j = 0; j < v; ++j)
		{
			if (i == j)
				adjm[i][j] = 0;
			else
				adjm[i][j] = INF;
		}
	}
	int x, y, w;
	for (i = 0; i < e; ++i)
	{
		scanf("%d%d%d", &x, &y, &w);
		--x;
		--y;
		if (w < adjm[x][y])
			adjm[x][y] = w;
	}
	int val, temp;
	for (i = 0; i < v; ++i)
	{
		for (j = 0; j < v; ++j)
		{
			temp = adjm[j][i];
			if (temp == INF)
				continue;
			for (k = 0; k < v; ++k)
			{
				val = temp + adjm[i][k];
				if (val < adjm[j][k])
					adjm[j][k] = val;
			}
		}
	}
	for (i = 0; i < v; ++i)
	{
		for (j = 0; j < v; ++j)
		{
			if (adjm[i][j] == INF)
				printf("-1 ");
			else
				printf("%d ", adjm[i][j]);
		}
		printf("\n");
	}
	free_mat(adjm, v);
	// if (clock_gettime(CLOCK_REALTIME, &end) == -1)
	// {
	// 	perror("clock gettime");
	// 	return EXIT_FAILURE;
	// }
	// double S = (end.tv_sec - begin.tv_sec);
	// double NS = (double)(end.tv_nsec - begin.tv_nsec) / (double)BILLION;
	// printf("\n\nTime taken for execution: %lf seconds\n", S + NS);
	return 0;
}