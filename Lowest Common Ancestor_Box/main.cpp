#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

typedef vector < int > vi;
vector < vi > ListaAdiacenta;
vi ListaNiveleNoduri(1000) , ListaTati(1000), Stramosi(1000), Inaltime(1000) ;
bitset < 1000 > beenThere;
int N, M, first_node, second_node,radacina;
int hMax;
ofstream g("date.out");
void read(){
  ifstream f("date.in");

  f >> N >> M >> radacina;

  ListaAdiacenta.assign( N+1, vi() );

  for ( int i = 0 ; i < M ; ++i )
    {
      int x, y;
      f >> x >> y;
      ListaAdiacenta[x].push_back(y);
      ListaAdiacenta[y].push_back(x);

    }

}

void DFS(int nod, int nivel){
  beenThere[nod] = true;
  ListaNiveleNoduri[nod] = nivel;

  if ( hMax < nivel )
    hMax = nivel;

  for ( auto &it : ListaAdiacenta[nod] )
  {
    if (!beenThere[it])
    {
      ListaTati[it] = nod;
      DFS(it,nivel+1);
    }
  }
}

void DFS_Stramosi( int nod, int tx, int nivel ){
  Stramosi[nod] = tx;
  Inaltime[nod] = nivel;

  if( nivel % hMax == 0 )
    tx = nod;

  for( int i = 0 ; i < N ; ++ i )
    {
      if(ListaTati[i] == nod )
        DFS_Stramosi(i , tx, nivel + 1 );
    }

}

void LCA ( int x , int y ){
  while ( Stramosi[x] != Stramosi[y] )
    {
      if( Inaltime[x] > Inaltime[y] )
        x = Stramosi[x];
      else
        y = Stramosi[y];
    }

  while ( x != y)
  {
    if ( Inaltime[x] > Inaltime[y] )
      x = ListaTati[x];
    else
      y = ListaTati[y];
  }

  g <<  x;
}
int main()
{

  read();
  DFS(radacina,0);

  DFS_Stramosi(radacina, radacina, 0);

  LCA(16,5);
}
