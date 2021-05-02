#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define BILLION 1000000000L
#define ll long long
#define dim 1005

ll n, x, y;
ll prev[dim][dim];

int main()
{
	struct timespec begin, end;
	if (clock_gettime(CLOCK_REALTIME, &begin) == -1)
	{
		perror("clock gettime");
		return EXIT_FAILURE;
	}
	scanf("%lld", &n);
	scanf("%lld%lld", &x, &y);
	for (int i = 0; i < x; ++i)
		for (int j = 0; j < y; ++j)
			scanf("%lld", &prev[i][j]);
	for (int z = 1; z < n; ++z)
	{
		ll dx, dy;
		ll mat[dim][dim], ans[dim][dim] = {0};
		scanf("%lld%lld", &dx, &dy);
		for (int i = 0; i < dx; ++i)
			for (int j = 0; j < dy; ++j)
				scanf("%lld", &mat[i][j]);
		for (int i = 0; i < x; ++i)
			for (int j = 0; j < dy; ++j)
				for (int k = 0; k < y; ++k)
					ans[i][j] += prev[i][k] * mat[k][j];
		y = dy;
		for (int i = 0; i < x; ++i)
			for (int j = 0; j < y; ++j)
				prev[i][j] = ans[i][j];
	}
	printf("%lld %lld\n", x, y);
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
			printf("%lld ", prev[i][j]);
		printf("\n");
	}
	if (clock_gettime(CLOCK_REALTIME, &end) == -1)
	{
		perror("clock gettime");
		return EXIT_FAILURE;
	}
	double S = (end.tv_sec - begin.tv_sec);
	double NS = (double)(end.tv_nsec - begin.tv_nsec) / (double)BILLION;
	printf("\n\nTime taken for execution: %lf seconds\n", S + NS);
	return 0;
}