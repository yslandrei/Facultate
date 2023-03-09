#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("in.txt");

typedef struct {
	int a, b;
}adi;
	
int n;
int ma[10][10]; // matrice de adiacenta
int mi[10][10]; // matrice de incidenta
int la[10][10]; // lista de adiacenta

int main() {
	
	int x, y, maxNode = 0;
	fin >> n;
	for (int i = 0; i < n; i++) {
		fin >> x >> y;
		ma[x][y] = ma[y][x] = 1;
		if (x == y)
			ma[x][y] = 1;
		if (x > maxNode)
			maxNode = x;
		if (y > maxNode)
			maxNode = y;
	}
	cout << "Matrice de adiacenta\n";
	for (int i = 1; i <= maxNode; i++) {
		for (int j = 1; j <= maxNode; j++)
			cout << ma[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";

	// matrice de adiacenta => lista de adiacenta
	int grade;
	for (int i = 1; i <= maxNode; i++) {
		grade = 0;
		for (int j = 1; j <= maxNode; j++) {
			if (ma[i][j] == 1)
				la[i][++grade] = j;
		}
		la[i][0] = grade;
	}
	cout << "Lista de adiacenta\n";
	for (int i = 1; i <= maxNode; i++) {
		int j = 0;
		while (la[i][j]) {
			cout << la[i][j] << " ";
			j++;
		}
		cout << "\n";
	}

	// lista de adiacenta => matrice de incidenta
	int line = 0;
	for (int i = 1; i <= maxNode; i++) {
		int j = 1;
		while (la[i][j]) {
			//mi[la[i][j]][z++] = 1;
			if(i < la[i][j]) {
				line++;
				mi[i][line] = 1;
				mi[la[i][j]][line] = 1;
			}
			j++;
		}
	}
	cout << "\n";
	cout << "Matrice de incidenta\n";
	for (int i = 1; i <= maxNode; i++) {
		for (int j = 1; j <= n; j++)
			cout << mi[i][j] << " ";
		cout << "\n";
	}
}
