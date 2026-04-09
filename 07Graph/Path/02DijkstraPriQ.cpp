#include<iostream>
#include<vector>
#include<queue>
using namespace std;
// 初始化uint和INF便于表示
using uint = unsigned int;
const uint INF = 0x3f3f3f;
// Dikjistra小根堆优化
void Dikjistra(vector<vector<int>>& graph, int start)
{
    const int n = graph.size();
    vector<bool>used(graph.size(), false);
    vector<uint>dis(graph.size(), INF);
    // 便于复用
    using pair = pair<int, int>;  // 存权值+索引
    priority_queue<pair, vector<pair>, greater<pair>>que;
    used[start] = true;
    dis[start] = 0;
    // 初始化第一轮
    for(int i = 0; i < n; i++)
    {
        dis[i] = graph[start][i];
        if(i != start)
            que.emplace(graph[start][i], i);
    }
    // 无需担心堆会不满，对于老旧节点的清扫在if(used[k])处已经完善，老节点直接丢弃，不再执行下面的更新插入逻辑
    while(!que.empty())
    {
        // 取堆顶
        auto top = que.top();
        // 弹出
        que.pop();
        int k = top.second;
        int minDis = top.first;
        // 如果最小点都脱离S集合图，直接退出循环
        if(minDis == INF)
            break;
        // 用过的点无需继续执行下面的更新逻辑
        if(used[k])
            continue;
        // 记得改状态
        used[k] = true;
        for(int j = 0; j < n; j++)
        {
            if(used[j] == false && dis[k] + graph[k][j] < dis[j])
            {
                // 不要忘记更新dis记录数组
                dis[j] = dis[k] + graph[k][j];
                que.emplace(dis[k] + graph[k][j], j);
            }
        }
    }
    // 打印信息
    for(auto u : dis){
        cout << u << " ";
    }
    cout << endl;
    return;
}


// 1 建堆
// 1.1 首先我们建立优先级队列priority_queue<TypeName>
// 我们知道，我们需要获取的是每轮的权值最小顶点Vertex，那么必须使用小根堆以保证取堆顶始终能获得当前堆内的最小元素！而STL::queue::priority_queue默认的是大根堆，因此我们要自行传入比较器Comp;
// 1.2 其次，我们发现，仅有一个权值参数，信息太少！不足以支撑我们在后续更新的遍历过程中找到这个权值最小点和其他尚未处理的点在vector<vector<int>>Graph上的数量关系（graph[k][j]）。因此我们想到pair作为堆的存储比较单元
// 1.3 pair的参数顺序应为 <权值, 索引>，因为STL提供的pair方法默认的operator比较是first字典比较，为避免重写仿函数重载比较规则，我们遵循权值+索引的顺序！
// 由上述推理我们知道建堆的正确方式：
// 	using pair = pair<int, int>  // 权值, 索引
// 	priority_queue<pair, vector<pair>, greater<pair>>que;  // 数据类型, 容器, 比较器
// 2 初始化
// 	唯一需要注意的是，在第一轮O(N)遍历中，start对应的顶点无需入堆
// 3 处理堆顶
// 3.1 每次操作过程我们知道，当取出auto top = que.top(); 时，top对应的就是当前Uset中权值最小的那一个顶点，取出有效数据top后，我们可以声明int k = top.second; 以及 int minDis = top.first分别记录最小顶点索引和最小距离；获取有效数据，弹出堆顶无用元素！que.pop();
// 3.2 而后就是验证当前堆顶顶点top的合法性，可能出现以下两种情况：
// 	-3.2.1 minDis == INF 最小节点已经是游离于start_Vertex域外的顶点：立刻break; 无需继续操作
// 	-3.2.2 used[k] = true 已经使用过的老顶点：说明在此前已经处理过该顶点（为什么在while循环控制条件说），无需继续处理，continue; 
// 3.3 而后，在确保顶点合法性的情况下，我们进行更新
// 4 更新
// 4.1 更新逻辑以及for循环对dis数组的更新和普通Dijkistra几乎一样，不在赘述；
// 4.2 对堆的更新：相对复杂，我们知道对堆内元素，我们希望可以直接操纵每一个元素实时更新避免内存中单元的浪费，但由于堆本身只可以看见堆顶的属性，我们不能这样做，有效的操作只有push和pop;
// 那么我们想到可以利用push，used数组的记录规避新老节点同时存在的问题，当未处理节点存在更小的dis数组时，新的pair就会被推入堆中，此时由小根堆的排序性质，其一定会在老顶点数据前出堆，因此在老顶点出堆时，新老顶点所代表的同一节点不同时段的状态都会被used数组标记为已使用，因此一定会走3.2.2的路径，不会干扰到其他节点！
// 5 while循环终止条件
// 为什么选取!que.empty()就一目了然了，因为3.2.2 4.2两条原则，保证了每一个无论新老的节点都一定会在最终被弹出，但新节点的入堆条件苛刻，直观感受显然最终堆会空（当然可以严格推导，这里不作为中点讨论）！而堆空就意味着所有节点都处理完，Uset中的有效点全部更新后转移到Sset，程序结束，等待打印dis数组

