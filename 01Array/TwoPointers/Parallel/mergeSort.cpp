#include<iostream>
#include<vector>
using namespace std;

void Merge(vector<int>& arr, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    vector<int> tmp;
    while(i <= mid && j <= right)
    {
        if(arr[i] < arr[j])
        {
            tmp.push_back(arr[i]);
            i++;
        }
        else
        {
            tmp.push_back(arr[j]);
            j++;
        }
    }
    while(i <= mid)
    {
        tmp.push_back(arr[i]);
        i++;
    }
    while(j <= right)
    {
        tmp.push_back(arr[j]);
        j++;
    }
    for(int k = 0; k < right - left + 1; k++)
    {
        arr[left + k] = tmp[k];
    }
}

void MergeSort(vector<int>& arr, int left, int right)
{
    if(left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid);
    MergeSort(arr, mid + 1, right);
    Merge(arr, left, mid, right);
}

int main()
{

    return 0;
}
