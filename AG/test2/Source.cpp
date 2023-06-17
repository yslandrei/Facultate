#include <limits.h>
#include <string.h>
#include <iostream>
#include <queue>
using namespace std;

int n, m, e;
int graph[100][100];

bool bfs(int s, int t, int parent[]) {
    bool visited[100];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < 100; v++)
            if (visited[v] == false && graph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
    }

    return (visited[t] == true);
}

int fordFulkerson(int s, int t) {
    int u, v;
    int parent[100];
    int maxFlow = 0;

    while (bfs(s, t, parent)) {
        int pathFlow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            if (graph[u][v] < pathFlow)
                pathFlow = graph[u][v];
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            graph[u][v] -= pathFlow;
            graph[v][u] += pathFlow;
        }
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    
    cin >> n >> m >> e;
    for (int i = 0; i < e; i++) {
        int x, y;
        cin >> x >> y;
        graph[x][y + n] = 1;
    }
    
    //leg nodul 0 de L
    for (int i = 1; i <= n; i++)
        graph[0][i] = 1;

    //leg ultimul nod de R
    for (int i = n + 1; i <= n + m; i++)
        graph[i][n + m + 1] = 1;

    cout << fordFulkerson(0, n + m + 1);
}