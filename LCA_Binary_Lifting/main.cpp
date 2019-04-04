#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

ifstream f("date.in");
typedef vector < int > vi;
vector < vi > ListaAdiacenta;
vector < vi > up;

vi tin, tout;

int N, L, timer;
void readTree(){

  f >> N;
  ListaAdiacenta.assign( N + 1, vi() );

  for ( int i = 0 ; i < N - 1 ; ++i )
  {
    int x, y;
    f >> x >> y;
    ListaAdiacenta[x].push_back(y);
    ListaAdiacenta[y].push_back(x);
  }
}
bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

void DFS(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= L; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (auto &u : ListaAdiacenta[v]) {
        if (u != p)
            DFS(u, v);
    }

    tout[v] = ++timer;
}

void preprocess( int root ){
  tin.resize( N+1 );
  tout.resize( N+1 );
  timer = 0;
  L = ceil(log2(N));
  up.assign(N+1 , vi(L+1));
  DFS(root, root);
}


int LCA(int u , int v){
  if (is_ancestor(u, v))
      return u;
  if (is_ancestor(v, u))
      return v;
  for (int i = L; i >= 0; --i) {
      if (!is_ancestor(up[u][i], v))
          u = up[u][i];
  }
  return up[u][0];
}
int main()
{
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);
  readTree();
  int querries;
  f >> querries;
  for ( int i = 0 ; i < querries ; ++i )
  {
    int root, u ,v;
    f >> root >> u >> v;
    preprocess(root);
    cout << LCA(u,v) << endl;
  }
}
