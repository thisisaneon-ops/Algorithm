#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

class SparseMatrix {
private:
	struct Triple {
		Triple(int row = 0, int col = 0, int val = 0)
			: row(row)
			, col(col)
			, val(val)
		{
		}
		int row;
		int col;
		int val;
		bool operator==(const Triple& triple) {
			return this->row == triple.row && this->col == triple.col && this->val == triple.val;
		}
	};
	int rows;
	int cols;
	vector<Triple>tripleArray;
private:
	struct RowFirst {
	public:
		// 定义仿函数保证行优先，返回a优先级更高
		bool operator()(const Triple& a, const Triple& b){
			if (a.row < b.row) {
				return true;
			}
			else if (a.row == b.row) {
				return a.col < b.col;
			}
			else {
				return false;
			}
		}
	};
	void readFile(const string& FilePath) {
		ifstream pf(FilePath);
		if (!pf.is_open()) {
			cout << "File Not Found!" << endl;
			return;
		}
		// 下面开始逐行读文件，构造Triple数组
		string unprocessed_triple;
		while (getline(pf, unprocessed_triple, '\n')) {
			stringstream ss(unprocessed_triple);
			string num;
			vector<int>v;
			while (getline(ss, num, ',')) {
				int number = stoi(num);
				v.push_back(number);
			}
			Triple triple(v[0], v[1], v[2]);
			tripleArray.push_back(triple);
		}
	}
public:
	SparseMatrix(int rows, int cols, string FilePath)
		: rows(rows)
		, cols(cols)
	{
		readFile(FilePath);
		sort(tripleArray.begin(), tripleArray.end(), RowFirst());
	}
	SparseMatrix(int rows, int cols)
		: rows(rows)
		, cols(cols)
	{	}
	~SparseMatrix() {	}
public:
	// 打印三元组
	void print() {
		for (auto& u : tripleArray) {
			cout << "( " << u.row << "," << u.col << "," << u.val << " )" << " ";
		}
		cout << endl;
	}
	// 修改值
	bool modify(const int& row, const int& col, const int& val) {
		auto it = find_if(tripleArray.begin(), tripleArray.end(), [row, col](const Triple& triple)->bool {return triple.row == row && triple.col == col; });  // 构造匿名对象比较
		// 没找到，直接创建新元素
		if (it == tripleArray.end()) {
			Triple newTriple(row, col, val);
			tripleArray.push_back(newTriple);
			sort(tripleArray.begin(), tripleArray.end(), RowFirst());
			return true;
		}
		// 找到了，看看值如果不相等则修改
		else {
			if (it->val == val) {
				cout << "same value, refuse to modify" << endl;
				return false;
			}
			else {
				// 如果等于0，删除这个节点，vals--
				if (val == 0) {
					it = tripleArray.erase(it);  // 接收下一个值，避免不必要的麻烦
					return true;
				}
				// 如果不等与0，直接修改
				else {
					it->val = val;
					return true;
				}
			}
		}
	}
	// 加法
	SparseMatrix Add(const SparseMatrix& matrix) {
		if (!isSameShape(matrix)) {
			cout << "Two Matrix do not share the same shape" << endl;
			throw invalid_argument("Calculation error");
		}
		// 采用归并思想
		SparseMatrix newMatrix(this->rows, this->cols);
		int i = 0;
		int j = 0;
		int m = this->tripleArray.size();
		int n = matrix.tripleArray.size();
		while (i < m && j < n) {
			auto& Triplei = this->tripleArray[i];
			auto& Triplej = matrix.tripleArray[j];
			// i优先级高
			if ((Triplei.row < Triplej.row) || (Triplei.row == Triplej.row) && (Triplei.col < Triplej.col)) {
				newMatrix.tripleArray.push_back(Triple(Triplei.row, Triplei.col, Triplei.val));
				i++;
			}
			// 优先级相等
			else if ((Triplei.row == Triplej.row) && (Triplei.col == Triplej.col)) {
				if (Triplei.val + Triplej.val != 0) {
					newMatrix.tripleArray.push_back(Triple(Triplei.row, Triplei.col, Triplei.val + Triplej.val));
				}
				i++;
				j++;
			}
			// j优先级高
			else {
				newMatrix.tripleArray.push_back(Triple(Triplej.row, Triplej.col, Triplej.val));
				j++;
			}
		}
		while (i < m) {
			auto& Triplei = this->tripleArray[i];
			newMatrix.tripleArray.push_back(Triple(Triplei.row, Triplei.col, Triplei.val));
			i++;
		}
		while (j < n) {
			auto& Triplej = matrix.tripleArray[j];
			newMatrix.tripleArray.push_back(Triple(Triplej.row, Triplej.col, Triplej.val));
			j++;
		}
		return newMatrix;
	}
	// 减法
	SparseMatrix Subtract(const SparseMatrix& matrix) {
		if (!isSameShape(matrix)) {
			cout << "Two Matrix do not share the same shape" << endl;
			throw invalid_argument("Calculation error");
		}
		// 采用归并思想
		SparseMatrix newMatrix(this->rows, this->cols);
		int i = 0;
		int j = 0;
		int m = this->tripleArray.size();
		int n = matrix.tripleArray.size();
		while (i < m && j < n) {
			auto& Triplei = this->tripleArray[i];
			auto& Triplej = matrix.tripleArray[j];
			// i优先级高
			if ((Triplei.row < Triplej.row) || (Triplei.row == Triplej.row) && (Triplei.col < Triplej.col)) {
				newMatrix.tripleArray.push_back(Triple(Triplei.row, Triplei.col, Triplei.val));
				i++;
			}
			// 优先级相等
			else if ((Triplei.row == Triplej.row) && (Triplei.col == Triplej.col)) {
				if (Triplei.val - Triplej.val != 0) {
					newMatrix.tripleArray.push_back(Triple(Triplei.row, Triplei.col, Triplei.val - Triplej.val));
				}
				i++;
				j++;
			}
			// j优先级高
			else {
				newMatrix.tripleArray.push_back(Triple(Triplej.row, Triplej.col, -Triplej.val));
				j++;
			}
		}
		while (i < m) {
			auto& Triplei = this->tripleArray[i];
			newMatrix.tripleArray.push_back(Triple(Triplei.row, Triplei.col, Triplei.val));
			i++;
		}
		while (j < n) {
			auto& Triplej = matrix.tripleArray[j];
			newMatrix.tripleArray.push_back(Triple(Triplej.row, Triplej.col, -Triplej.val));
			j++;
		}
		return newMatrix;
	}
	// 第一种想法，暴力插入，再rowfirst排序
	SparseMatrix Transpose() {
		SparseMatrix matrix(this->cols, this->rows);
		for (auto& u : this->tripleArray) {
			Triple tmp(u.col, u.row, u.val);
			matrix.tripleArray.push_back(tmp);
		}
		sort(matrix.tripleArray.begin(), matrix.tripleArray.end(), RowFirst());
		return matrix;
	}
	// 第二种想法，辅助数组
	SparseMatrix QuickTranspose() {
		// 初始化矩阵
		SparseMatrix newMatrix(this->cols, this->rows);
		newMatrix.tripleArray.resize(this->tripleArray.size());
		// 初始化 ocpPerCol 记录每列实际占用的格子数
		vector<int>ocpPerCol(cols, 0);
		// 线性遍历
		for (auto& u : this->tripleArray) {
			ocpPerCol[u.col]++;
		}
		// 统计得到每列实际三元组数
		// 初始化 colFirstIdx数组，初始化每列第一索引数组，标记每列当前元素应填写数据在newMatrix三元组数组实际位置
		vector<int>colFirstIdx(cols, 0);  // 不确定第一个有效位置是谁，都初始化为0
		for (int i = 1; i < ocpPerCol.size(); i++) {
			colFirstIdx[i] = colFirstIdx[i - 1] + ocpPerCol[i - 1];  // 当前列在新三元组数组起始位置的映射 = 上一列的映射 + 上一列的元素个数
		}
		// 初始化完毕，开始对照 this->tripleArray找元素，在colFirstIdx列在新矩阵对应行的位置，把数据填进去
		for (auto& u : this->tripleArray) {
			// 元素所在列
			int curCol = u.col;
			// 所在列对应映射位置
			int curRefPos = colFirstIdx[curCol];
			// 填写元素
			auto& obj = newMatrix.tripleArray[curRefPos];
			obj.row = u.col;
			obj.col = u.row;
			obj.val = u.val;
			// 将当前列有效位置后移，为下一个元素插入做准备
			colFirstIdx[curCol]++;
		}
		return newMatrix;
	}
	// 打印所有
	void printall() {
		// 让指针指向tripleArray的第一个元素，如果匹配，就打印val，不匹配就等到匹配再打印
		int idx = 0;
		for (int i = 1; i <= this->rows; i++) {
			for (int j = 1; j <= this->cols; j++) {
				// 匹配：当前位置存在有效非零元素
				// 小心两个问题：1. 记得查idx，越界就不要访问了 2. 注意 i j都是从1开始，三元组是1-based规则
				if (idx < tripleArray.size() && 
					i == tripleArray[idx].row && j == tripleArray[idx].col) {
					cout << tripleArray[idx].val << " ";
					idx++;
				}
				// 不匹配：当前位置为0
				else {
					cout << "0 ";
				}
			}
			cout << endl;
		}
		cout << endl;
		return;
	}
	// 乘法
	SparseMatrix Multiply(const SparseMatrix& matrix) {
		if (!isNesh(matrix)) {
			throw invalid_argument("Wrong input");
		}
		SparseMatrix newMatrix(this->rows, matrix.cols);
		// this的行
		// cij = Σaikbkj
		for (int i = 1; i <= rows; i++) {
			// matrix的列
			for (int j = 0; j < matrix.rows; j++) {
				// 公共元素 -- this的列 matrix的行
				int sum = 0;
				for (int k = 1; k <= cols; k++) {

				}
			}
		}
		return newMatrix;
	}
private:
	// 判断是否同型
	bool isSameShape(const SparseMatrix& matrix) {
		return matrix.cols == this->cols && matrix.rows == this->rows;
	}
	// 是否啮合
	bool isNesh(const SparseMatrix& matrix) {
		return this->cols == matrix.rows;
	}
};
int main() {
	SparseMatrix matrix(4, 5, "Path.txt");
	SparseMatrix matrix2(4, 5, "Path2.txt");
	SparseMatrix matrix3(5, 5, "Path2.txt");
	cout << "print matrix" << endl;
	matrix.print();
	cout << "print matrix2" << endl;
	matrix2.print();
	cout << "matrix.modify(1, 2, 5)" << endl;
	matrix.modify(1, 2, 5);
	cout << "matrix.modify(1, 4, 10)" << endl;
	matrix.modify(1, 4, 10);
	cout << "m1 + m2" << endl;
	SparseMatrix addMatrix = matrix.Add(matrix2);
	addMatrix.print();
	cout << "m1 - m2" << endl;
	SparseMatrix subMatrix = matrix.Subtract(matrix2);
	subMatrix.print();
	SparseMatrix TransposeSubMatrix = subMatrix.Transpose();
	TransposeSubMatrix.print();
	TransposeSubMatrix.printall();
	matrix.print();
	matrix.printall();
	matrix2.print();
	matrix2.printall();
	SparseMatrix MultiMatrix = matrix.Multiply(matrix3);
	MultiMatrix.printall();
	return 0;
}