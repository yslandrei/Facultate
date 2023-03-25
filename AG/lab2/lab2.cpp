//5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de apelul 
//recursiv al procedurii DFS_VISIT(G, u) (apadurea descoperită de DFS).

#include <iostream>
#include <stdlib.h>
#include <map>
#include <list>
using namespace std;

int n;
map<int, bool> visited;
map<int, list<int> > adj;

void DFS(int v) {
	visited[v] = true;
	
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (visited[*i] == 0)
			DFS(*i);
}


int main() {
	int v, w;

	cin >> n;
	for (auto i = 0; i < n; i++) {
		cin >> v >> w;
		adj[v].push_back(w);
		adj[w].push_back(v);
	}

	DFS(5);

	cout << "Vizitati: ";
	for (auto i = 0; i < visited.size(); i++)
		if(visited[i])
			cout << i << " ";
}