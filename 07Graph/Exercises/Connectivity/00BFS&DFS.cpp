#include<iostream>
#include<vector>
#include<queue>
#include<cstdlib>
using namespace std;

// 深搜广搜基本思想
#ifdef DEBUG
// 深度优先搜索
void DFS(int start, vector<bool>& visited, const vector<vector<int>>& map) {
	// 如果已经遍历过，直接返回，无需打印，避免死循环
	if (visited[start] == true) {
		return;
	}
	visited[start] = true;
	cout << start << " ";
	for (auto& u : map[start]) {
		// 遍历得到的u对应着start连着的每一个对象
		// u没有遍历过且u和start连着则递归，否则不递归
		if (visited[u] == false) {
			DFS(u, visited, map);
		}
	}
	return;
}
void DFS(vector<vector<int>>& map) {
	int n = map.size();
	vector<bool>visited(n, false);
	DFS(0, visited, map);
	cout << endl;
	return;
}

// 广度优先搜索
void BFS(vector<vector<int>>& map) {
	const int n = map.size();
	vector<bool>visited(n, false);
	queue<int>q;
	q.push(0);
	visited[0] = true;
	while (!q.empty()) {
		auto front = q.front();
		cout << front << " ";
		q.pop();
		for (auto u : map[front]) {
			if (visited[u] == false) {
				q.push(u);
				visited[u] = true;
			}
		}
	}
	cout << endl;
	return;
}

int main() {
	vector<vector<int>> map = {
	{1, 2},    // 节点 0 的邻居是 1, 2
	{0, 3, 4}, // 节点 1 的邻居是 0, 3, 4
	{0},       // 节点 2 的邻居是 0
	{1},       // 节点 3 的邻居是 1
	{1}        // 节点 4 的邻居是 1
	};
	DFS(map);
	BFS(map);
	return 0;
}
#endif // DEBUG

// 200 岛屿问题
#ifdef DEBUG

// 利用DFS BFS思想做题
// 深搜所有可能，广搜最短一层

// LeetCode 200 岛屿数量
/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。

示例 1：
输入：grid =
[
  ['1','1','1','1','0'],
  ['1','1','0','1','0'],
  ['1','1','0','0','0'],
  ['0','0','0','0','0']
]
输出：1
*/
// 必须要四个面都找，防止出现下面的情况
/*
1 1 1 1 0 0
0 0 0 1 0 0
0 1 0 1 0 0
0 1 0 1 0 0
0 1 1 1 0 0  无法往左，会漏一部分陆地
*/

// 深度优先思想
// DFS只负责标记
void DFS(int i, int j, vector<vector<char>>& map, vector<vector<bool>>& visited) {
	// 注意递归终止条件：
	// 如果跑越界了，就返回，防止下标非法
	if (i < 0 || j < 0 || i >= map.size() || j >= map[i].size()) {
		return;
	}
	// 为什么要查visited？如果合法数据，怎么可能越过水区跑到之前记录过的岛屿呢？
	// 不错，确实不会越过水区，但是会在自己的区域内打转，比如[1,1] 先调用DFS(0,0) -> DFS(0,1) -> DFS(0,0) -> ......
	// 所以必须要加
	if (visited[i][j] == true) {
		return;
	}
	if (map[i][j] == '0') {
		return;
	}
	visited[i][j] = true;
	// 向四个方向看看
	DFS(i - 1, j, map, visited);
	DFS(i + 1, j, map, visited);
	DFS(i, j - 1, map, visited);
	DFS(i, j + 1, map, visited);
}
// 主函数负责计数
int islandsDFS(vector<vector<char>>& map) {
	const int n = map.size();
	const int m = map[0].size();
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	int islands = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < visited[i].size(); j++) {
			if (visited[i][j] == false && map[i][j] == '1') {
				islands++;
				DFS(i, j, map, visited);
			}
		}
	}
	return islands;
}

// 广度优先思想
int islandsBFS(vector<vector<char>>& map) {
	const int n = map.size();
	const int m = map[0].size();
	using cord = pair<int, int>;
	queue<cord>q;
	vector<vector<bool>>visited(n, vector<bool>(m, false));
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] == false && map[i][j] == '1') {
				count++;
				q.emplace(i, j);
				visited[i][j] = true;
				while (!q.empty()) {
					auto front = q.front();
					int x = front.first;
					int y = front.second;
					q.pop();
					// 上下左右
					if (x - 1 >= 0 && map[x - 1][y] == '1' && visited[x - 1][y] == false) {
						q.emplace(x - 1, y);
						visited[x - 1][y] = true;
					}
					if (x + 1 < n && map[x + 1][y] == '1' && visited[x + 1][y] == false) {
						q.emplace(x + 1, y);
						visited[x + 1][y] = true;
					}
					if (y - 1 >= 0 && map[x][y - 1] == '1' && visited[x][y - 1] == false) {
						q.emplace(x, y - 1);
						visited[x][y - 1] = true;
					}
					if (y + 1 < m && map[x][y + 1] == '1' && visited[x][y + 1] == false) {
						q.emplace(x, y + 1);
						visited[x][y + 1] = true;
					}
				}
			}
		}
	}
	return count;
}

/*
*  对DFS的优化：在我们DFS的时候，我们设置了一个visited标记数组来记录我们有没有遍历过这个点；这样显很占空间，我们没有很好的直接利用grid二维数组，反而去开辟了一个全新的二维数组，这无疑是占用很大空的！
* 因此为了提高空间复杂度，我们完全可以在grid上原地修改来标记我们是否来过这个位置！
* 思路如下：
* 当我们遍历顶点[i][j]时，一旦发现他是一个未遍历的有效陆地点时，我们完全可以直接将grid[i][j]修改为'0'(改成'水') 来标记：当前位置是一个无效位置，来避免空间的浪费！
*/
// 只负责标记位
void DFSopt(int i, int j, vector<vector<char>>& grid) {
	const int m = grid.size();
	const int n = grid[0].size();
	if (i < 0 || j < 0 || i >= m || j >= n) {
		return;
	}
	if (grid[i][j] == '0') {
		return;
	}
	grid[i][j] = '0';
	// 向四个方向走
	DFSopt(i - 1, j, grid);
	DFSopt(i + 1, j, grid);
	DFSopt(i, j - 1, grid);
	DFSopt(i, j + 1, grid);
}
// 负责遍历
int DFSOptIslands(vector<vector<char>>& grid) {
	const int m = grid.size();
	const int n = grid[0].size();
	int count = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			// 直接通过grid[i][j]判断，如果为'1'说明是未遍历的陆地；否则为1. 水 2. 已遍历的陆地
			if (grid[i][j] == '1') {
				count++;
				DFSopt(i, j, grid);
			}
		}
	}
	return count;
}
/* BFS同理，这里不再赘述 */

// 所以我们也可以使用并查集的思想来解决岛屿问题
class Solution {
public:
	struct UnionFind {
		int getCount() { return count; }
		UnionFind(int n) {
			count = n;
			parent.resize(n, 0);
			for (int i = 0; i < n; i++) {
				parent[i] = i;
			}
		}
		int find(int x) {
			if (parent[x] != x) {
				parent[x] = find(parent[x]);
			}
			return parent[x];
		}
		void merge(int x, int y) {
			int rootX = find(x);
			int rootY = find(y);
			if (rootX != rootY) {
				parent[rootX] = rootY;
				count--;
			}
		}
		vector<int> parent;
		int count;
	};
	int numIslands(vector<vector<char>>& grid) {
		const int m = grid.size();
		const int n = grid[0].size();
		int water = 0;
		UnionFind uf(m * n);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (grid[i][j] == '1') {
					if (i + 1 < m && grid[i + 1][j] == '1') {
						uf.merge(i * n + j, (i + 1) * n + j);
					}
					if (j + 1 < n && grid[i][j + 1] == '1') {
						uf.merge(i * n + j, i * n + j + 1);
					}
				}
				else { water++; }
			}
		}
		return uf.getCount() - water;
	}
};
#endif // DEBUG

// 547 省份数量
#ifdef DEBUG

/*
* LeetCode 547 省份数量
有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b 直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。
省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i 个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。
返回矩阵中 省份 的数量。
*/

// 深度优先搜索
void DFS(int start, vector<bool>& visited, vector<vector<int>>& isConnected) {
	if (visited[start] == true) {
		return;
	}
	visited[start] = true;
	for (int j = 0; j < isConnected.size(); j++) {
		if (visited[j] == false && isConnected[start][j] == 1) {
			DFS(j, visited, isConnected);
		}
	}
}
int provincesDFS(vector<vector<int>>& isConnected) {
	const int n = isConnected.size();
	vector<bool>visited(n, false);
	int count = 0;
	// 循环遍历每个点
	for (int i = 0; i < n; i++) {
		if (visited[i] == false) {
			count++;
			DFS(i, visited, isConnected);
		}
	}
	return count;
}

// 广度优先搜索
int findCircleNum(vector<vector<int>>& isConnected) {
	const int n = isConnected.size();
	vector<bool> visited(n, false);
	queue<int> q;
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] == false) {
			count++;
			q.push(i);
			visited[i] = true;
			while (!q.empty()) {
				auto front = q.front();
				q.pop();
				for (int k = 0; k < n; k++) {
					if (visited[k] == false && isConnected[front][k] == 1) {
						q.push(k);
						visited[k] = true;
					}
				}
			}
		}
	}
	return count;
}

// UnionFind解法
class Solution {
public:
	struct UnionFind {
	private:
		vector<int> parent;
		int count;

	public:
		UnionFind(int n) {
			parent.resize(n, 0);
			for (int i = 0; i < n; i++) {
				parent[i] = i;
			}
			count = n;
		}

	public:
		// find  查
		int find(int x) {
			if (parent[x] != x) {
				parent[x] = find(parent[x]);
			}
			return parent[x];
		}
		// Union  并
		void Union(int x, int y) {
			int root_x = find(x);
			int root_y = find(y);
			if (root_x != root_y) {
				parent[root_x] = root_y;
				count--;
			}
		}
		int getCount() { return count; }
	};
	int findCircleNum(vector<vector<int>>& isConnected) {
		const int n = isConnected.size();
		UnionFind uf(n);
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (isConnected[i][j] == 1) {
					uf.Union(i, j);
				}
			}
		}
		return uf.getCount();
	}
};
#endif // DEBUG

// * 695. 最大岛屿面积
#ifdef DEBUG

/*
* 695. 最大岛屿面积
给你一个大小为 m x n 的二进制矩阵 grid。
岛屿是由一些相邻的 1（代表土地）构成的组合，这里的“相邻”要求两个 1 必须在水平或者竖直的四个方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。
岛屿的面积是岛上值为 1 的单元格的数目。
计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0。
*/
void DFS(int i, int j, vector<vector<int>>& grid, int& area) {
	if (grid[i][j] == 0) {
		return;
	}
	area++;
	grid[i][j] = 0;
	if (i - 1 >= 0 && grid[i - 1][j] == 1) {
		DFS(i - 1, j, grid, area);
	}
	if (i + 1 < grid.size() && grid[i + 1][j] == 1) {
		DFS(i + 1, j, grid, area);
	}
	if (j - 1 >= 0 && grid[i][j - 1] == 1) {
		DFS(i, j - 1, grid, area);
	}
	if (j + 1 < grid[0].size() && grid[i][j + 1] == 1) {
		DFS(i, j + 1, grid, area);
	}
}
int maxAreaOfIslandDFS(vector<vector<int>>& grid) {
	const int m = grid.size();
	const int n = grid[0].size();
	int largestArea = 0;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1) {
				int area = 0;
				DFS(i, j, grid, area);
				largestArea = max(largestArea, area);
			}
		}
	}
	return largestArea;
}

int maxAreaOfIslandBFS(vector<vector<int>>& grid) {
	const int m = grid.size();
	const int n = grid[0].size();
	int ret = 0;
	using cord = pair<int, int>;
	queue<cord>q;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 1) {
				int area = 0;
				q.emplace(i, j);
				grid[i][j] = 0;
				while (!q.empty()) {
					auto front = q.front();
					int x = front.first;
					int y = front.second;
					q.pop();
					area++;
					if (x - 1 >= 0 && grid[x - 1][y] == 1) {
						q.emplace(x - 1, y);
						grid[x - 1][y] = 0;
					}
					if (x + 1 < grid.size() && grid[x + 1][y] == 1) {
						q.emplace(x + 1, y);
						grid[x + 1][y] = 0;
					}
					if (y - 1 >= 0 && grid[x][y - 1] == 1) {
						q.emplace(x, y - 1);
						grid[x][y - 1] = 0;
					}
					if (y + 1 < grid[0].size() && grid[x][y + 1] == 1) {
						q.emplace(x, y + 1);
						grid[x][y + 1] = 0;
					}
				}
				ret = max(ret, area);
			}
		}
	}
	return ret;
}
#endif // DEBUG

// * 1254. 统计封闭岛屿
#ifdef DEBUG
/*
* 1254. 统计封闭岛屿
二维矩阵 grid 由 0（土地）和 1（水）组成。岛是由最大的 4 个方向连通的 0 组成的群，封闭岛是一个完全由 1 包围（左、上、右、下）的岛。
请返回封闭岛屿的数目。
*/
/*
* 先遍历第一行 第一列 最后一行 最后一列，把所有出现在这些位上的陆地以及毗邻的陆地全部变成水，再去中间找就可以了！
*/
void DFS(int i, int j, vector<vector<int>>& grid) {
	if (i < 0 || i >= grid.size()) {
		return;
	}
	if (j < 0 || j >= grid[0].size()) {
		return;
	}
	if (grid[i][j] == 1) {
		return;
	}
	grid[i][j] = 1;
	if (i - 1 >= 0 && grid[i - 1][j] == 0) {
		DFS(i - 1, j, grid);
	}
	if (i + 1 < grid.size() && grid[i + 1][j] == 0) {
		DFS(i + 1, j, grid);
	}
	if (j - 1 >= 0 && grid[i][j - 1] == 0) {
		DFS(i, j - 1, grid);
	}
	if (j + 1 < grid[0].size() && grid[i][j + 1] == 0) {
		DFS(i, j + 1, grid);
	}
}
int closedIsland(vector<vector<int>>& grid) {
	// 把周围一圈先扫干净
	const int m = grid.size();
	const int n = grid[0].size();
	// 第一行和最后一行
	for (int j = 0; j < n; j++) {
		if (grid[0][j] == 0) {
			DFS(0, j, grid);
		}
		if (grid[m - 1][j] == 0) {
			DFS(m - 1, j, grid);
		}
	}
	// 第一列和最后一列
	for (int i = 0; i < m; i++) {
		if (grid[i][0] == 0) {
			DFS(i, 0, grid);
		}
		if (grid[i][n - 1] == 0) {
			DFS(i, n - 1, grid);
		}
	}
	// 开始数数
	int count = 0;
	for (int i = 1; i < m - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			if (grid[i][j] == 0) {
				count++;
				DFS(i, j, grid);
			}
		}
	}
	return count;
}

#endif // DEBUG

// *417. 太平洋大西洋水流问题
#ifdef DEBUG

/*
417. 太平洋大西洋水流问题
有一个 m × n 的矩形岛屿，与太平洋和大西洋相邻。“太平洋”处于大陆的左边界和上边界，而“大西洋”处于大陆的右边界和下边界。
这个岛被分割成一个由若干方形单元格组成的网格。给定一个 m x n 的整数矩阵 heights，heights[r][c] 表示坐标 (r, c) 上单元格高于海平面的高度。
岛上雨水较多，如果相邻单元格的高度小于或等于当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋。
返回网格坐标 result 的 2D 列表，其中 result[i] = [ri, ci] 表示雨水从单元格 (ri, ci) 流动既可流向太平洋也可流向大西洋。
*/
void DFS(int i, int j, vector<vector<int>>& heights, vector<vector<bool>>& canReach) {
	const int m = heights.size();
	const int n = heights[0].size();
	canReach[i][j] = true;
	if (i - 1 >= 0 && heights[i - 1][j] >= heights[i][j] && canReach[i - 1][j] == false) {
		DFS(i - 1, j, heights, canReach);
	}
	if (i + 1 < m && heights[i + 1][j] >= heights[i][j] && canReach[i + 1][j] == false) {
		DFS(i + 1, j, heights, canReach);
	}
	if (j - 1 >= 0 && heights[i][j - 1] >= heights[i][j] && canReach[i][j - 1] == false) {
		DFS(i, j - 1, heights, canReach);
	}
	if (j + 1 < n && heights[i][j + 1] >= heights[i][j] && canReach[i][j + 1] == false) {
		DFS(i, j + 1, heights, canReach);
	}
}
vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
	vector<vector<int>> ret;
	const int m = heights.size();
	const int n = heights[0].size();
	// 左上
	vector<vector<bool>>canReachP(m, vector<bool>(n, false));
	// 右下
	vector<vector<bool>>canReachA(m, vector<bool>(n, false));
	// 开始淹没
	// 太平洋发力
	for (int i = 0; i < m; i++) {
		DFS(i, 0, heights, canReachP);
	}
	for (int j = 0; j < n; j++) {
		DFS(0, j, heights, canReachP);
	}
	// 大西洋发力
	for (int i = 0; i < m; i++) {
		DFS(i, n - 1, heights, canReachA);
	}
	for (int j = 0; j < n; j++) {
		DFS(m - 1, j, heights, canReachA);
	}
	// 找哪些是可以同时进入两个洋的
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (canReachA[i][j] == true && canReachP[i][j] == true) {
				ret.push_back({ i, j });
			}
		}
	}
	return ret;
}
#endif // DEBUG
// 79 * 单词搜索
/*
给定一个 m x n 二维字符网格 board和一个字符串单词word 。如果word存在于网格中，返回true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
*/
class Solution {
public:
	bool DFS(int i, int j, int k, vector<vector<char>>& board, string word,
		vector<vector<bool>>& visited) {
		const int m = board.size();
		const int n = board[0].size();
		if (k == word.size()) {
			return true;
		}
		if (i < 0 || j < 0 || i >= m || j >= n) {
			return false;
		}
		if (visited[i][j] == true) {
			return false;
		}
		if (word[k] != board[i][j]) {
			return false;
		}
		visited[i][j] = true;
		bool up = DFS(i - 1, j, k + 1, board, word, visited);
		bool down = DFS(i + 1, j, k + 1, board, word, visited);
		bool left = DFS(i, j - 1, k + 1, board, word, visited);
		bool right = DFS(i, j + 1, k + 1, board, word, visited);
		visited[i][j] = false;
		return up || down || left || right;
	}
	bool exist(vector<vector<char>>& board, string word) {
		const int m = board.size();
		const int n = board[0].size();
		vector<vector<bool>> visited(m, vector<bool>(n, false));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (DFS(i, j, 0, board, word, visited)) {
					return true;
				}
			}
		}
		return false;
	}
};