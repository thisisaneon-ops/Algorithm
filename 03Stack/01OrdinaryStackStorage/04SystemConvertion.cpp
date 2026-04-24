// 1.3 进制转化

// 注意单独处理n <= 0
string Transformer(int n, const int& base)
{
	if (n <= 0)
	{
		return "illegal";
	}
	if (base < 2 || base > 16)
	{
		cout << "非法基数" << endl;
		return "HelloWorld";
	}
	stack<int>s;
	// 利用除留余数法
	while (n != 0)
	{
		int remainder = n % base;
		n /= base;
		s.push(remainder);
	}
	string seeds = "0123456789ABCDEF";
	string ret;
	while (!s.empty())
	{
		char top = seeds[s.top()];
		ret += top;
		s.pop();
	}
	return ret;
}

