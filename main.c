#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long bubbleComp = 0;
long long mergeComp = 0;
long long quickComp = 0;


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
    if(l<r)
    {
        int m=(l+r)/2;

        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);

        merge(arr,l,m,r);
    }
}


int partition(int arr[], int low, int high)
{
    int pivot=arr[high];
    int i=low-1;

    for(int j=low;j<high;j++)
    {
        quickComp++;

        if(arr[j] < pivot)
        {
            i++;

            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }

    int temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;

    return i+1;
}

void quickSort(int arr[], int low, int high)
{
    if(low<high)
    {
        int pi=partition(arr,low,high);

        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}


void generateData(int arr[], int n)
{
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%100000;
    }
}

int main()
{
    srand(time(NULL));

    int sizes[] =
    {
        10,
        100,
        1000,
        2000,
        5000,
        10000
    };

    printf("SIZE\tBubbleComp\tMergeComp\tQuickComp\n");

    for(int s=0;s<6;s++)
    {
        int n=sizes[s];

        int *data=(int*)malloc(n*sizeof(int));

        generateData(data,n);

        int *a=(int*)malloc(n*sizeof(int));
        int *b=(int*)malloc(n*sizeof(int));
        int *c=(int*)malloc(n*sizeof(int));

        memcpy(a,data,n*sizeof(int));
        memcpy(b,data,n*sizeof(int));
        memcpy(c,data,n*sizeof(int));

        bubbleComp=0;
        mergeComp=0;
        quickComp=0;

        bubbleSort(a,n);

        mergeSort(b,0,n-1);

        quickSort(c,0,n-1);

        printf("%d\t%lld\t\t%lld\t\t%lld\n",
               n,
               bubbleComp,
               mergeComp,
               quickComp);

        free(data);
        free(a);
        free(b);
        free(c);
    }

    return 0;
}
