// 1.2 中缀转逆波兰

// 注意不要忘记 (的priority以及最后残留在stack内部的数据
// 规则相对复杂：
// ( 直接入栈  ) 向下找直到第一个 ( 
// + - * / 前两者为1Level 后两者为2Level  
// 1如果 CurLevel > TopLevel: 直接压栈
// 2如果 CurLevel <= TopLevel: 等，直到 变成情况1
// 注意除了）外不允许弹出（
int Priority(string i)
{
	if (i == "+" || i == "-")
	{
		return 1;
	}
	else if(i == "*" || i == "/")
	{
		return 2;
	}
	else
	{
		return -1;
	}
}
bool judgePrior(string cur, string top)
{
	int CurLevel = Priority(cur);
	int TopLevel = Priority(top);
	return CurLevel > TopLevel;
}
string NPLTransform(vector<string>& tokens)
{
	string NPL;
	stack<string>ops;
	for(int i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/" || tokens[i] == "(" || tokens[i] == ")")
		{
			if (tokens[i] == "(")
			{
				ops.push("(");
			}
			else if (tokens[i] == ")")
			{
				while (!ops.empty() && ops.top() != "(")
				{
					string top = ops.top();
					NPL += top;
					NPL += " ";
					ops.pop();
				}
				// 出循环时 ops.top() == '(', 要弹出
				ops.pop();
			}
			else
			{
				// ops.top() 是'(' 和 ')'单独处理
				while (!ops.empty() && !judgePrior(tokens[i], ops.top()))
				{
					string top = ops.top();
					NPL += top;
					NPL += " ";
					ops.pop();
				}
				ops.push(tokens[i]);
			}
		}
		else  // 数字直接抄
		{
			NPL += tokens[i];
			NPL += " ";
		}
	}
	// 栈内还有剩余元素
	while (!ops.empty())
	{
		NPL += ops.top();
		NPL += " ";
		ops.pop();
	}
	return NPL;
}
