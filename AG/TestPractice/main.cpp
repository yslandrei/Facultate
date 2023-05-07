#include <iostream>
#include <map>
#include <list>
#include <iterator>
#include <limits>
#include <algorithm>
#include <queue>
using namespace std;

typedef struct cNodes {
	int dest;
	int cost;
}cNode;

class Graph {
private:
	int n = 0, m = 0; // n - varfuri, m - muchii
	map<int, bool> vis;
	map<int, list<int> > adj;
	map<int, list<cNode> > adjC;

public:
	void addEdge(int a, int b) {
		adj[a].push_back(b);
		n = max(n, max(a, b));
		m++;
	}

	void addEdge(int a, int b, int cost) {
		adjC[a].push_back(cNode{ b, cost });
		n = max(n, max(a, b));
		m++;
	}

	void DFS(int v) {
		vis[v] = true;
		cout << v << " ";
		
		for (auto i = adj[v].begin(); i != adj[v].end(); i++)
			if (vis[*i] == false)
				DFS(*i);
	}

	void BFS(int v) {
		vis[v] = true;
		list<int> que;
		que.push_back(v);
		
		while (!que.empty()) {
			v = que.front();
			cout << v << " ";

			for (auto i = adj[v].begin(); i != adj[v].end(); i++)
				if (vis[*i] == false) {
					vis[*i] = true;
					que.push_back(*i);
				}
			que.pop_front();

		}
	}

	void FloydMarshal() {
		int dist[10][10] = { 0 };
		for (int v = 0; v <= n; v++)
			for (auto it = adjC[v].begin(); it != adjC[v].end(); it++)
				dist[v][it->dest] = it->cost;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				if (i != j && dist[i][j] == 0)
					dist[i][j] = INT_MAX;


		for(int k = 0; k <= n; k ++)
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n; j++)
					if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INT_MAX && dist[i][k] != INT_MAX))
						dist[i][j] = dist[i][k] + dist[k][j];

		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				if (dist[i][j] == INT_MAX)
					cout << "inf" << " ";
				else
					cout << dist[i][j] << "   ";
			}
			cout << "\n";
		}
	}

	void Dijkstra(int src) {
		list<int> que;
		int dist[100];
		for (int v = 0; v <= n; v++) {
			que.push_back(v);
			dist[v] = INT_MAX;
		}
		dist[src] = 0;

		while (!que.empty()) {
			int minV, minDist = INT_MAX;
			for (int v : que)
				if (dist[v] < minDist) {
					minDist = dist[v];
					minV = v;
				}

			for (auto i = adjC[minV].begin(); i != adjC[minV].end(); i++)
				if (dist[minV] + i->cost < dist[i->dest])
					dist[i->dest] = dist[minV] + i->cost;

			que.remove(minV);
		}

		for (int v = 0; v <= n; v++)
			cout << src << " -> " << v << " = " << dist[v] << "\n";
	}

	void BelmannFord(int src) {
		int dist[100];
		for (int v = 0; v <= n; v++)
			dist[v] = INT_MAX;
		dist[src] = 0;

		for (int k = 1; k <= n - 1; k++)
			for (int v = 0; v <= n; v++) 
				for (auto i = adjC[v].begin(); i != adjC[v].end(); i++)
					if (dist[v] + i->cost < dist[i->dest])
						dist[i->dest] = dist[v] + i->cost;

		//verificam daca e ciclu negativ infinit
		for (int v = 0; v <= n; v++)
			for (auto i = adjC[v].begin(); i != adjC[v].end(); i++)
				if (dist[v] + i->cost < dist[i->dest]) {
					cout << "Ciclu negativ infinit!";
					return;
				}

		for (int v = 0; v <= n; v++)
			cout << src << " -> " << v << " = " << dist[v] << "\n";
	}
};

int main() {
	Graph g;
	g.addEdge(0, 1, 3);
	g.addEdge(0, 2, 6);
	g.addEdge(1, 0, 3);
	g.addEdge(1, 2, 2);
	g.addEdge(1, 3, 1);
	g.addEdge(2, 1, 6);
	g.addEdge(2, 1, 2);
	g.addEdge(2, 3, 1);
	g.addEdge(2, 4, 4);
	g.addEdge(2, 5, 2);
	g.addEdge(3, 1, 1);
	g.addEdge(3, 2, 1);
	g.addEdge(3, 4, 2);
	g.addEdge(3, 6, 4);
	g.addEdge(4, 2, 4);
	g.addEdge(4, 3, 2);
	g.addEdge(4, 5, 2);
	g.addEdge(4, 6, 1);
	g.addEdge(5, 2, 2);
	g.addEdge(5, 4, 2);
	g.addEdge(5, 6, 1);
	g.addEdge(6, 3, 4);
	g.addEdge(6, 4, 1);
	g.addEdge(6, 5, 1);
	
	g.FloydMarshal();
}