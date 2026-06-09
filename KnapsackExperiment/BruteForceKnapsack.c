#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 25

int weight[MAX_ITEMS];
int value[MAX_ITEMS];

void generateItems(int n)
{
    for(int i = 0; i < n; i++)
    {
        weight[i] = rand() % 100 + 1;
        value[i] = 100 + rand() % 901;
    }
}

void runTest(int n, int capacity)
{
    generateItems(n);

    long long totalSubsets = 1LL << n;

    int bestValue = 0;
    int bestWeight = 0;

    clock_t start = clock();

    for(long long mask = 0;
        mask < totalSubsets;
        mask++)
    {
        int currentWeight = 0;
        int currentValue = 0;

        for(int i = 0; i < n; i++)
        {
            if(mask & (1LL << i))
            {
                currentWeight += weight[i];
                currentValue += value[i];
            }
        }

        if(currentWeight <= capacity &&
           currentValue > bestValue)
        {
            bestValue = currentValue;
            bestWeight = currentWeight;
        }
    }

    clock_t end = clock();

    double ms =
        1000.0 *
        (end - start)
        /
        CLOCKS_PER_SEC;

    printf("%-10d %-12d %-15d %-15d %-12.2f\n",
           n,
           capacity,
           bestValue,
           bestWeight,
           ms);
}

int main()
{
    srand((unsigned)time(NULL));

    int itemCounts[] =
    {
        10,
        15,
        20,
        25
    };

    int capacities[] =
    {
        10000,
        100000,
        1000000
    };

    printf("BRUTE FORCE KNAPSACK RESULTS\n\n");

    printf("%-10s %-12s %-15s %-15s %-12s\n",
           "Items",
           "Capacity",
           "BestValue",
           "BestWeight",
           "Time(ms)");

    for(int c = 0; c < 3; c++)
    {
        for(int i = 0; i < 4; i++)
        {
            runTest(
                itemCounts[i],
                capacities[c]
            );
        }

        printf("\n");
    }

    return 0;
}
