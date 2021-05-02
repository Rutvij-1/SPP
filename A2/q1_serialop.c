#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define BILLION 1000000000L
#define ll long long

int **dp = NULL;
ll ***mat = NULL;
int *dim = NULL;

void free_mat(ll **restrict a, int x)
{
	register int i;
	for (i = 0; i < x; ++i)
		free(a[i]);
	free(a);
}

ll **calloc_mat(int x, int y)
{
	ll **a = (ll **)calloc(x, sizeof(ll *));
	register int i;
	for (i = 0; i < x; ++i)
		a[i] = (ll *)calloc(y, sizeof(ll));
	return a;
}

ll **malloc_mat(int x, int y)
{
	ll **a = (ll **)malloc(x * sizeof(ll *));
	register int i;
	for (i = 0; i < x; ++i)
		a[i] = (ll *)malloc(y * sizeof(ll));
	return a;
}

// Tiled matrix multiplication
int s = 64;
ll **matrix_mul(ll **restrict a, ll **restrict b, int x, int m, int y)
{
	ll **c = calloc_mat(x, y);
	register int i1, j1, k1, i, j, k;
	ll temp;
	int limi, limj, limk;
	ll *pc, *pb;
	for (i1 = 0; i1 < x; i1 += s)
	{
		limi = i1 + s;
		if (limi > x)
			limi = x;
		for (k1 = 0; k1 < m; k1 += s)
		{
			limk = k1 + s;
			if (limk > m)
				limk = m;
			for (j1 = 0; j1 < y; j1 += s)
			{
				limj = j1 + s;
				if (limj > y)
					limj = y;
				for (i = i1; i < limi; ++i)
					for (k = k1; k < limk; ++k)
					{
						temp = a[i][k];
						pc = c[i] + j1;
						pb = b[k] + j1;
						for (j = j1; j < limj - 15; j += 16)
						{
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
							*pc++ += temp * (*pb++);
						}
						for (; j < limj; ++j)
							*pc++ += temp * (*pb++);
					}
			}
		}
	}
	return c;
}

ll **get_mat(int x, int y)
{
	ll **a = malloc_mat(x, y);
	register int i, j;
	for (i = 0; i < x; ++i)
	{
		ll *row = a[i];
		for (j = 0; j < y; ++j)
			scanf("%lld", (row + j));
	}
	return a;
}

void matrix_op(int n)
{
	ll **op = malloc_mat(n, n);
	dp = (int **)malloc(n * sizeof(int *));
	register int i, j, k;
	for (i = 0; i < n; ++i)
	{
		op[i][i] = 0;
		dp[i] = (int *)malloc(n * sizeof(int));
		dp[i][i] = i;
	}
	int temp1, temp2, pos;
	ll temp3, val, tval;
	for (i = 2; i <= n; ++i)
	{
		temp1 = n - i + 1;
		for (j = 0; j < temp1; ++j)
		{
			temp2 = j + i - 1;
			temp3 = INT_MAX;
			tval = dim[j] * dim[temp2 + 1];
			for (k = j; k < temp2; ++k)
			{
				val = op[j][k] + op[k + 1][temp2] + (tval * dim[k + 1]);
				if (val < temp3)
				{
					temp3 = val;
					pos = k;
				}
			}
			op[j][temp2] = temp3;
			dp[j][temp2] = pos;
		}
	}
	free_mat(op, n);
}

ll **fun(int l, int r)
{
	if (l < r)
	{
		int p = dp[l][r], x = dim[l], y = dim[p + 1], z = dim[r + 1];
		ll **mat1 = fun(l, p), **mat2 = fun(p + 1, r);
		ll **ans = matrix_mul(mat1, mat2, x, y, z);
		if (l < p)
			free_mat(mat1, x);
		if (p + 1 < r)
			free_mat(mat2, y);
		return ans;
	}
	return mat[l];
}

int main()
{
	// struct timespec begin, end;
	// if (clock_gettime(CLOCK_REALTIME, &begin) == -1)
	// {
	// 	perror("clock gettime");
	// 	return EXIT_FAILURE;
	// }
	int n;
	scanf("%d", &n);
	register int i, j;
	int *x = (int *)malloc(n * sizeof(int)), *y = (int *)malloc(n * sizeof(int));
	dim = (int *)malloc((n + 1) * sizeof(int));
	mat = (ll ***)malloc(n * sizeof(ll *));
	int temp_y;
	for (i = 0; i < n; ++i)
	{
		scanf("%d%d", (x + i), (y + i));
		temp_y = y[i];
		mat[i] = get_mat(x[i], temp_y);
		dim[i + 1] = temp_y;
	}
	dim[0] = x[0];
	matrix_op(n);
	ll **ans = fun(0, n - 1);
	printf("%d %d\n", x[0], y[n - 1]);
	for (i = 0; i < x[0]; ++i)
	{
		for (j = 0; j < y[n - 1]; ++j)
			printf("%lld ", ans[i][j]);
		printf("\n");
	}
	for (i = 0; i < n; ++i)
	{
		free_mat(mat[i], x[i]);
		free(dp[i]);
	}
	free(dp);
	free(mat);
	free(dim);
	if (n > 1)
		free_mat(ans, x[0]);
	free(x);
	free(y);
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
