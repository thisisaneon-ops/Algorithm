/*
##### [155]最小栈

设计一个支持 `push` ，`pop` ，`top` 操作，并能在常数时间内检索到最小元素的栈。

实现 `MinStack` 类:

- `MinStack()` 初始化堆栈对象。
- `void push(int val)` 将元素val推入堆栈。
- `void pop()` 删除堆栈顶部的元素。
- `int top()` 获取堆栈顶部的元素。
- `int getMin()` 获取堆栈中的最小元素。

首先题目要求我们想到 O(1)的方法返回最小元素，而不能丢失栈FILO

最暴力的就是插入删除的时候直接维护栈内元素，让他有序，但这直接破坏了栈FILO的性质

其次就是不改变push 和 pop函数，保证栈FILO的性质，但是调用getMin()函数的时候一次遍历顺序栈，找到最小值min_val; 但是这就是O(N)时间复杂度了

那么我们想到重新开一个变量来保存min_val，根据push和pop实时更新，但是遇到的问题是 pop 出去后，一旦删掉了min_val对象，那么第二小的就找不到了。同理如果开两个变量，第三小也找不到。此时我们想到利用某种数据结构存储最小值( helper数组 ）

helper数组变量的作用

raw_array版本，效率最高，运行最快！
*/

class MinStack
{
private:
    int* helper_;
    int* arr_;
    int size_;
    int capa_;
    void expand()
    {
        int* brr_ = new int[capa_ * 2];
        int* newhelper_ = new int[capa_ * 2];
        for(int i = 0; i < size_; i++)
        {
            brr_[i] = arr_[i];
            newhelper_[i] = helper_[i];
        }
        delete[] helper_;
        delete[] arr_;
        arr_ = brr_;
        helper_ = newhelper_;
        capa_ *= 2;
    }
public:
   	MinStack(int capa = 5): capa_ (capa), size_ (0)
    {
        arr_ = new int[capa];
        helper_ = new int[capa];
    }
    ~MinStack()
    {
        delete[] arr_;
        delete[] helper_;
    }
    void push(const int& val)
    {
        if(size_ == capa_)
        {
            expand();
        }
        arr_[size_] = val;
        if(size_ == 0)
        {
            helper_[size_] = val;
        }
        else
        {
        	helper_[size_] = min(val, helper_[size_ - 1]);
        }
        size_++;
    }
    void pop()
    {
        if(size_ == 0)
        {
            throw std::invalid_argument("...");
        }
        size_--;
    }
    int top()
    {
        if(size_ == 0)
        {
            throw std::invalid_argument("...");
        }
        return arr_[size_ - 1];
    }
    int getMin()
    {
        return helper_[size_ - 1];
    }
};