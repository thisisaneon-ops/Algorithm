/*
##### [150]逆波兰求值

考察栈的基本操作

逆波兰表达式，也称作后缀表达式，以不含括号也仍然没有计算歧义为显著特点；

测试案例情况：

数组内部是string类型，每一个string对象可能是操作符也可能是 -200 ~ 200 之间的一个数

保证所有的输入都是合法逆波兰表达式，不会出现例如 1 + 2 4 3  /  1 4  6  7 * 这种错误的输入
*/

int NPLCalculator(vector<string>& tokens)  // 这里假定所有逆波兰表达式都合法
{
    stack<int>s;
    for(int i = 0; i < tokens.size(); i++)
    {
        string cur = tokens[i];
        if(cur == "+" || cur == "-" || cur == "*" || cur == "/")
        {
            int right = s.top();
            s.pop();
            int left = s.top();
            s.pop();
            int newTop = 0;
            if(cur == "+")
            {
                newTop = left + right;
            }
            else if(cur == "-")
            {
                newTop = left - right;
            }
            else if(cur == "*")
            {
                newTop = left * right;
            }
            else
            {
                newTop = left / right;  // 要不要乘1.0 看具体要求，这里不实现了，因为返回值是int
            }
            s.push(newTop);
        }
        else
        {
            int curVal = stoi(cur);
            s.push(curVal);
        }
    }
    return s.top();  // 返回栈顶元素即可
}