#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void runDP(int n, int W)
{
    int *wt = (int *)malloc(n * sizeof(int));
    int *val = (int *)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
    {
        wt[i] = rand() % 100 + 1;
        val[i] = 100 + rand() % 901;
    }

    clock_t start = clock();

    int **dp = (int **)malloc((n + 1) * sizeof(int *));

    for(int i = 0; i <= n; i++)
    {
        dp[i] = (int *)calloc(W + 1, sizeof(int));
    }

    for(int i = 1; i <= n; i++)
    {
        for(int w = 0; w <= W; w++)
        {
            if(wt[i - 1] <= w)
            {
                dp[i][w] = max(
                    dp[i - 1][w],
                    val[i - 1] +
                    dp[i - 1][w - wt[i - 1]]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    clock_t end = clock();

    double ms =
        1000.0 *
        (end - start) /
        CLOCKS_PER_SEC;

    double memoryMB =
        ((double)(n + 1) * (W + 1) * 4)
        / 1024 / 1024;

    printf("%-8d %-10d %-12d %-12.2f %-12.2f\n",
           n,
           W,
           dp[n][W],
           ms,
           memoryMB);

    for(int i = 0; i <= n; i++)
        free(dp[i]);

    free(dp);
    free(wt);
    free(val);
}

int main()
{
    srand((unsigned)time(NULL));

    int itemCounts[] =
    {
        100,
        200,
        500,
        1000,
        2000,
        3000,
        5000
    };

    int capacities[] =
    {
        1000,
        5000,
        10000
    };

    printf("DYNAMIC PROGRAMMING KNAPSACK RESULTS\n\n");

    printf("%-8s %-10s %-12s %-12s %-12s\n",
           "Items",
           "Capacity",
           "MaxValue",
           "Time(ms)",
           "Memory(MB)");

    for(int c = 0; c < 3; c++)
    {
        for(int i = 0; i < 7; i++)
        {
            runDP(
                itemCounts[i],
                capacities[c]
            );
        }

        printf("\n");
    }

    return 0;
}
