#include <iostream>
#include <algorithm>
#include "vector.h"
#include "offer.h"
using namespace std;

bool cmp(const offer& a, const offer& b) {
    return a.getId() > b.getId();
}

int main() {
    vector<offer> v;
    v.push_back(offer(0, "nume", "dest", "tip", 100));
    v.push_back(offer(1, "num1e", "des1t", "t1ip", 200));
    v.push_back(offer(3, "num1e", "des1t", "t1ip", 200));
    v.push_back(offer(2, "num1e", "des1t", "t1ip", 200));

    sort(v.begin(), v.end(), cmp);
    v.erase(v.begin());
    v.print();
    if (v[0] == v[1])
        cout << "sugi";
    if (v[0] != v[1])
        cout << "nu sugi";
    
    _CrtDumpMemoryLeaks();
    return 0;
}