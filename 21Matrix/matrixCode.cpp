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
	int valids;
	vector<Triple>tripleArray;

public:
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
public:
	void readFile(string FilePath) {
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
		, valids(0)
	{
		readFile(FilePath);
		valids = tripleArray.size();
		sort(tripleArray.begin(), tripleArray.end(), RowFirst());
	}
	SparseMatrix(int rows, int cols)
		: rows(rows)
		, cols(cols)
		, valids(0)
	{	}
	~SparseMatrix() {	}
public:
	void print() {
		for (auto& u : tripleArray) {
			cout << "( " << u.row << "," << u.col << "," << u.val << " )" << " ";
		}
		cout << endl;
	}
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
	bool isSameShape(const SparseMatrix& matrix) {
		return matrix.cols == this->cols && matrix.rows == this->rows;
	}
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
	SparseMatrix Transpose() {

	}
};
int main() {
	SparseMatrix matrix(4, 5, "Path.txt");
	SparseMatrix matrix2(4, 5, "Path2.txt");
	cout << "print matrix" << endl;
	matrix.print();
	cout << "print matrix2" << endl;
	matrix2.print();
	cout << "matrix.modify(1, 2, 5)" << endl;
	matrix.modify(1, 2, 5);
	cout << "matrix.modify(1, 4, 10)" << endl;
	matrix.modify(1, 4, 10);
	bool flag = matrix.isSameShape(matrix2);
	if (flag) {
		cout << "is same shape" << endl;
	}
	else cout << "not same shape" << endl;
	cout << "m1 + m2" << endl;
	SparseMatrix addMatrix = matrix.Add(matrix2);
	addMatrix.print();
	cout << "m1 - m2" << endl;
	SparseMatrix subMatrix = matrix.Subtract(matrix2);
	subMatrix.print();
	return 0;
}