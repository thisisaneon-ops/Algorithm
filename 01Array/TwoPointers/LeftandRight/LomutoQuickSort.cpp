#include<iostream>
using namespace std;

int Partition(int arr[], int left, int right)
{
	int pivot = arr[right];
	int i = left - 1;
	int j;
	for (j = left; j < right; j++)
	{
		if(arr[j] <= pivot)
		{
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[j]);
	int pos = i + 1;
	return pos;
}

void Lomuto(int arr[], int left, int right)
{
	if (left >= right)
		return;
	int pi = Partition(arr, left, right);
	Lomuto(arr, left, pi - 1);
	Lomuto(arr, pi + 1, right);
}

void test()
{
	srand(time(nullptr));
	int arr[10];
	for (int& i : arr)
		i = rand() % 90 + 10;
	cout << "Before sorting" << endl;
	for (int& i : arr)
		cout << i << " ";
	cout << endl;
	cout << "After sorting" << endl;
	Lomuto(arr, 0, 9);
	for (int& i : arr)
		cout << i << " ";
}

int main()
{
	test();
	return 0;
}
