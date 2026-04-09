#include <iostream>
#include <functional>
using namespace std;

class PriorityQueue
{
    using Comp = function<bool(int, int)>;

public:
    PriorityQueue(int capa)
        : capa_(capa), size_(0), comp_([](int a, int b) -> bool
                                       { return a > b; })
    {
        queue_ = new int[capa];
    }
    ~PriorityQueue()
    {
        delete[] queue_;
    }

public:
    void push(int val)
    {
        if (size_ == capa_)
        {
            expand();
        }
        queue_[size_] = val;
        if (size_ != 0)
        {
            sift_up(size_, val);
        }
        size_++;
    }
    void pop()
    {
        if (size_ == 0)
        {
            return;
        }
        swap(queue_[0], queue_[size_ - 1]);
        size_--;
        if (size_ > 1)
        {
            sift_down(0, queue_[0]);
        }
    }
    bool empty()
    {
        return size_ == 0;
    }
    int size()
    {
        return size_;
    }

private:
    void sift_up(int pos, int val)
    {
        int parent = (pos - 1) / 2;
        while (pos > 0)
        {
            if (comp_(queue_[pos], queue_[parent]))
            {
                queue_[pos] = queue_[parent];
                pos = parent;
            }
            else
            {
                break;
            }
        }
        queue_[pos] = val;
    }
    void sift_down(int pos, int val)
    {
        while (pos <= size_ / 2 - 1)
        {
            int child = pos * 2 + 1;
            if (child + 1 < size_ && comp_(queue_[child + 1], queue_[child]))
            {
                child = child + 1;
            }
            if (comp_(queue_[child], queue_[pos]))
            {
                queue_[pos] = queue_[child];
                pos = child;
            }
            else
            {
                break;
            }
        }
        queue_[pos] = val;
    }

private:
    void expand()
    {
        int *newQueue = new int[capa_ * 2];
        for (int i = 0; i < size_; i++)
        {
            newQueue[i] = queue_[i];
        }
        delete[] queue_;
        queue_ = newQueue;
        capa_ *= 2;
    }
    int *queue_;
    int size_;
    int capa_;
    Comp comp_;
};

int main()
{

    return 0;
}