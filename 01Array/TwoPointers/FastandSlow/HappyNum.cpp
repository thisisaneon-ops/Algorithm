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
