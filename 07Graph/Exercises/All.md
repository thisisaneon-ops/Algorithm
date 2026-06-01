## 图

### 图基础

#### DFS

深度优先搜索算法

```C++
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
```



#### BFS

```C++
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
```



#### 并查集

```C++
#include<iostream>
#include<vector>
using namespace std;
// 并查集
#ifdef DEBUG
class UnionFind {
private:
	vector<int>parent;
	int count;
public:
	UnionFind(vector<int> parent) {
		this->parent = parent;
		count = parent.size();
	}
public:
	// makeSet  集
	void makeSet() {
		for (int i = 0; i < parent.size(); i++) {
			parent[i] = i;
		}
		count = parent.size();
	}
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
	int getCount() {
		return count;
	}
};
```





#### Dijkstra

```C++
class RareDikjstra {
	int Dijkstra(vector<vector<uint>>& graph, int start, int end) {
		const int n = graph.size();
		vector<uint>dis(n, INF);
		vector<bool>use(n, false);
		// 初始化dis和use数组
		for (int i = 0; i < n; i++) {
			dis[i] = graph[start][i];
		}
		use[start] = true;
		// 下面开始循环
		for (int i = 1; i < n; i++) {
			// 找当前U集合里还没有用的元素里最小的那个
			int k = -1;
			int min = INF;
			for (int j = 0; j < n; j++) {
				if (use[j] == false) {
					if (dis[j] < min) {
						min = dis[j];
						k = j;
					}
				}
			}
			// 若出循环k还是-1, 说明剩下的都是孤立点
			if (k == -1) {
				break;  // 直接退出循环
			}
			// 否则将当前最小的Vertex标记为used, 并且更新剩余节点的dis数值
			use[k] = true;
			for (int j = 0; j < n; j++) {
				if (use[j] == false) {
					dis[j] = std::min(dis[j], min + graph[k][j]);
				}
			}
		}
		return dis[end];
	}
};

```



小根堆优化

```C++
class OptimizedDikjstra {
	int Dijkstra(vector<vector<uint>>& graph, int start, int end) {
		const int n = graph.size();
		vector<uint>dis(n, INF);
		vector<bool>use(n, false);
		using pair = pair<uint, int>;  // key是权值，value是序号
		priority_queue<pair, vector<pair>, greater<pair>>q;
		// 先初始化
		for (int i = 0; i < n; i++) {
			dis[i] = graph[start][i];
			q.emplace(dis[i], i);
		}
		use[start] = true;
		// 下面开始循环
		while (!q.empty()) {
			auto top = q.top();
			q.pop();
			uint min = top.first;
			int k = top.second;
			if (min == INF) {
				break;
			}
			// 已经找到了最小的那个，下面只需要更改状态＋更新其他
			if (use[k])
				continue;
			use[k] = true;
			for (int i = 0; i < n; i++) {
				if (use[i] == false) {
					dis[i] = std::min(dis[i], min + graph[k][i]);
					q.emplace(dis[i], i);
				}
			}
		}
		return dis[end];
	}
};
```



##### [743] 网络延迟时间

有 `n` 个网络节点，标记为 `1` 到 `n`。

给你一个列表 `times`，表示信号经过 **有向** 边的传递时间。 `times[i] = (ui, vi, wi)`，其中 `ui` 是源节点，`vi` 是目标节点， `wi` 是一个信号从源节点传递到目标节点的时间。

现在，从某个节点 `K` 发出一个信号。需要多久才能使所有节点都收到信号？如果不能使所有节点收到信号，返回 `-1` 。

```C++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 先建立矩阵
        using uint = unsigned int;
        uint INF = INT_MAX;
        vector<vector<uint>>graph(n, vector<uint>(n, INF));
        for(auto u : times){
            // 每个元素的结构: 起始点 终点 时间
            int start = u[0] - 1;
            int end = u[1] - 1;
            int time = u[2];
            graph[start][end] = time;
        }
        for(int i = 0; i < n; i++){
            graph[i][i] = 0;
        }

        // 有了graph下面就很好操作了
        vector<uint>dis(n, INF);
        vector<bool>use(n, false);
        for(int i = 0; i < n; i++){
            dis[i] = graph[k - 1][i];
        }
        use[k - 1] = true;
        // 下面开始循环
        for(int i = 1; i < n; i++){
            int point = -1;
            uint min = INF;
            for(int j = 0; j < n; j++){
                if(use[j] == false && dis[j] < min){
                    min = dis[j];
                    point = j;
                }
            }
            if(point == -1){
                break;
            }
            use[point] = true;
            for(int j = 0; j < n; j++){
                if(use[j] == false){
                    dis[j] = std::min(dis[j], min + graph[point][j]);
                }
            }
        }
        // 最后遍历数组，找到最大值并返回
        uint maxTime = 0;
        for(int i = 0; i < n; i++){
            maxTime = max(maxTime, dis[i]);
        }
        return maxTime == INF ? -1 : maxTime;
    }
};过滤
```

小根堆优化

```C++
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // 先建立矩阵
        using uint = unsigned int;
        uint INF = INT_MAX;
        vector<vector<uint>>graph(n, vector<uint>(n, INF));
        for(auto u : times){
            // 每个元素的结构: 起始点 终点 时间
            int start = u[0] - 1;
            int end = u[1] - 1;
            int time = u[2];
            graph[start][end] = time;
        }
        for(int i = 0; i < n; i++){
            graph[i][i] = 0;
        }

        // 有了graph下面就很好操作了
        vector<uint>dis(n, INF);
        vector<bool>use(n, false);
        using pair = pair<uint, int>;
        priority_queue<pair, vector<pair>, greater<pair>>q;
        for(int i = 0; i < n; i++){
            dis[i] = graph[k - 1][i];
            q.emplace(dis[i], i);
        }
        use[k - 1] = true;
        // 下面开始循环
        while(!q.empty()){
            auto top = q.top();
            q.pop();
            int point = top.second;
            uint min = top.first;
            if(min == INF){
                break;
            }
            if(use[point]){
                continue;
            }
            use[point] = true;
            for(int j = 0; j < n; j++){
                if(use[j] == false){
                    dis[j] = std::min(dis[j], min + graph[point][j]);
                    q.emplace(dis[j], j);
                }
            }
        }
        // 最后遍历数组，找到最大值并返回
        uint maxTime = 0;
        for(int i = 0; i < n; i++){
            maxTime = max(maxTime, dis[i]);
        }
        return maxTime == INF ? -1 : maxTime;
    }
};
```



#### Floyd

```

```



### 图的应用练习

#### DFS回溯找路径

##### [797]所有可能的路径

给你一个有 `n` 个节点的 **有向无环图（DAG）**，请你找出从节点 `0` 到节点 `n-1` 的所有路径并输出（**不要求按特定顺序**）

 `graph[i]` 是一个从节点 `i` 可以访问的所有节点的列表（即从节点 `i` 到节点 `graph[i][j]`存在一条有向边）。

```C++
class Solution {
    vector<vector<int>> graph;
    vector<vector<int>> paths;
    int n;
    void dfs(int i, vector<int>& path) {
        if (i == n - 1) {
            paths.push_back(path);
            return;
        }
        for (int k = 0; k < graph[i].size(); k++) {
            path.push_back(graph[i][k]);
            dfs(graph[i][k], path);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& v) {
        paths.clear();
        graph.clear();
        graph = v;
        vector<int> path;
        n = v.size();
        path.push_back(0);
        dfs(0, path);
        return paths;
    }
};

```



##### [79] 单词搜索

给定一个 `m x n` 二维字符网格 `board` 和一个字符串单词 `word` 。如果 `word` 存在于网格中，返回 `true` ；否则，返回 `false` 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

```C++
class Solution {
public:
    bool DFS(int i, int j, int k, vector<vector<char>>& board, string word,
             vector<vector<bool>>& visited) {
        const int m = board.size();
        const int n = board[0].size();
        if(k == word.size()){
            return true;
        }
        if(i < 0 || j < 0 || i >= m || j >= n){
            return false;
        }
        if(visited[i][j] == true){
            return false;
        }
        if(word[k] != board[i][j]){
            return false;
        }
        visited[i][j] = true;
        bool up =  DFS(i - 1, j, k + 1, board, word, visited);
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

```

原地修改

```C++
class Solution {
    string target;
    bool dfs(int idx, int i, int j, vector<vector<char>>& board) {
        const int m = board.size();
        const int n = board[0].size();
        if (idx == target.size()) {
            return true;
        }
        if (i < 0 || i >= m || j < 0 || j >= n) {
            return false;
        }
        if (board[i][j] != target[idx]) {
            return false;
        }
        // 原地修改，随便改成什么，改废了就可以
        char tmp = board[i][j];
        board[i][j] = '#';
        bool ret = dfs(idx + 1, i - 1, j, board) || dfs(idx + 1, i + 1, j, board) ||
        dfs(idx + 1, i, j - 1, board) || dfs(idx + 1, i, j + 1, board);
        board[i][j] = tmp;
        return ret;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        const int m = board.size();
        const int n = board[0].size();
        target = word;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(0, i, j, board)) {
                    return true;
                }
            }
        }
        return false;
    }
};

```



##### [1971]寻找图中是否存在合法路径

有一个具有 `n` 个顶点的 **双向** 图，其中每个顶点标记从 `0` 到 `n - 1`（包含 `0` 和 `n - 1`）。图中的边用一个二维整数数组 `edges` 表示，其中 `edges[i] = [ui, vi]` 表示顶点 `ui` 和顶点 `vi` 之间的双向边。 每个顶点对由 **最多一条** 边连接，并且没有顶点存在与自身相连的边。

请你确定是否存在从顶点 `source` 开始，到顶点 `destination` 结束的 **有效路径** 。

给你数组 `edges` 和整数 `n`、`source` 和 `destination`，如果从 `source` 到 `destination` 存在 **有效路径** ，则返回 `true`，否则返回 `false` 。

```C++
class Solution {
    void dfs(int u, vector<bool>& visited, vector<vector<int>>& adjList){
        if(visited[u] == true){
            return;
        }
        visited[u] = true;
        for(int i = 0; i < adjList[u].size(); i++){
            dfs(adjList[u][i], visited, adjList);
        }
    }
public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        vector<vector<int>>adjList(n, vector<int>());
        const int m = edges.size();
        for(int i = 0; i < m; i++){
            int startEdge = edges[i][0];
            int endEdge = edges[i][1];
            adjList[startEdge].push_back(endEdge);
            adjList[endEdge].push_back(startEdge);
        }
        vector<bool>visited(n, false);
        dfs(start, visited, adjList);
        return visited[end];
    }
};

```



#### 图的连通性

##### [547] 省份问题

有 `n` 个城市，其中一些彼此相连，另一些没有相连。如果城市 `a` 与城市 `b` 直接相连，且城市 `b` 与城市 `c` 直接相连，那么城市 `a` 与城市 `c` 间接相连。

**省份** 是一组直接或间接相连的城市，组内不含其他没有相连的城市。

给你一个 `n x n` 的矩阵 `isConnected` ，其中 `isConnected[i][j] = 1` 表示第 `i` 个城市和第 `j` 个城市直接相连，而 `isConnected[i][j] = 0` 表示二者不直接相连。

返回矩阵中 **省份** 的数量。

DFS和BFS 并查集都可以做

```C++
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

```



##### [200] 岛屿问题

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

```C++
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

```



##### 695 最大岛屿面积

给你一个大小为 `m x n` 的二进制矩阵 `grid` 。

**岛屿** 是由一些相邻的 `1` (代表土地) 构成的组合，这里的「相邻」要求两个 `1` 必须在 **水平或者竖直的四个方向上** 相邻。你可以假设 `grid` 的四个边缘都被 `0`（代表水）包围着。

岛屿的面积是岛上值为 `1` 的单元格的数目。

计算并返回 `grid` 中最大的岛屿面积。如果没有岛屿，则返回面积为 `0` 。

深搜

```C++
class Solution {
public:
    void DFS(int i, int j, vector<vector<int>>& grid, int& area){
        if(grid[i][j] == 0){
            return;
        }
        area++;
        grid[i][j] = 0;
        if(i - 1 >= 0 && grid[i - 1][j] == 1){
            DFS(i - 1, j, grid, area);
        }
        if(i + 1 < grid.size() && grid[i + 1][j] == 1){
            DFS(i + 1, j, grid, area);
        }
        if(j - 1 >= 0 && grid[i][j - 1] == 1){
            DFS(i, j - 1, grid, area);
        }
        if(j + 1 < grid[0].size() && grid[i][j + 1] == 1){
            DFS(i, j + 1, grid, area);
        }
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        int largestArea = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    int area = 0;
                    DFS(i, j, grid, area);
                    largestArea = max(largestArea, area);
                }
            }
        }
        return largestArea;
    }
};

```

广搜

```C++
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        int ret = 0;
        using cord = pair<int, int>;
        queue<cord>q;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 1){
                    int area = 0;
                    q.emplace(i, j);
                    grid[i][j] = 0;
                    while(!q.empty()){
                        auto front = q.front();
                        int x = front.first;
                        int y = front.second;
                        q.pop();
                        area++;
                        if(x - 1 >= 0 && grid[x - 1][y] == 1){
                            q.emplace(x - 1, y);
                            grid[x - 1][y] = 0;
                        }
                        if(x + 1 < grid.size() && grid[x + 1][y] == 1){
                            q.emplace(x + 1, y);
                            grid[x + 1][y] = 0;
                        }
                        if(y - 1 >= 0 && grid[x][y - 1] == 1){
                            q.emplace(x, y - 1);
                            grid[x][y - 1] = 0;
                        }
                        if(y + 1 < grid[0].size() && grid[x][y + 1] == 1){
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
};

```









#### 边缘处理

##### [1254] 统计封闭岛屿

二维矩阵 `grid` 由 `0` （土地）和 `1` （水）组成。岛是由最大的4个方向连通的 `0` 组成的群，封闭岛是一个 `完全` 由1包围（左、上、右、下）的岛。

请返回 *封闭岛屿* 的数目。

```C++
class Solution {
public:
    void DFS(int i, int j, vector<vector<int>>& grid) {
        if(i < 0 || i >= grid.size()){
            return;
        }
        if(j <0 || j >= grid[0].size()){
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
};

```





##### [1020]飞地的数量

给你一个大小为 `m x n` 的二进制矩阵 `grid` ，其中 `0` 表示一个海洋单元格、`1` 表示一个陆地单元格。

一次 **移动** 是指从一个陆地单元格走到另一个相邻（**上、下、左、右**）的陆地单元格或跨过 `grid` 的边界。

返回网格中 **无法** 在任意次数的移动中离开网格边界的陆地单元格的数量。

```C++
class Solution {
    void dfs(int i, int j, vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        if (i < 0 || j < 0 || i > m - 1 || j > n - 1){
            return;
        }
        if(grid[i][j] == 0){
            return;
        }
        grid[i][j] = 0;
        dfs(i - 1, j, grid);
        dfs(i + 1, j, grid);
        dfs(i, j - 1, grid);
        dfs(i, j + 1, grid);
    }

public:
    int numEnclaves(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 1) {
                dfs(i, 0, grid);
            }
            if (grid[i][n - 1] == 1) {
                dfs(i, n - 1, grid);
            }
        }
        for (int j = 0; j < n; j++) {
            if (grid[0][j] == 1) {
                dfs(0, j, grid);
            }
            if (grid[m - 1][j] == 1) {
                dfs(m - 1, j, grid);
            }
        }
        // 找剩下的面积总数
        int area = 0;
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (grid[i][j] == 1) {
                    area++;
                }
            }
        }
        return area;
    }
};

```





##### [417] 大西洋太平洋问题

有一个 `m × n` 的矩形岛屿，与 **太平洋** 和 **大西洋** 相邻。 **“太平洋”** 处于大陆的左边界和上边界，而 **“大西洋”** 处于大陆的右边界和下边界。

这个岛被分割成一个由若干方形单元格组成的网格。给定一个 `m x n` 的整数矩阵 `heights` ， `heights[r][c]` 表示坐标 `(r, c)` 上单元格 **高于海平面的高度** 。

岛上雨水较多，如果相邻单元格的高度 **小于或等于** 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋。

返回网格坐标 `result` 的 **2D 列表** ，其中 `result[i] = [ri, ci]` 表示雨水从单元格 `(ri, ci)` 流动 **既可流向太平洋也可流向大西洋** 。

```C++
class Solution {
    void dfs(int i, int j, vector<vector<int>>& map, vector<vector<int>>& heights) {
        if(i < 0 || i >= heights.size() || j < 0 || j >= heights[0].size()){
            return;
        }
        if(map[i][j] == 1){
            return;
        }
        map[i][j] = 1;
        if (i - 1 >= 0 && heights[i - 1][j] >= heights[i][j]) {
            dfs(i - 1, j, map, heights);
        }
        if (i + 1 < heights.size() && heights[i + 1][j] >= heights[i][j]) {
            dfs(i + 1, j, map, heights);
        }
        if (j - 1 >= 0 && heights[i][j - 1] >= heights[i][j]) {
            dfs(i, j - 1, map, heights);
        }
        if (j + 1 < heights[0].size() && heights[i][j + 1] >= heights[i][j]) {
            dfs(i, j + 1, map, heights);
        }
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        const int m = heights.size();
        const int n = heights[0].size();
        vector<vector<int>> pacific(m, vector<int>(n, 0));
        vector<vector<int>> atlantic(m, vector<int>(n, 0));
        // 先让Pacific倒灌
        for (int i = 0; i < m; i++) {
            dfs(i, 0, pacific, heights);
        }
        for (int j = 0; j < n; j++) {
            dfs(0, j, pacific, heights);
        }
        // 再让atlantic操作
        for (int i = 0; i < m; i++) {
            dfs(i, n - 1, atlantic, heights);
        }
        for (int j = 0; j < n; j++) {
            dfs(m - 1, j, atlantic, heights);
        }
        // 检查map里2的个数
        vector<vector<int>> ret;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pacific[i][j] && atlantic[i][j] != 0) {
                    ret.push_back({i, j});
                }
            }
        }
        return ret;
    }
};

```





##### [130]被围绕的区域

给你一个 `m x n` 的矩阵 `board` ，由若干字符 `'X'` 和 `'O'` 组成，**捕获** 所有 **被围绕的区域**：

- **连接：**一个单元格与水平或垂直方向上相邻的单元格连接。
- **区域：连接所有** `'O'` 的单元格来形成一个区域。
- **围绕：**如果一个区域中的所有 `'O'` 单元格都不在棋盘的边缘，则该区域被包围。这样的区域 **完全** 被 `'X'` 单元格包围。

通过 **原地** 将输入矩阵中的所有 `'O'` 替换为 `'X'` 来 **捕获被围绕的区域**。你不需要返回任何值。

```
class Solution {
    void dfs(int i, int j, vector<vector<char>>& board) {
        const int m = board.size();
        const int n = board[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n) {
            return;
        }
        if (board[i][j] == 'X' || board[i][j] == 'M') {
            return;
        }
        board[i][j] = 'M';
        dfs(i - 1, j, board);
        dfs(i + 1, j, board);
        dfs(i, j - 1, board);
        dfs(i, j + 1, board);
    }

public:
    void solve(vector<vector<char>>& board) {
        const int m = board.size();
        const int n = board[0].size();
        for (int i = 0; i < m; i++) {
            if (board[i][0] == 'O') {
                dfs(i, 0, board);
            }
            if (board[i][n - 1] == 'O') {
                dfs(i, n - 1, board);
            }
        }
        for (int j = 0; j < n; j++) {
            if (board[0][j] == 'O') {
                dfs(0, j, board);
            }
            if (board[m - 1][j] == 'O') {
                dfs(m - 1, j, board);
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'M') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};

```





#### 多源BFS

##### [994]腐烂的橘子

在给定的 `m x n` 网格 `grid` 中，每个单元格可以有以下三个值之一：

- 值 `0` 代表空单元格；
- 值 `1` 代表新鲜橘子；
- 值 `2` 代表腐烂的橘子。

每分钟，腐烂的橘子 **周围 4 个方向上相邻** 的新鲜橘子都会腐烂。

返回 *直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1* 。

```C++
// 值 0 代表空单元格；
// 值 1 代表新鲜橘子；
// 值 2 代表腐烂的橘子。
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        using cord = pair<int, int>;
        queue<cord> q;
        int lvl = -1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // 遇到腐烂的橘子感染周围
                if (grid[i][j] == 2) {
                    q.push({i, j});
                }
            }
        }
        // 现在里面是第0层
        while (!q.empty()) {
            int cursize = q.size();
            for (int i = 0; i < cursize; i++) {
                auto front = q.front();
                q.pop();
                int fronti = front.first;
                int frontj = front.second;
                if (fronti - 1 >= 0 && grid[fronti - 1][frontj] == 1) {
                    q.push({fronti - 1, frontj});
                    grid[fronti - 1][frontj] = 2;
                }
                if (fronti + 1 < m && grid[fronti + 1][frontj] == 1) {
                    q.push({fronti + 1, frontj});
                    grid[fronti + 1][frontj] = 2;
                }
                if (frontj - 1 >= 0 && grid[fronti][frontj - 1] == 1) {
                    q.push({fronti, frontj - 1});
                    grid[fronti][frontj - 1] = 2;
                }
                if (frontj + 1 < n && grid[fronti][frontj + 1] == 1) {
                    q.push({fronti, frontj + 1});
                    grid[fronti][frontj + 1] = 2;
                }
            }
            lvl++;
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    return -1;
                }
            }
        }
        return lvl == -1 ? 0 : lvl;
    }
};

```





#### 拓扑排序

##### [207] 课程表

你这个学期必须选修 `numCourses` 门课程，记为 `0` 到 `numCourses - 1` 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 `prerequisites` 给出，其中 `prerequisites[i] = [ai, bi]` ，表示如果要学习课程 `ai` 则 **必须** 先学习课程  `bi` 。

- 例如，先修课程对 `[0, 1]` 表示：想要学习课程 `0` ，你需要先完成课程 `1` 。

请你判断是否可能完成所有课程的学习？如果可以，返回 `true` ；否则，返回 `false` 。

```C++
// 课程表
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& pres) {
        const int m = numCourses;
        // 建立邻接表
        vector<vector<int>>adjList(m, vector<int>());
        // 建立入度数组
        vector<int>inDegree(m, 0);
        // 先初始化入度数组和建立邻接表
        for (int i = 0; i < pres.size(); i++) {
            // 当前课程
            int ai = pres[i][0];
            // 先修课程
            int bi = pres[i][1];
            // 建立学好后可以学什么的表
            adjList[bi].push_back(ai);
            // 建立入度表，统计入度值，判断是否入队
            inDegree[ai]++;
        }
        // 建立队列并初始化
        queue<int>q;
        for (int i = 0; i < m; i++) {
            if(inDegree[i] == 0)
                q.push(i);
        }
        // 用cnt变量统计已经学过的课程总数
        int cnt = 0;
        // 开始读取并入队
        while (!q.empty()) {
            auto front = q.front();
            cnt++;
            q.pop();
            for (int i = 0; i < adjList[front].size(); i++) {
                inDegree[adjList[front][i]]--;
                // 如果入度为零，当前课程入队
                if (inDegree[adjList[front][i]] == 0) {
                    q.push(adjList[front][i]);
                }
            }
        }
        return numCourses == cnt;
    }
};

```



##### [210] 课程表II

返回学习顺序，如果学不完返回空数组

```C++
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& pres) {
        const int m = numCourses;
        // 建立邻接表
        vector<vector<int>> adjList(m, vector<int>());
        // 建立入度数组
        vector<int> inDegree(m, 0);
        // 建立学习顺序数组
        vector<int> order;
        // 先初始化入度数组和建立邻接表
        for (int i = 0; i < pres.size(); i++) {
            // 当前课程
            int ai = pres[i][0];
            // 先修课程
            int bi = pres[i][1];
            // 建立学好后可以学什么的表
            adjList[bi].push_back(ai);
            // 建立入度表，统计入度值，判断是否入队
            inDegree[ai]++;
        }
        // 建立队列并初始化
        queue<int> q;
        for (int i = 0; i < m; i++) {
            if (inDegree[i] == 0)
                q.push(i);
        }
        // 开始读取并入队
        while (!q.empty()) {
            auto front = q.front();
            order.push_back(front);
            q.pop();
            for (int i = 0; i < adjList[front].size(); i++) {
                inDegree[adjList[front][i]]--;
                // 如果入度为零，当前课程入队
                if (inDegree[adjList[front][i]] == 0) {
                    q.push(adjList[front][i]);
                }
            }
        }
        if(order.size() < numCourses){
            order.clear();
        }
        return order;
    }
};

```





#### 并查集

##### [547]省份问题

也可以用并查集来写

```C++
class Solution {
    struct UnionFind {
        int cnt;
        vector<int> parent;
        UnionFind(int n) {
            cnt = n;
            parent.resize(n);
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
                cnt--;
            }
        }
        int getCnt() { return cnt; }
    };

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        const int n = isConnected.size();
        UnionFind uf(n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(isConnected[i][j] == 1){
                    uf.merge(i, j);
                }
            }
        }
        return uf.getCnt();
    }
};

```



##### [684]冗余连接

树可以看成是一个连通且 **无环** 的 **无向** 图。

给定一个图，该图从一棵 `n` 个节点 (节点值 `1～n`) 的树中添加一条边后获得。添加的边的两个不同顶点编号在 `1` 到 `n` 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 `n` 的二维数组 `edges` ，`edges[i] = [ai, bi]` 表示图中在 `ai` 和 `bi` 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 `n` 个节点的树。如果有多个答案，则返回数组 `edges` 中最后出现的那个。

```C++
class Solution {
    struct UnionFind {
        int cnt;
        vector<int> parent;
        UnionFind(int n) {
            cnt = n;
            parent.resize(n);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        void merge(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootX] = rootY;
                cnt--;
            }
        }
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        int getCnt() { return cnt; }
    };

public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        const int n = edges.size();
        // 注意节点序号是1-based
        UnionFind uf(n + 1);
        int superfluous = 0;
        for (int i = 0; i < edges.size(); i++) {
            int edgea = edges[i][0];
            int edgeb = edges[i][1];
            if (uf.find(edgea) == uf.find(edgeb)) {
                superfluous = i;
            } else {
                uf.merge(edgea, edgeb);
            }
        }
        return edges[superfluous];
    }
};

```





##### [685]冗余连接

在本问题中，有根树指满足以下条件的 **有向** 图。该树只有一个根节点，所有其他节点都是该根节点的后继。该树除了根节点之外的每一个节点都有且只有一个父节点，而根节点没有父节点。

输入一个有向图，该图由一个有着 `n` 个节点（节点值不重复，从 `1` 到 `n`）的树及一条附加的有向边构成。附加的边包含在 `1` 到 `n` 中的两个不同顶点间，这条附加的边不属于树中已存在的边。

结果图是一个以边组成的二维数组 `edges` 。 每个元素是一对 `[ui, vi]`，用以表示 **有向** 图中连接顶点 `ui` 和顶点 `vi` 的边，其中 `ui` 是 `vi` 的一个父节点。

返回一条能删除的边，使得剩下的图是有 `n` 个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。

分析问题：

在研究这个问题之前，我们需要先明确一颗正确的树和一颗错误的树(被添加了一个多余的边后的树)可能具备什么样的父子结点属性？
正确的树：

1. 有根树具有一个根节点 -- 有且仅有一个入度为0的Vertix
2. 其他Vertix的父节点只能有一个，入度为1
   换句话说：只能有一个入度为0的节点，其他节点入度只能为1

错误的树：

可能的错误	

1. 把某些节点指向到根节点身上  --》 根节点入度为1，全局无一个入度为0节点
2. 把某些节点指向其祖先节点(包括父节点)形成环结构，导致某些节点入度变为2(通常是被指节点) 
   由此不难看出，一颗错误的树通常可能有如下特征：
3. 全局无入度为0节点
4. 某节点入度为2，存在多个父节点

```
且这两个错误只可能同时存在一个

```

逻辑分析：

xxxxxx

```C++
class Solution {
	// 先写一个并查集
	struct UnionFind {
		int cnt;
		vector<int> parent;
		UnionFind(int n) {
			cnt = n;
			parent.resize(n);
			for (int k = 0; k < n; k++) {
				parent[k] = k;
			}
		}
		void merge(int x, int y) {
			int rootX = find(x);
			int rootY = find(y);
			if (rootX != rootY) {
				parent[rootX] = rootY;
				cnt--;
			}
			return;
		}
		int find(int x) {
			if (parent[x] != x) {
				parent[x] = find(parent[x]);
			}
			return parent[x];
		}
		int getCnt() { return cnt; }
	};

public:
	// [[1,2],[1,3],[2,3]]
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		const int n = edges.size();
		// 声明一个flag看一下到底跑没跑出inDegree = 2的点
		bool isExist2 = false;
		// 入度数组，为保持1-based创建n+1个空位
		vector<int>inDegree(n + 1, 0);
		// 记录对应父节点，方便入度为2时直接调取
		vector<int>fathers(n + 1, 0);
		// 创建UnionFind判断连通性
		UnionFind uf(n + 1);
		// 记录可能出现的入度为2情况下的前一个重叠起点边
		int father1;
		// 记录可能出现的入度为2情况下的后一个重叠起点边
		int father2;
		// 记录可能出现的入度为2情况下的终点边
		int errorChild;
		// 记录不考虑入度为2的第一个可能导致循环的错误边
		int cand;
		// 记录是否存在环结构，便于出循环判断入度为2的情况下到底返回哪条边
		bool isFirstCycle = false;
		for (int i = 0; i < n; i++) {
			vector<int>edge = edges[i];
			// 取出起点和中点
			int start = edge[0];
			int end = edge[1];
			// 先更新入度数组
			inDegree[end]++;
			// 如果出现了入度为2
			if (inDegree[end] == 2) {
				// 更新状态
				isExist2 = true;
				// 分别更新三个特殊节点
				father1 = fathers[end];
				father2 = start;
				errorChild = end;
				// 顺便直接检查，如果已经出现联通了，说明新进边本身就不应该存在，直接返回
				if (uf.find(start) == uf.find(end)) {
					return { father2, end };
				}
				// 如果不连通，需等全局的边都跑完在判断是否存在环结构，如存在返回旧边，否则返回新的
			}
			// 如果是一般节点
			else {
				// 正常更新father数组
				fathers[end] = start;
				// 如果遇到环结构，直接记录第一个出现的破坏结构的边的序号并更新状态，便于入度为2的时候判断，以及没有入度为2时的返回
				if (uf.find(start) == uf.find(end)) {
					if (!isFirstCycle) {
						cand = i;
						isFirstCycle = true;
					}
				}
				// 注意，start -> end，参数顺序要调整
				uf.merge(end, start);
			}
		}
		// 先看有没有入度为2
		// 一旦有，最高优先级，一旦存在环结构，返回旧边，否则返回新的
		if (isExist2) {
			if (isFirstCycle) {
				return { father1, errorChild };
			}
			else {
				return { father2, errorChild };
			}
		}
		// 否则正常返回第一个破坏者
		return edges[cand];
	}
};

```

