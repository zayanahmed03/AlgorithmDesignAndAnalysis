#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 50

int weight[MAX_ITEMS];
int value[MAX_ITEMS];

int n;
int capacity;

int bestValue;


void backtrack(
    int index,
    int currentWeight,
    int currentValue)
{
    if(index == n)
    {
        if(currentValue > bestValue)
        {
            bestValue = currentValue;
        }
        return;
    }

    if(currentWeight + weight[index]
       <= capacity)
    {
        backtrack(
            index + 1,
            currentWeight + weight[index],
            currentValue + value[index]
        );
    }

    backtrack(
        index + 1,
        currentWeight,
        currentValue
    );
}

void generateItems()
{
    for(int i = 0; i < n; i++)
    {
        weight[i] = rand() % 100 + 1;
        value[i] = 100 + rand() % 901;
    }
}

void runTest(int items, int cap)
{
    n = items;
    capacity = cap;

    generateItems();

    bestValue = 0;

    clock_t start = clock();

    backtrack(0,0,0);

    clock_t end = clock();

    double ms =
        1000.0 *
        (end - start)
        /
        CLOCKS_PER_SEC;

    printf("%-10d %-12d %-15d %-12.2f\n",
           n,
           capacity,
           bestValue,
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
        25,
        30,
        35
    };

    int capacities[] =
    {
        10000,
        100000,
        1000000
    };

    printf("BACKTRACKING KNAPSACK RESULTS\n\n");

    printf("%-10s %-12s %-15s %-12s\n",
           "Items",
           "Capacity",
           "BestValue",
           "Time(ms)");

    for(int c = 0; c < 3; c++)
    {
        for(int i = 0; i < 6; i++)
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
