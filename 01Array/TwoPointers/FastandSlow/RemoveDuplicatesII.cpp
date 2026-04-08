#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if(nums.size() <= 2)
    {
        return nums.size();
    }
    int slow = 0;
    int fast = 1;
    int dup = 1;
    while(fast < nums.size())
    {
        if(nums[fast] == nums[slow])
        {
            dup++;
        }
        else
        {
            dup = 1;
        }
        if(dup > 2)
        {
            fast++;
        }
        else
        {
            slow++;
            nums[slow] = nums[fast];
            fast++;
        }
    }
    return slow+1;
}

int main()
{
    vector<int>n = {1,1,1,2};
    int N = removeDuplicates(n);
    cout << N << endl;
    for(int i = 0; i < N; i++)
    {
        cout << n[N] << " ";
    }
    return 0;
}
