#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *mergeFile;
FILE *quickFile;


void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    int size = r - l + 1;

    fprintf(mergeFile, "%d\n", size);

    if(l < r)
    {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if(arr[j] < pivot)
        {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if(low <= high)
    {
        int size = high - low + 1;

        fprintf(quickFile, "%d\n", size);
    }

    if(low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void generateData(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100000;
    }
}

int main()
{
    srand(time(NULL));

    int n = 100;

    int *data = (int *)malloc(n * sizeof(int));
    int *mergeArray = (int *)malloc(n * sizeof(int));
    int *quickArray = (int *)malloc(n * sizeof(int));

    generateData(data, n);

    for(int i = 0; i < n; i++)
    {
        mergeArray[i] = data[i];
        quickArray[i] = data[i];
    }

    mergeFile = fopen("merge_sizes.txt", "w");
    quickFile = fopen("quick_sizes.txt", "w");

    mergeSort(mergeArray, 0, n - 1);
    quickSort(quickArray, 0, n - 1);

    fclose(mergeFile);
    fclose(quickFile);

    printf("Analysis complete.\n");
    printf("Files generated:\n");
    printf("merge_sizes.txt\n");
    printf("quick_sizes.txt\n");

    free(data);
    free(mergeArray);
    free(quickArray);

    return 0;
}
