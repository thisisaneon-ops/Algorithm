#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<sstream>
#include<fstream>
#include<cstdlib>
using namespace std;

class MyGraph
{
public:
	void readFile(string FilePath)
	{
		ifstream pf(FilePath);
		if (!pf.is_open())
		{
			cout << "FilePath Error" << endl;
			return;
		}
		hVer_.emplace_back("");
		string label;
		while (getline(pf, label, '\n'))
		{
			hVer_.emplace_back(label);
			string seeds;
			if (getline(pf, seeds, '\n'))
			{
				stringstream ss(seeds);
				string seed;
				while (getline(ss, seed, ','))
				{
					hVer_.back().Adjlist_.emplace_back(stoi(seed));
				}
			}
		}
		pf.close();
	}

	void print() const
	{
		for (int i = 1; i < hVer_.size(); i++)
		{
			cout << hVer_[i].label_ << " ： ";
			for (auto& u : hVer_[i].Adjlist_)
			{
				cout << u << " ";
			}
			cout << endl;
		}
	}

	void DFS()
	{
		vector<bool>visited(hVer_.size(), false);
		visited[0] = true;
		DFS(1, visited);
	}

	void BFS()
	{
		vector<bool>visited(hVer_.size(), false);
		queue<int>q;
		visited[0] = true;
		q.push(1);
		visited[1] = true;
		while (!q.empty())
		{
			int front = q.front();
			q.pop();
			cout << hVer_[front].label_ << " ";
			for (auto& i : hVer_[front].Adjlist_)
			{
				if (visited[i] == false)
				{
					q.push(i);
					visited[i] = true;
				}
			}
		}
		cout << endl;
	}

	void shortCut(int start, int end)
	{
		vector<bool>visited(hVer_.size(), false);
		queue<int>q;
		vector<int>Path(hVer_.size(), 0);
		visited[0] = true;
		q.push(start);
		visited[start] = true;
		while (!q.empty())
		{
			int front = q.front();
			q.pop();
			if (front == end)
			{
				break;
			}
			for (auto& i : hVer_[front].Adjlist_)
			{
				if (visited[i] == false)
				{
					q.push(i);
					visited[i] = true;
					Path[i] = front;
				}
			}
		}
		// 出循环的两种可能： 1. q.empty()  2. front == end;
		if (!q.empty())
		{
			while (end != 0)
			{
				cout << hVer_[end].label_ << "<==";
				end = Path[end];
			}
		}
		else
		{
			cout << "So such cut" << endl;
		}
		cout << endl;
	}

private:
	void DFS(int i, vector<bool>& visited)
	{
		if (visited[i] == true)
		{
			return;
		}
		cout << hVer_[i].label_ << " ";
		visited[i] = true;
		for(auto& u : hVer_[i].Adjlist_)
		{ 
			DFS(u, visited);
		}
	}

private:
	struct Vertex
	{
		Vertex(string label)
			: label_(label)
		{
		}
		string label_;
		list<int>Adjlist_;
	};
	vector<Vertex>hVer_;
};


int main()
{
	MyGraph graph;
	graph.readFile("Graphdata.txt");
	graph.print();
	cout << "DFS" << endl;
	graph.DFS();
	cout << endl << "BFS" << endl;
	graph.BFS();
	cout << endl;
	graph.shortCut(2,5);
	return 0;
}
