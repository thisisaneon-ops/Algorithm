#include<iostream>
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<algorithm>
#include<stack>
#include<unordered_map>
using namespace std;

/*
1. 导论
算法的五大性质：有穷性，确定性，可行性，输入(可以没有)，输出(必须至少一个)
算法设计的五大性质：正确性，可读性，鲁棒性，高效性
*/

// 1. 数组
/*
* 最基本的：底层实现(增删改查扩容打印)
*/
// 快速排序
// 挖坑法
void quickSort1(vector<int>&arr, int i, int j) {
	if (i >= j) {
		return;
	}
	int left = i;
	int right = j;
	int pivot = arr[left];
	while (left < right) {
		while (left < right && arr[right] >= pivot) {
			right--;
		}
		if (left < right) {
			arr[left] = arr[right];
			left++;
		}
		while (left < right && arr[left] <= pivot) {
			left++;
		}
		if (left < right){
			arr[right] = arr[left];
			right--;
		}
	}
	arr[left] = pivot;  // 出来的时候left和right是同一个
	quickSort1(arr, i, left);
	quickSort1(arr, left + 1, j);
}
// Hoare
void Hoare(vector<int>& arr, int i, int j) {
	if (i >= j) {
		return;
	}
	// 注意，你用do-while开头就必须从非法位置开始，否则会漏掉第一个和最后一个元素！
	int left = i - 1;  
	int right = j + 1;
	int pivot = arr[left];
	while (true) {
		do { left++; } while (arr[left] < pivot);
		do { right--; } while (arr[right] > pivot);
		if (left > right) { break; }
		swap(arr[left], arr[right]);
	}
	Hoare(arr, i, right);
	Hoare(arr, right + 1, j);
}

// 归并排序
void merge(vector<int>& arr, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	vector<int>tmp;
	while (i <= mid && j <= right) {
		if (arr[i] < arr[j]) {
			tmp.push_back(arr[i++]);
		}
		else {
			tmp.push_back(arr[j++]);
		}
	}
	while (i <= mid) {
		tmp.push_back(arr[i++]);
	}
	while (j <= right) {
		tmp.push_back(arr[j++]);
	}
	for (int k = 0; k < right - left + 1; k++) {
		arr[left + k] = tmp[k];
	}
}
void mergeSort(vector<int>& arr, int left, int right) {
	if (left >= right) {
		return;
	}
	int mid = left + (right - left) / 2;
	mergeSort(arr, left, mid);
	mergeSort(arr, mid + 1, right);
	merge(arr, left, mid, right);
}

// 去重及其变体
// 基础去重
int removeDuplicates(vector<int>& arr) {
	sort(arr.begin(), arr.end());
	int read = 1;
	int write = 0;
	const int n = arr.size();
	while (read < n) {
		if (arr[read] != arr[write]) {
			arr[++write] = arr[read];
		}
		read++;
	}
	return write + 1;  // 返回有效元素个数
}
// 可保留两个
int removeDuplicatesII(vector<int>& arr) {
	if (arr.size() == 0) {
		return 0;
	}
	const int n = arr.size();
	int cnt = 1;
	int read = 1;
	int write = 0;
	while (read < n) {
		if (arr[read] == arr[write]) {
			if (cnt < 2) {
				arr[++write] = arr[read];
				cnt++;
			}
		}
		else {
			cnt = 1;
			arr[++write] = arr[read];
		}
		read++;
	}
	return write + 1;
}

// X数之和系列
// 两数之和1 哈希表
vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int>m;
	const int n = nums.size();
	for (int i = 0; i < n; i++) {
		int remain = target - nums[i];
		if (m.find(remain) != m.end()) {
			return { i, m[remain] };
		}
		m[nums[i]] = i;
	}
	return {};
}
// 两数之和2
// nums是已排序的数组（原题返回的是 1-based）
vector<int> twoSum(vector<int>& nums, int target) {
	const int n = nums.size();
	int left = 0;
	int right = n - 1;
	while (left < right) {
		int curSum = nums[left] + nums[right];
		if (curSum == target) { return { left, right }; }
		else if (curSum > target) { right--; }
		else { left++; }
	}
	return {};
}
// 三数之和
// 注意是返回数字  原题是0 + 不止一组解 + 去重
vector<vector<int>> threeSum(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end());
	const int n = nums.size();
	vector<vector<int>>ans;
	for (int i = 0; i < n - 2; i++) {
		if (i != 0 && nums[i] == nums[i - 1]) {
			continue;
		}
		int curVal = nums[i];
		int remain2 = target - curVal;
		int left = i + 1;
		int right = n - 1;
		while (left < right) {
			int curSum = nums[left] + nums[right];
			if (curSum == remain2) { 
				ans.push_back({ curVal, nums[left], nums[right] });
				do { left++; } while (left < right && nums[left] == nums[left - 1]);
				do { right--; } while (left < right && nums[right] == nums[right + 1]);
			}
			else if (curSum > remain2) { right--; }
			else { left++; }
		}
	}
	return ans;
}

// 成水最多的容器
int maxVolume(vector<int>& heights) {
	const int  n = heights.size();
	int left = 0;
	int right = n - 1;
	int maxVolume = 0;
	while (left < right) {
		int height = min(heights[left], heights[right]);
		int width = right - left;
		int curVolume = height * width;
		maxVolume = max(maxVolume, curVolume);
		if (heights[left] < heights[right]) {
			left++;
		}
		else {
			right--;
		}
	}
	return maxVolume;
}

// 滑动窗口
// 找无重复的最长字串
int LongestSubString(string s) {
	if (s.size() == 0) { return 0; }
	vector<int>bucket(128, 0);
	const int n = s.size();
	int write = 0;
	int read = 1;
	bucket[s[write]]++;
	int len = 1;
	int finallen = 1;
	while (read < n) {
		if (bucket[s[read]] == 0) {
			bucket[s[read]]++;
			len++;
			finallen = max(finallen, len);
		}
		else {
			while (bucket[s[read]] != 0) {
				bucket[s[write]]--;
				len--;
				write++;
			}
			bucket[s[read]]++;
			len++;
			finallen = max(finallen, len);
		}
		read++;
	}
	return finallen;
}

// 分区扫描
// 保留数组只出现一次的元素
int rareElements(vector<int>& arr) {
	if (arr.size() <= 1) {
		return arr.size();
	}
	const int n = arr.size();
	int i = 0;
	int write = 0;
	while (i < n) {
		int j = i;
		do { j++; } while (j < n && arr[j] == arr[i]);
		if (i + 1 == j) {
			arr[write++] = arr[i];
		}
		i = j;
	}
	return write;
}

// 2. 链表
// 基本实现(带哨兵)
struct ListNode {
	ListNode(int data = 0)
		: data(data), next(nullptr)
	{
	}
	int data;
	ListNode* next;
};
class List {
public:
	List()
		: head(new ListNode(0))
	{}
	~List() {
		while (head != nullptr) {
			ListNode* node = head;
			head = head->next;
			delete node;
		}
	}
public:
	void push_back(int val) {
		ListNode* tail = head;
		while (tail->next != nullptr) {
			tail = tail->next;
		}
		tail->next = new ListNode(val);
	}
	void push_front(int val) {
		ListNode* next = head->next;
		ListNode* node = new ListNode(val);
		head->next = node;
		node->next = next;
	}
	void pop_back() {
		if (head->next == nullptr) {
			return;
		}
		ListNode* tail = head->next;
		ListNode* pre = head;
		while (tail->next != nullptr) {
			pre = tail;
			tail = tail->next;
		}
		pre->next = nullptr;
		delete tail;
	}
	void pop_front() {
		if (head->next == nullptr) {
			return;
		}
		ListNode* del = head->next;
		ListNode* next = del->next;
		head->next = next;
		delete del;
	}
private:
	ListNode* head;
};

// 找中点(无头结点, 偶数找偏左的那个)
ListNode* midNodeleft(ListNode* head) {
	ListNode* fast = head->next;
	ListNode* slow = head;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

ListNode* midNoderight(ListNode* head) {
	ListNode* fast = head;
	ListNode* slow = head;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}
// 判环
bool IsCycle(ListNode* head) {
	if (head == nullptr) {
		throw std::invalid_argument("invalid headptr");
	}
	ListNode* fast = head;
	ListNode* slow = head;
	do {
		fast = fast->next->next;
		slow = slow->next;
	} while (fast != nullptr && fast->next != nullptr && fast != slow);
	if (fast == nullptr || fast->next == nullptr) { return false; }
	return true;
}
// 找入口
ListNode* entrance(ListNode* head) {
	if (head == nullptr) {
		throw std::invalid_argument("invalid headptr");
	}
	ListNode* fast = head;
	ListNode* slow = head;
	do {
		fast = fast->next->next;
		slow = slow->next;
	} while (fast != nullptr && fast->next != nullptr && fast != slow);
	if (fast == nullptr || fast->next == nullptr) { return nullptr; }
	fast = head;
	while (fast != slow) {
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
// 倒数第K
ListNode* lastKNode(ListNode* head, int k) {
	ListNode* slow = head;
	ListNode* fast = head;
	for (int i = 0; i < k; i++){
		if (fast == nullptr) {
			throw std::invalid_argument("invalid k");
		}
		fast = fast->next;
	}
	while (fast != nullptr) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}

// 反转 + 部分反转
// 三指针迭代实现链表反转
ListNode* reverse(ListNode* head) {
	ListNode* prev = nullptr;
	ListNode* node = head;
	while (node != nullptr) {
		ListNode* next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}
	return prev;
}
// 部分反转
ListNode* reversePart(ListNode* head, int i, int j) {
	ListNode* dummy = new ListNode();
	dummy->next = head;
	if (head == nullptr) { return nullptr; }
	if (i < 0 || i > j) { throw std::invalid_argument("invalid index"); }
	if (i == j) { return head; }
	// 先找left前一个和right
	ListNode* leftprev = dummy;
	ListNode* right = dummy;
	for (int k = 0; k < i; k++) { 
		if (leftprev == nullptr) { throw std::invalid_argument("invalid edge"); }
		leftprev = leftprev->next;
	}
	for (int k = 0; k < j; k++) { 
		if (right == nullptr) { throw std::invalid_argument("invalid edge"); }
		right = right->next; 
	}
	// 下面开始断链
	ListNode* left = leftprev->next;
	ListNode* rightafter = right->next;
	left->next = nullptr;
	right->next = nullptr;
	// 反转，代码复用
	ListNode* newLeft = reverse(left);
	ListNode* newRight = newLeft;
	while (newRight->next != nullptr) {
		newRight = newRight->next;
	}
	// 重连
	leftprev->next = newLeft;
	newRight->next = rightafter;
	ListNode* newhead = dummy->next;
	delete dummy;
	return newhead;
}
// 排序(插入排序 + 归并排序)
ListNode* InsertionSort(ListNode* head) {
	ListNode* dummy = new ListNode();
	ListNode* node = head;
	while (node != nullptr) {
		ListNode* prev = dummy;
		ListNode* cur = dummy->next;
		while (cur != nullptr && cur->data < node->data) {
			prev = cur;
			cur = cur->next;
		}
		prev->next = node;
		ListNode* next = node->next;
		node->next = cur;
		node = next;
	}
	ListNode* ret = dummy->next;
	delete dummy;
	return ret;
}

ListNode* merge(ListNode* left, ListNode* right) {
	ListNode* dummy = new ListNode();
	ListNode* tail = dummy;
	while (left != nullptr && right != nullptr) {
		if (left->data < right->data) {
			tail->next = left;
			tail = left;
			left = left->next;
		}
		else {
			tail->next = right;
			tail = right;
			right = right->next;
		}
	}
	while (left != nullptr) {
		tail->next = left;
		tail = left;
		left = left->next;
	}
	while (right != nullptr) {
		tail->next = right;
		tail = right;
		right = right->next;
	}
	ListNode* ret = dummy->next;
	delete dummy;
	return ret;
}
ListNode* mergeSort(ListNode* head) {
	if (head == nullptr) {
		return;
	}
	ListNode* left = head;
	ListNode* mid = midNodeleft(head);
	ListNode* right = mid->next;
	mid->next = nullptr;
	ListNode* newleft = mergeSort(left);
	ListNode* newright = mergeSort(right);
	return merge(newleft, newright);
}

// 回文链表
// 思路就是找到中间，反转后面，逐一比对，这里不再赘述，手写略

// 稀有节点
ListNode* keepRareElements(ListNode* head) {
	ListNode* dummy = new ListNode();
	ListNode* tail = dummy;
	ListNode* i = head;
	while (i != nullptr) {
		ListNode* j = i->next;
		while (j != nullptr && j->data == i->data) { j = j->next; }
		if (j == i->next) {
			tail->next = i;
			tail = i;
			tail->next = nullptr;
		}
		i = j;
	}
	tail->next = nullptr;  // 其实是冗余代码，但是出于防御性
	return dummy->next;
}

// 3. 栈和队列
// 栈底层的基本实现：1. 顺序栈  2. 链式栈
// 栈的应用
// 1. 基础存储
// 逆波兰表达式求值 / 中缀转逆波兰
// 求值
int NPLCalculator(vector<string>& tokens) {
	stack<int>s;
	const int n = tokens.size();
	for (int i = 0; i < n; i++) {
		auto cur = tokens[i];
		if (cur == "+" || cur == "-" || cur == "*" || cur == "/") {
			if (s.empty()) { throw std::invalid_argument("invalid tokens"); }
			int right = s.top();
			s.pop();
			if (s.empty()) { throw std::invalid_argument("invalid tokens"); }
			int left = s.top();
			if (cur == "+") { s.push(left + right); }
			else if (cur == "-") { s.push(left - right); }
			else if (cur == "*") { s.push(left * right); }
			else { s.push(left / right); }
		}
		else {
			int num = stoi(cur);
			s.push(num);
		}
	}
	if (s.size() != 1) { throw std::invalid_argument("invalid tokens"); }
	return s.top();
}

int Priority(string s) {
	if (s == "*" || s == "/") { return 2; }
	if (s == "+" || s == "-") { return 1; }
	return 0;  // ( ) 特殊标记为0
}
string ToNPL(vector<string>& tokens) {
	string ret;
	stack<string>ops;  // 符号栈
	// 原则：比较符号优先级, 更高级的直接入栈, 平级或更低级的等其他的先出栈再入栈, 特殊处理()
	const int n = tokens.size();
	for (int i = 0; i < n; i++) {
		auto op = tokens[i];
		if (op == "+" || op == "-" || op == "*" || op == "/" || op == "(" || op == ")") {
			if (op == "(") {
				ops.push("(");
			}
			else if (op == ")") {
				while (!ops.empty() && ops.top() != "(") {
					auto top = ops.top();
					ret += (top + " ");
					ops.pop();
				}
				if (ops.empty()) { throw std::invalid_argument("wrong string"); }
				ops.pop();
			}
			else {
				while (!ops.empty() && Priority(ops.top()) >= Priority(op)) {
					auto top = ops.top();
					ret += (top + " ");
					ops.pop();
				}
				ops.push(op);
			}
		}
		else {
			int num = stoi(op);
			ret += (num + " ");
		}
	}
	while (!ops.empty()) {
		ret += (ops.top() + " ");
		ops.pop();
	}
	return ret;
}
// 退格字符串比较
bool isSameString(string a, string b) {
	stack<char>s1;
	stack <char>s2;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == '#') {
			if (!s1.empty()) { s1.pop(); }
		}
		else { s1.push(a[i]); }
	}
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == '#') {
			if (!s2.empty()) { s2.pop(); }
		}
		else { s2.push(b[i]); }
	}
	if (s1.size() != s2.size()) { return false; }
	while (!s1.empty() && !s2.empty()) {
		if (s1.top() != s2.top()) { return false; }
		s1.pop();  s2.pop();
	}
	return true;
}
// 进制转化(除留余数法)
string Transformer(int num, int n) {
	if (num == 0) { return 0; }
	if (n < 2 || n > 16) { throw std::invalid_argument("unsupported transform"); }
	if (n == 10) { return to_string(num); }
	string seeds = "0123456789ABCDEF";
	string s;
	while (num != 0) {
		int remainder = num % n;
		num /= n;
		auto cur = seeds[remainder];
		s += cur;
	}
	reverse(s.begin(), s.end());
	return s;
}

// 2. 括号匹配
bool isValidQuotations(string s) {
	stack<char>ops;
	const int n = s.size();
	for (int i = 0; i < n; i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			ops.push(s[i]);
		}
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
			if (ops.empty()) { return false; }
			auto top = ops.top();
			if (s[i] == ')' && top != '(') { return false; }
			if (s[i] == ']' && top != '[') { return false; }
			if (s[i] == '}' && top != '{') { return false; }
			ops.pop();
		}
		else { return false; }
	}
	return ops.empty();
}

int addValid(string s) {
	stack<char>ops;
	const int n = s.size();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			ops.push(s[i]);
		}
		else if (s[i] == ')' || s[i] == ']' || s[i] == '}') {
			if (ops.empty()) { cnt++; }
			else
			{
				auto top = ops.top();
				if (s[i] == ')' && top != '(') { cnt++; }
				if (s[i] == ']' && top != '[') { cnt++; }
				if (s[i] == '}' && top != '{') { cnt++; }
				else { ops.pop(); }
			}
		}
		else { return -999; }
	}
	return cnt + ops.size();
}
// 最长的连续括号(存储索引)
int LongestQuotation(string& s) {
	stack<int>ops;
	int longest = 0;
	const int n = s.size();
	ops.push(-1);  // 用哨兵
	for (int i = 0; i < n; i++) {
		if (s[i] == '(') { ops.push(i); }
		else {
			// 如果是右括号，先抓人(机制保证了一定能抓到！)
			// 找到以后，取新栈顶，计算长度，更新最大长度
			ops.pop();
			if (ops.empty()) { ops.push(i); }
			else {
				int left = ops.top();
				int curLen = i - left;
				longest = max(longest, curLen);
			}
		}
	}
	return longest;
}
// 括号分数
int quotationScore(string& s) {
	stack<int>scores;
	const int n = s.size();
	scores.push(0);
	for (int i = 0; i < n; i++) {
		auto quo = s[i];
		if (quo == '(') {
			scores.push(0);  // 新开一层
		}
		else {  // 验收结果
			if (scores.empty()) { throw std::invalid_argument("invalid input"); }
			auto top = scores.top();
			scores.pop();
			if (top == 0) { scores.top() += 1; }
			else { scores.top() += (top * 2); }
		}
	}
	return scores.top();
}
// 3. 辅助栈(最小栈模拟)
class MinStack {
private:
	int* array;
	int* stack;
	int size;
	int capa;
	void expand() {
		int* newarray = new int[capa * 2];
		int* newstack = new int[capa * 2];
		for (int i = 0; i < size; i++) {
			newarray[i] = array[i];
			newstack[i] = stack[i];
		}
		delete[] array;
		delete[] stack;
		array = newarray;
		stack = newstack;
		capa *= 2;
	}
public:
	MinStack(int capa = 5)
		: array(new int[capa])
		, stack(new int[capa])
		, size(0)
		, capa(capa)
	{}
	void push(int val) {
		if (size == capa) { expand(); }
		array[size] = val;
		if (size == 0) { stack[size] = val; }
		else { stack[size] = min(val, stack[size - 1]); }
		size++;
	}
	void pop() {
		size--;
	}
	int top() {
		if (size == 0) { throw std::invalid_argument("invalid requirement"); }
		return array[size - 1];
	}
	int getMin() {
		if (size == 0) { throw std::invalid_argument("invalid requirement"); }
		return stack[size - 1];
	}
};

// 4. 单调栈(★★★难)

// 5. 串
// BF暴力搜索
int BF(string s, string t) {
	const int m = s.size();
	const int n = t.size();
	if (m < n) { return -1; }
	int i = 0;   int j = 0;
	while (i < m) {
		if (s[i] == t[j]) {
			i++;  j++;
			if (j == n) { return i - j; }
		}
		else {
			j = 0;
			i = i - j + 1;
		}
	}
	return -1;
}
// KMP搜索
int* getNext(string t) {
	const int n = t.size();
	int j = 0;  int k = -1;
	int* next = new int[n];
	next[j] = k;
	while (j < n - 1) {
		if (k == -1 || t[j] == t[k]) {
			j++;  k++;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
	return next;
}
int KMP(string s, string t) {
	const int m = s.size();
	const int n = t.size();
	if (m < n) { return -1; }
	int i = 0;   int j = 0;
	int* next = getNext(t);
	while (i < m) {
		if (j == -1 || s[i] == t[j]) {
			i++;  j++;
			if (j == n) { return i - j; }
		}
		else {
			j = next[j];
		}
	}
	return -1;
}
// 串的练习(比较杂乱，考试估计考的可能性不大)

// 6. 多维数组、稀疏矩阵和广义表

int main() {

	return 0;
}