#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main() {

    int matrice_adiacenta[10][10] = { 0 };
    int matricea_distantelor[10][10];
    int n, m, a, b, ok;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b;
        matrice_adiacenta[a - 1][b - 1] = 1;
        matrice_adiacenta[b - 1][a - 1] = 1;
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            matricea_distantelor[i][j] = 99999;
        }
    }

    // noduri izolate
    cout << "Noduri Izolate: ";
    int global_ok = 1;
    for (int i = 0; i < m; ++i) {
        ok = 0;
        for (int j = 0; j < m; ++j) {
            if (matrice_adiacenta[i][j] == 1) {
                ok = 1;
            }
        }
        if (!ok) {
            cout << i + 1 << " ";
            global_ok = 0;
        }
    }
    if (global_ok) {
        cout << "Nu are noduri izolate!\n";
    }
    else {
        cout << "\n";
    }

    // graf regulat

    int cnt = -1;
    ok = 1;
    for (int i = 0; i < m; ++i) {
        int cnt_min = 0;
        for (int j = 0; j < m; ++j) {
            if (matrice_adiacenta[i][j] == 1) {
                cnt_min++;
            }
        }
        if (cnt == -1) {
            cnt = cnt_min;
        }
        if (cnt != cnt_min) {
            ok = 0;
            break;
        }
    }
    if (ok) {
        cout << "Este graf regulat!\n";
    }
    else {
        cout << "Nu este graf regulat\n";
    }

    // matricea distantelor

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrice_adiacenta[i][j] == 1) {
                matricea_distantelor[i][j] = matrice_adiacenta[i][j];
            }
        }
    }

    for (int k = 0; k < m; ++k) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (matricea_distantelor[i][k] != 99999 and matricea_distantelor[k][j] != 99999) {
                    if (matricea_distantelor[i][j] > matricea_distantelor[i][k] + matricea_distantelor[k][j]) {
                        matricea_distantelor[i][j] = matricea_distantelor[i][k] + matricea_distantelor[k][j];
                    }
                }
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matricea_distantelor[i][j] == 99999)
                matricea_distantelor[i][j] = 0;
            cout << matricea_distantelor[i][j] << " ";
        }
        cout << "\n";
    }

    ok = 1;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <m; ++j) {
            if (matricea_distantelor[i][j] == 0) {
                ok = 0;
            }
        }
    }

    if (ok) {
        cout << "Graful este conex" << "\n";
    }
    else {
        cout << "Graful nu este conex" << "\n";
    }


    return 0;
}
