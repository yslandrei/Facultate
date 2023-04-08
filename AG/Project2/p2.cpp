#include <iostream>
#include <fstream>
#include <vector>

#define MAX_INT 9999999

using namespace std;

struct edge {
	int a, b, cost;
};

struct graph {
	int n, e;
	int m[100][100];
}gr;

int main(int agrc, char* argv[]) {
	ifstream f(argv[1]);

	f >> gr.n >> gr.e;

	int a, b, cost;
	for (int i = 0; i < gr.e; i++) {
		f >> a >> b >> cost;
		gr.m[a][b] = cost;
	}

	for (int i = 0; i < gr.n; i++)
		for (int j = 0; j < gr.n; j++) {
			if (gr.m[i][j] == 0 && i != j)
				gr.m[i][j] = MAX_INT;
		}
	for (int k = 0; k < gr.n; k++)
		for (int i = 0; i < gr.n; i++)
			for (int j = 0; j < gr.n; j++)
				gr.m[i][j] = min(gr.m[i][j], gr.m[i][k] + gr.m[k][j]);
	

	f.close();
}