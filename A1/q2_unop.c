#include <stdio.h>
#include <time.h>

#define BILLION 1000000000L
#define INF 1000000000
#define dim 2505

int min(int a, int b)
{
	if (b < a)
		return b;
	return a;
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
	int adjm[dim][dim] = {0};
	for (int i = 0; i < dim; ++i)
		for (int j = 0; j < dim; ++j)
			if (i != j)
				adjm[i][j] = INF;
	scanf("%d%d", &v, &e);
	for (int i = 0; i < e; ++i)
	{
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		adjm[x - 1][y - 1] = min(adjm[x - 1][y - 1], w);
	}
	for (int k = 0; k < v; ++k)
		for (int i = 0; i < v; ++i)
			for (int j = 0; j < v; ++j)
				adjm[i][j] = min(adjm[i][j], adjm[i][k] + adjm[k][j]);
	for (int i = 0; i < v; ++i)
	{
		for (int j = 0; j < v; ++j)
		{
			if (adjm[i][j] == INF)
				printf("-1 ");
			else
				printf("%d ", adjm[i][j]);
		}
		printf("\n");
	}
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