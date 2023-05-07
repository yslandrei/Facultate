#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <limits>
using namespace std;

ifstream fin("test1.in");

int isAciclic = true;

class Graph {
public:
	int n = 0, m = 0;
	map<int, list<int> > adj;
	map<int, bool> vis;

	void addEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	void DFS(int v, int par) {
		vis[v] = true;
		//cout << v << " ";

		for (auto it = adj[v].begin(); it != adj[v].end(); it++) {
			if (vis[*it] == false)
				DFS(*it, v);
			else if(*it != par) {
				isAciclic = false;
				return;
			}
		}
	}
};

int main() {
	Graph g;
	int a, b;

	fin >> g.n >> g.m;
	for (int i = 0; i < g.m; i++) {
		fin >> a >> b;
		g.addEdge(a, b);
	}
	
	for (auto v : g.adj) {
		if (g.vis[v.first] == false)
			g.DFS(v.first, -1);
	}
	
	if (isAciclic)
		cout << "DA";
	else
		cout << "NU";
}