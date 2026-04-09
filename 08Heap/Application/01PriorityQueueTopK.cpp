#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int arr[] = {1, 6, 7, 3, 5, 9, 12, 65, 43, 121, 89};
    int size = sizeof(arr) / sizeof(int);
    // 找前三小，默认大根堆
    priority_queue<int> q;
    int k = 3;
    for (int i = 0; i < k; i++)
    {
        q.push(arr[i]);
    }
    for (int i = k; i < size; i++)
    {
        int top = q.top();
        if (arr[i] > top)
        {
            continue;
        }
        else
        {
            q.pop();
            q.push(arr[i]);
        }
    }
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    return 0;
}