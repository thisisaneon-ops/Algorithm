// ##### [202]快乐数
// 编写一个算法来判断一个数 `n` 是不是快乐数。
// **快乐数** 定义为：
// - 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和
// - 然后重复这个过程直到这个数变为 1，或者 **无限循环** 但始终变不到 1
// - 如果这个过程 **结果为 1**，那么这个数就是快乐数
// 利用快慢指针抓住环的特性；一旦有环，那么必然会相遇；一旦最后fast 和 slow都是1那么就是快乐数

// 看到循环、环结构（无论是链表的显式环结构还是快乐数的逻辑环结构）都可以想快慢指针，Floyd算法

bool IsHappyNumber(int n)
{
    int slow = n;
    int fast = n;
    do{
        fast = func(func(fast));
        slow = func(slow);
    } while(fast != slow);
    if(fast == 1)
    {
        return true;
    }
    return false;
}
int func(int n)
{
    int sum = 0;
    while(n != 0)
    {
        int remainder = n % 10;
        n /= 10;
        sum += remainder * remainder;
    }
    return sum;
}
