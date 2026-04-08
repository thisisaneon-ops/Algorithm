#include <iostream>
#include <functional>
using namespace std;

int GrabMiddle(int arr[], int a, int b, int c)
{
    if (arr[a] > arr[b])
    {
        if (arr[c] > arr[a])
            return a;
        else
        {
            return (arr[b] > arr[c] ? b : c);
        }
    }
    else
    {
        if (arr[c] > arr[b])
            return b;
        else
        {
            return (arr[a] > arr[c] ? a : c);
        }
    }
}

int Partition(int arr[], int begin, int end)
{
    int idx = GrabMiddle(arr, begin, begin + (end - begin) / 2, end);
    swap(arr[0], arr[idx]);
    int i = begin;
    int j = end;
    int pivot = arr[i];
    while (i < j)
    {
        while (i < j && arr[j] > pivot)
            j--;
        if (i < j)
        {
            arr[i] = arr[j];
            i++;
        }
        while (i < j && arr[i] < pivot)
            i++;
        if (i < j)
        {
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i] = pivot;
    return i;
}

void SelectTopK(int arr[], int begin, int end, int k)
{
    int pos = Partition(arr, begin, end);
    if (pos == k - 1)
        return;
    else if (pos > k - 1)
        SelectTopK(arr, begin, pos - 1, k);
    else
        SelectTopK(arr, pos + 1, end, k);
}

void test01()
{
    int arr[] = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    int size = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    SelectTopK(arr, 0, size - 1, k);
    for (int i = 0; i < k; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    cout << "Hello" << endl;
    test01();
    return 0;
}
