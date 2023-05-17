#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int n, head;

void getLeafs(int ver, vector<int> v, vector<int>& leafs) {
	bool isLeaf = true;
	for (int i = 0; i < n; i++) {
		if (v[i] == ver) {
			isLeaf = false;
			getLeafs(i, v, leafs);
		}
	}
	if (isLeaf)
		leafs.push_back(ver);
}

int main(int argc, char** argv) {
	ifstream f(argv[1]);
	ofstream g(argv[2]);

	vector<int> v, prufer, leafs;

	f >> n;
	for (int i = 0; i < n; i++) {
		int x;
		f >> x;
		v.push_back(x);
		if (v.back() == -1)
			head = i;
	}
	g << n - 1 << "\n";
	int k = n;
	while (k > 1) {
		leafs.clear();
		getLeafs(head, v, leafs);
		int minLeaf = INT_MAX;
		for (int i = 0; i < leafs.size(); i++)
			if (leafs[i] < minLeaf)
				minLeaf = leafs[i];
		g << v[minLeaf] << ' ';
		v[minLeaf] = INT_MAX;
		k--;
	}

	f.close();
	g.close();
}
