#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long bubbleComp;
long long mergeComp;
long long quickComp;


void bubbleSort(int arr[], int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            bubbleComp++;

            if(arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


void merge(int arr[], int l, int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;

    int *L = (int*)malloc(n1*sizeof(int));
    int *R = (int*)malloc(n2*sizeof(int));

    for(int i=0;i<n1;i++)
        L[i] = arr[l+i];

    for(int i=0;i<n2;i++)
        R[i] = arr[m+1+i];

    int i=0,j=0,k=l;

    while(i<n1 && j<n2)
    {
        mergeComp++;

        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i<n1)
        arr[k++] = L[i++];

    while(j<n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = (l+r)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low-1;

    for(int j=low;j<high;j++)
    {
        quickComp++;

        if(arr[j] < pivot)
        {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return i+1;
}

void quickSort(int arr[], int low, int high)
{
    if(low < high)
    {
        int pi = partition(arr,low,high);

        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}


void generateData(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i] = rand() % 1000;
    }
}

void testDataset(int datasetNumber)
{
    int n = 100;

    int data[100];
    int bubble[100];
    int mergeA[100];
    int quickA[100];

    generateData(data,n);

    memcpy(bubble,data,sizeof(data));
    memcpy(mergeA,data,sizeof(data));
    memcpy(quickA,data,sizeof(data));


    printf("DATASET %d\n\n",datasetNumber);

    printf("Random Numbers:\n");

    for(int i=0;i<n;i++)
    {
        printf("%d ",data[i]);

        if((i+1)%10==0)
            printf("\n");
    }

    bubbleComp = 0;
    mergeComp = 0;
    quickComp = 0;

    bubbleSort(bubble,n);
    mergeSort(mergeA,0,n-1);
    quickSort(quickA,0,n-1);

    printf("\nComparison Counts:\n");
    printf("Bubble Sort = %lld\n",bubbleComp);
    printf("Merge Sort  = %lld\n",mergeComp);
    printf("Quick Sort  = %lld\n",quickComp);
}

int main()
{
    srand(time(NULL));

    testDataset(1);

    printf("\n\nPress ENTER for Dataset 2...");
    getchar();

    testDataset(2);

    return 0;
}
