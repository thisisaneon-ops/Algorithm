// ##### [26] 基础去重 
// 返回有效元素的个数
// 核心：快慢指针；最基础模型
// slow负责写；fast负责读
// 核心判断就是纯粹的 nums[fast] 和 nums[slow] 是否相等

int removeDuplicatesI(vector<int>& nums)
{
	int slow = 0;
	int fast = 1;
	while (fast < nums.size())
	{
		if (nums[fast] != nums[slow])
		{
			slow++;
			nums[slow] = nums[fast];
		}
		fast++;
	}
	return slow + 1;
}
