#include"iostream"
#include"stdlib.h"
#include"iomanip"
#include"time.h"
using namespace std;
class HeapArray {
public: 
	HeapArray(int size = 10) :m_Size(0), m_Capacity(size){
		this->m_Array = new int[size];
	}
	~HeapArray() {
		if (m_Array != NULL) {
			delete[] m_Array;
			m_Array = NULL;
		}
	}
	//尾插
	void push_back(int val);
	//尾删
	void pop_back();
	//插入
	void insert(int pos, int val);
	//删除
	void erase(int pos);
	//查询
	int find(int val);
	//修改
	void update(int pos, int val);

	void showArray();
private:
	//扩容
	void expand(int newCapacity) {
		int* NewArray = new int[newCapacity];
		for (int i = 0; i < this->m_Size; i++) {
			NewArray[i] = this->m_Array[i];
		}
		delete[] m_Array;
		this->m_Array = NewArray;
		this->m_Capacity = newCapacity;
	}
	int* m_Array;  //数组首地址（数组名）
	int m_Capacity;     //数组容量 Capacity
	int m_Size;    //有效元素个数
};
void HeapArray::push_back(int val) {
	if (this->m_Size == this->m_Capacity) {
		expand(2 * this->m_Capacity);
	}
	this->m_Array[this->m_Size++] = val;
}
void HeapArray::pop_back() {
	if (this->m_Size == 0) {
		return;
	}
	m_Size--;
}
void HeapArray::insert(int pos, int val) {
	if (pos < 0 || pos > this->m_Size)
		return;
	if (this->m_Size == this->m_Capacity) {
		expand(2 * this->m_Capacity);
	}
	for (int i = this->m_Size; i > pos; i--) {
		this->m_Array[i] = this->m_Array[i - 1];
	}
	this->m_Array[pos] = val;
	this->m_Size++;
}
void HeapArray::erase(int pos) {
	if (pos < 0 || pos > this->m_Size - 1) {
		return;
	}
	for (int i = pos; i < this->m_Size - 1; i++) {
		this->m_Array[i] = this->m_Array[i + 1];
	}
	this->m_Size--;
}
int HeapArray::find(int val) {
	for (int i = 0; i < this->m_Size; i++) {
		if (this->m_Array[i] == val) {
			cout << "    该元素在 " << i << endl;;
			return i;
		}
	}
	return -1;
}
void HeapArray::update(int pos, int val) {
	if (pos < 0 || pos > this->m_Size - 1) {
		return;
	}
	this->m_Array[pos] = val;
}
void HeapArray::showArray() {
	for (int i = 0; i < this->m_Size; i++) {
		cout << setw(5) << this->m_Array[i];
	}
	cout << endl;
}
void test01() {
	HeapArray myarr;
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		myarr.push_back(rand() % 20 + 1);
	}
	myarr.showArray();
	myarr.pop_back();
	myarr.showArray();
	myarr.insert(3, 10);
	myarr.showArray();
	int a= myarr.find(1);
	myarr.erase(a);
	myarr.showArray();
	myarr.update(3, 10);
	myarr.showArray();
}
int main() {
	test01();
	return 0;
}
