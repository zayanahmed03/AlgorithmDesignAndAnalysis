#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int main()
{
    srand((unsigned)time(NULL));

    FILE *fp = fopen("Knapsack1000Data.csv", "w");

    if(fp == NULL)
    {
        printf("Cannot create file.\n");
        return 1;
    }

    fprintf(fp, "ItemID,Weight,Value\n");

    for(int i = 1; i <= N; i++)
    {
        int weight = rand() % 100 + 1;
        int value  = 100 + rand() % 901;

        fprintf(fp, "%d,%d,%d\n",
                i,
                weight,
                value);
    }

    fclose(fp);

    printf("File generated: Knapsack1000Data.csv\n");

    return 0;
}
