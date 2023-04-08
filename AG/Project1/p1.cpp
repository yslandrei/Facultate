#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>

using namespace std;

struct edge {
	int a, b, cost;
};

struct graph {
	int n, e;
	vector<edge> edges;
}gr;

int main(int agrc, char* argv[]) {
	ifstream f(argv[1]);
	ofstream g(argv[2]);


	int source;
	bool visited[100] = { 0 };
	int dist[100];
	f >> gr.n >> gr.e >> source;

	int a, b, cost;
	for (int i = 0; i < gr.e; i++) {
		f >> a >> b >> cost;
		gr.edges.push_back(edge{ a, b, cost });
	}

	for (int i = 0; i < gr.n; i++)
		dist[i] = INT_MAX;
	dist[source] = 0;

	for (int i = 1; i < gr.n; i++)
		for (int j = 0; j < gr.e; j++)
			if (dist[gr.edges[j].a] != INT_MAX && dist[gr.edges[j].a] + gr.edges[j].cost < dist[gr.edges[j].b])
				dist[gr.edges[j].b] = dist[gr.edges[j].a] + gr.edges[j].cost;

	for (int i = 0; i < gr.n; i++) {
		if (dist[i] == INT_MAX) {
			g << "INF ";
			continue;
		}
		g << dist[i] << " ";
	}

	f.close();
	g.close();
}