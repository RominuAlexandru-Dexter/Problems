#include <fstream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <bitset>

using namespace std;

bitset < 2019 > beenThere;

typedef vector < int > vi;
vector < vi > ListaAdiacenta;
vi adancime (2019);

int stramosi[12][2019];
int N, M;
void read(){
  ifstream f("date.in");
  f >> N >> M;

  ListaAdiacenta.assign(N+1, vi() );

  for ( int i = 0 ; i < M ; ++i )
    {
      int x, y;
      f >> x >> y;

      ListaAdiacenta[x].push_back(y);
      ListaAdiacenta[y].push_back(x);
    }

  memset (stramosi, -1, sizeof(stramosi));

}

void DFS( int nod ){
  beenThere[nod] = true;

  for ( auto &it: ListaAdiacenta[nod])
    {
      if (!beenThere[it])
      {
        adancime[it] = adancime[nod] + 1;
        stramosi[0][it] = nod;
        DFS(it);
      }
    }

}

void completeMatrix(){
  for ( int i = 1;  i < 12 ; ++i)
  {
    for ( int j = 0 ; j < N ; ++ j )
    {
      if( stramosi[i-1][j] != -1 )
        stramosi[i][j] = stramosi[i-1][ stramosi[i-1][j] ];
    }
  }
}

int urcaPrimul( int de_urcat, int tinta){
  int aux = de_urcat;

  for ( int i = 0;  i < 12 ; ++i)
  {
    if (tinta & 1 != 0)
      aux = stramosi[i][aux];
    tinta = tinta >> 1;
  }
  return aux;
}

int LCA(int A, int B ){

  if ( adancime[A] > adancime[B] )
    A = urcaPrimul(A, adancime[A] - adancime[B]);
  else if ( adancime[A] < adancime[B] )
          B = urcaPrimul(B, adancime[B] - adancime[A]);

  if ( A == B )
    return A;


  for ( int i = 12; i >= 0; --i )
  {
    if (stramosi[i][A] != stramosi[i][B])
      A = stramosi[i][A],
      B = stramosi[i][B];
  }

  return stramosi[0][A];

}
int main()
{
  read();
  DFS(1);
  completeMatrix();
  cout << LCA(5,7);
}
