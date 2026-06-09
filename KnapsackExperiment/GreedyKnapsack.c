#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int id;
    int weight;
    double value;
    double ratio;
} Item;

int compare(const void *a, const void *b)
{
    Item *x = (Item *)a;
    Item *y = (Item *)b;

    if(x->ratio < y->ratio)
        return 1;
    else if(x->ratio > y->ratio)
        return -1;
    else
        return 0;
}

void generateItems(Item items[], int n)
{
    for(int i = 0; i < n; i++)
    {
        items[i].id = i + 1;
        items[i].weight = rand() % 100 + 1;
        items[i].value = 100 + rand() % 901;
        items[i].ratio = items[i].value / items[i].weight;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int itemCounts[] =
    {
        1000,
        2000,
        3000,
        4000,
        5000,
        6000,
        7000,
        8000,
        9000,
        10000,
        20000,
        40000,
        80000,
        160000,
        320000
    };

    int capacities[] =
    {
        10000,
        100000,
        1000000
    };

    int numItems = sizeof(itemCounts) / sizeof(itemCounts[0]);
    int numCapacities = sizeof(capacities) / sizeof(capacities[0]);

    printf("GREEDY KNAPSACK RESULTS\n\n");

    printf("%-10s %-12s %-15s %-15s\n",
           "Items",
           "Capacity",
           "Total Value",
           "Time(ms)");

    for(int c = 0; c < numCapacities; c++)
    {
        int capacity = capacities[c];

        for(int t = 0; t < numItems; t++)
        {
            int n = itemCounts[t];

            Item *items =
                (Item *)malloc(n * sizeof(Item));

            if(items == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }

            generateItems(items, n);

            clock_t start = clock();

            qsort(items,
                  n,
                  sizeof(Item),
                  compare);

            int currentWeight = 0;
            double totalValue = 0;

            for(int i = 0; i < n; i++)
            {
                if(currentWeight +
                   items[i].weight <= capacity)
                {
                    currentWeight += items[i].weight;
                    totalValue += items[i].value;
                }
            }

            clock_t end = clock();

            double ms =
                1000.0 *
                (end - start) /
                CLOCKS_PER_SEC;

            printf("%-10d %-12d %-15.2f %-15.2f\n",
                   n,
                   capacity,
                   totalValue,
                   ms);

            free(items);
        }

        printf("\n");
    }

    return 0;
}
