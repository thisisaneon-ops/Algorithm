#include <iostream>
using namespace std;

void sift_down(int *arr, int pos, int size)
{
    int val = arr[pos];
    while (pos <= size / 2 - 1)
    {
        int child = 2 * pos + 1;
        if (child + 1 < size && arr[child + 1] > arr[child])
        {
            child = child + 1;
        }
        if (arr[child] > val)
        {
            arr[pos] = arr[child];
            pos = child;
        }
        else
        {
            break;
        }
    }
    arr[pos] = val;
}

void heapSort(int *arr, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        sift_down(arr, i, size);
    }
    for (int i = size - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        sift_down(arr, 0, i);
    }
}

int main()
{
    int arr[] = {9, 8, 6, 1, 4, 2, 5, 7, 3};
    int size = sizeof(arr) / sizeof(int);
    for (auto &u : arr)
    {
        cout << u << " ";
    }
    cout << endl;
    heapSort(arr, size);
    for (auto &u : arr)
    {
        cout << u << " ";
    }
    cout << endl;
    return 0;
}