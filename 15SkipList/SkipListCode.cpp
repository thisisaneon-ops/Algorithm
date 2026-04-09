#include <iostream>
#include <random>
#include <ctime>
using namespace std;

struct Node
{
    Node(int val = 0)
        : val_(val), down_(nullptr), next_(nullptr)
    {
    }
    int val_;
    Node *down_;
    Node *next_;
};

struct headNode : public Node
{
    headNode(int level = 1)
        : level_(level)
    {
    }
    int level_;
};

class SkipList
{
public:
    SkipList()
    {
        head_ = new headNode();
    }
    ~SkipList()
    {
        Node *head = head_;
        while (head != nullptr)
        {
            Node *next = head->down_;
            while (head != nullptr)
            {
                Node *q = head->next_;
                delete head;
                head = q;
            }
            head = next;
        }
    }

public:
    bool find(int val)
    {
        Node *p = head_;
        while (p != nullptr)
        {
            while (p != nullptr)
            {
                Node *q = p->next_;
                if (q->val_ == val)
                {
                    return true;
                }
                else if (q->val_ < val)
                {
                    p = q;
                    q = q->next_;
                }
                else
                {
                    break;
                }
            }
            if (p->down_ == nullptr)
            {
                break;
            }
            p = p->down_;
        }
        return false;
    }
    void add(int val)
    {
        if (find(val))
        {
            return;
        }
        int level = getL();
        if (level > head_->level_)
        {
            level = head_->level_ + 1;
            headNode *newhead = new headNode(level);
            newhead->down_ = head_;
            head_ = newhead;
        }
        Node **Vertical = new Node *[level];
        for (int i = 0; i < level; i++)
        {
            Vertical[i] = new Node(val);
            if (i > 0)
            {
                Vertical[i]->down_ = Vertical[i - 1];
            }
        }
        Node **update = new Node *[level];
        Node *pre = head_;
        for (int i = head_->level_; i > level; i--)
        {
            pre = pre->down_;
        }
        for (int i = level - 1; i >= 0; i--)
        {
            Node *q = pre->next_;
            while (q != nullptr && q->val_ < val)
            {
                pre = q;
                q = q->next_;
            }
            update[i] = pre;
        }
        for (int i = 0; i < level; i++)
        {
            Vertical[i]->next_ = update[i]->next_;
            update[i]->next_ = Vertical[i];
        }
        delete[] Vertical;
        delete[] update;
    }
    void erase(int val)
    {
        Node *p = head_;
        while (p != nullptr)
        {
            Node *q = p->next_;
            while (q != nullptr)
            {
                if (q->val_ == val)
                {
                    p->next_ = q->next_;
                    delete q;
                    break;
                }
                else if (q->val_ < val)
                {
                    p = q;
                    q = q->next_;
                }
                else
                {
                    break;
                }
            }
            if (head_->next_ == nullptr)
            {
                Node *down = head_->down_;
                delete head_;
                head_ = static_cast<headNode *>(down);
            }
            if (p->down_ == nullptr)
            {
                break;
            }
            p = p->down_;
        }
    }

private:
    int getL()
    {
        int cnt = 1;
        while (rand() % 2 == 1)
        {
            cnt++;
        }
        return cnt;
    }

private:
    headNode *head_;
};

int main()
{
    return 0;
}