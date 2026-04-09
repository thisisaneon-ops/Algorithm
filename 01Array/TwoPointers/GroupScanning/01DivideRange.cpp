// ##### **[228] 最小区间范围**

// 题目描述：一句话说就是，把每个连续的数字区间表示为 a->b的形式，单元素区间不需要->，直接写a即可；

// 分区的标准应该是：当前元素和前一个元素是否是自增加一的关系；如果不是，说明需要划分区间，如果是的，说明在同一个区间内。根据长度 j - i 是否 == 1 一来判断是否需要加箭头标识，标识区间。 

vector<string>DivideRange(vector<int>& nums)
{
    vector<string>ret;
    int i = 0; 
    while(i < nums.size())
    {
        int j = i + 1;
        while(j < nums.size() && nums[j] == nums[j - 1] + 1)
        {
            j++;
        }
        // 最终会停在nums[j] != nums[j - 1]的位置
        // 例如：1 2 3  5 6  8  10
        if(j - i == 1)
        {
            ret.push_back(to_string(nums[i]));
        }
        else
        {
            string tmp;
            tmp += to_string(nums[i]);
            tmp += "->";
            tmp += to_string(nums[j - 1]);
            ret.push_back(tmp);
        }
        i = j;
    }
    return ret;
}