// 单链表逆置

// 请借助栈实现单链表的逆置运算

// 个人没看出有什么更好的用栈的方式，感觉没什么实际意义，算法没人这么干！（刚入门可以），因为三指针迭代和头插显然更好，都是原地修改！

// 借助此题巩固对栈LIFO的理解即可，不必深究

// 因为利用栈，就完全没有利用以及避开了next指针域修改可能带来的优势以及对断链，空指针访问，没有记录丢失节点等指针操作问题的思考！

ListNode* reverselist(ListNode* head)  // 我们都默认没有哨兵节点！
{
    if(head == nullptr || head->next == nullptr)
    {
        return head;
    }
    stack<ListNode*>nodes;
    using Node = ListNode;  // 太长了我不想写ListNode
    Node* p = head;
    while(p != nullptr)
    {
        Node* next = p->next;
        nodes.push(p);
        p = next;
    }
    // 栈初始化完毕，下面开始弹出
    Node* newhead = nodes.top();  // 头节点
    nodes.pop();  // 弹出，准备进入循环！
    Node* tail = newhead;  // 初始化tail时刻指向最后一个有效位置，便于连接新节点！
    while(!nodes.empty())
    {
        Node* top = nodes.top();
        tail->next = top;
        tail = top;  // tail移动到最新位置
        nodes.pop();
    }
    // 最后出来的时候，链表应该空了，但是最后一个节点的指针域没有置空
    tail->next = nullptr;  // 其实和删除重复元素II的最后一步很像！必须断链！否则成环！
    return newhead;
}