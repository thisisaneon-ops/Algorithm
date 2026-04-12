int numTrees(int n){
    vector<int>memo(n + 1, 1);
    return C(memo, n);
}
int C(vector<int>&memo, int i){
    if(memo[i] > 1){
        return memo[i];
    }
    if(i == 0 || i == 1){
        memo[i] = 1;
        return memo[i];
    }
    int sum = 0;
    for(int k = 0; k < i; k++){
        sum += C(memo, k) * C(memo, i - 1 - k);
    }
    memo[i] = sum;
    return memo[i];
}


int numTrees(int n){
    vector<int>nums(n + 1, 0);
    nums[0] = 1;
    nums[1] = 1;
    for(int i = 2; i <= n; i++){
        int sum = 0;
        for(int j = 0; j < i; j++){
            sum += nums[j] * nums[i - 1 - j];
        }
        nums[i] = sum;
    }
    return nums[n];
}

/*
- 暴力递归**：时间复杂度 **O(2^n)** 或更精确地说是**卡特兰数级别** Ω(4nn3/2)Ω(*n*3/24*n*)，对于算法分析来说，视作**指数级**。
- **DP 解法** **：时间复杂度 **O(n^2)**，空间复杂度 O(n)。
*/