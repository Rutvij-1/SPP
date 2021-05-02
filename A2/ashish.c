#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define reg_long register long long
#define INF (int)1e9
#define MAX_SIZE 2501

void outputMat(long long **ar, int n)
{
	// int i, j;
	for (register int i = 1; i <= n; ++i)
	{
		for (register int j = 1; j <= n; ++j)
		{
			reg_long *ar_i = *(ar + i);
			reg_long temp = *(ar_i + j);
			if (temp != INF)
			{
				printf("%lld ", temp);
			}
			else
			{
				printf("-1 ");
			}
		}
		printf("\n");
	}
}

void FloydWarshall(long long **ar, int n)
{
	register int i, j, k;
	{
		// #pragma omp parallel
		for (k = 1; k <= n; ++k)
		{
			reg_long *ar_k = *(ar + k);
#pragma omp parallel for shared(ar, ar_k) private(i, j) num_threads(5)
			for (i = 1; i <= n; ++i)
			{
				reg_long *ar_i = *(ar + i);
				reg_long dist_ik = *(ar_i + k);
				if (dist_ik != INF)
				{
					for (j = 1; j <= n; ++j)
					{
						reg_long dist_ij = *(ar_i + j);
						reg_long dist_kj = *(ar_k + j);
						if (dist_ij > dist_ik + dist_kj)
						{
							*(ar_i + j) = dist_ik + dist_kj;
						}
					}
				}
			}
		}
	}
}

int main()
{
	int n1, n2, w;
	int v, e;
	struct timespec init, end;
	// int i, j;
	scanf("%d %d", &v, &e);
	long long **ar = malloc((v + 2) * sizeof(long long *));
	for (register int a = 0; a <= v; a++)
	{
		ar[a] = malloc(((v + 2) * sizeof(long long)));
	}
	for (register int i = 1; i <= v; ++i)
	{
		for (register int j = 1; j <= v; ++j)
		{
			ar[i][j] = INF;
			if (i == j)
			{
				ar[i][i] = 0;
			}
		}
	}
	for (register int i = 0; i < e; ++i)
	{
		scanf("%d %d %d", &n1, &n2, &w);
		if (n1 != n2)
		{
			ar[n1][n2] = w;
		}
	}
	if (clock_gettime(CLOCK_REALTIME, &init) < 0)
	{
		printf("error in getting time. Aborting\n");
		return -1;
	}
	FloydWarshall(ar, v);
	if (clock_gettime(CLOCK_REALTIME, &end) < 0)
	{
		printf("error in getting time. Aborting\n");
		return -1;
	}
	double tt = end.tv_sec - init.tv_sec;
	double ns = (1.0 * (end.tv_nsec - init.tv_nsec)) / 1e9;
	outputMat(ar, v);
	printf("Time Taken : %lf\n", tt + ns);
	return 0;
}
