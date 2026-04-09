#include<iostream>
#include<vector>
#include<queue>
#include<climits>
using namespace std;
using uint = unsigned int;
const uint INF = INT_MAX / 2;
void Dijkstra(vector<vector<uint>>& graph, int start)
{
    vector<uint>dis(graph.size(), INF);
    vector<bool>isUsed(graph.size(), false);
    isUsed[start] = true;
    // 先初始化一遍
    int N = graph.size();
    for(int i = 0; i < N; i++)
    {
        dis[i] = graph[start][i];
    }
    // 开始循环，循环 N - 1次
    for(int i = 0; i < N - 1; i++)
    {
        // 初始化k min 找最小当轮顶点
        int k = -1;
        uint min = INF;
        for(int j = 0; j < N; j++)
        {
            if(isUsed[j] == false && dis[j] < min)
            {
                min = dis[j];
                k = j;
            }
        }
        // 如果压根没有更新，说明剩下的都是游离的断点，无法与start构成有效链接
        if(k == -1)
        {
            break;
        }
        // 一定不要忘记改状态！！！
        isUsed[k] = true;
        // 更新剩余部分
        for(int j = 0; j < N; j++)
        {
            if(isUsed[j] == false)
            {
                dis[j] = std::min(dis[j], min + graph[k][j]);
            }
        }
    }
    for(auto& u : dis)
    {
        cout << u << " ";
    }
    return;
}
int main()
{
	vector<vector<uint>>graph =
	{
		{ 0, 6, 3, INF, INF, INF },
		{ 6, 0, 2, 4, INF, INF },
		{ 3, 2, 0, INF, 8, INF },
		{ INF, 4, INF, 0, 2, 7 },
		{ INF, INF, 8, 2, 0, 3 },
		{ INF, INF, INF, 7, 3, 0 }
	};
    Dijkstra(graph, 2);
    return 0;
}
