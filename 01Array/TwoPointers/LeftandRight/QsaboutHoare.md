如果你能回答以下几个，就说明你完全理解Hoare算法的本质了！

1. 为什么 i= j 也要return 不能是i > j  --return么
2. 在do-while里，为什么不需要单独手动移动 left 和 right？while里却需要？
3. 为什么while循环的条件是 <  > pivot？不可以是 <= pivot  >= pivot么？
4. 出循环时 left 和 right可能是什么关系？可能不相邻间隔很多个位置么？
5. 整个循环的过程中有什么不变的性质？
6. 为什么最后划分区间的时候需要我们以 right // right + 1做划分？

双指针交换法，理解难度大

关心的就是中间的间隙大小

left只有可能在出循环时在right右边一个或者就是和right重合
