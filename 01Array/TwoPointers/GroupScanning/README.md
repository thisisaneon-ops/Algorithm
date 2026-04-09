这是一类不常见的技巧。核心思想就是在一次遍历的过程中分区，选取区域内部有标志的对象代表整个区间，配了几道练习可以选择性阅读！

```C++
// 范式：
T i = init_;
T record = head;
while(i != illegal)
{
    T j = i;
    while(j != illegal && j ? i)
    {
        j++;
    }
    if(judgement)
    {
        operation
    }
    i = j;
}
return head;
```

将线性表内部满足某些条件的元素看成一个自然组，在遍历完每个组后做出判断，依据判断执行/不执行某操作；然后再让指针指向下一个区域