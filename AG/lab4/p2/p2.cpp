#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <iterator>
using namespace std;

int findSmallest(list<int> v){
  bool a[1000] = { 0 };
  list<int>::iterator it;
  for(it = v.begin(); it != v.end(); ++it){
    a[*it] = 1;
  }
  for(int i = 0; i < 1000; i ++){
    if(a[i] == 0)
      return i;
  }
  return -1;
}

int main(int argc, char** argv){
  ifstream f(argv[1]);
  ofstream g(argv[2]);
  
  int n;
  list<int> prufer;
  int v[1000];
  f >> n;
  for(int i = 0; i < n; i ++){
    int x;
    f >> x;
    prufer.push_back(x);
  }

  for(int i = 0; i < n - 1; i ++){
    int y = findSmallest(prufer);
    int x = prufer.front();
    cout << x << " " << y << "\n";
    prufer.pop_front();
    prufer.push_back(y);
  }

  f.close();
  g.close();
}
