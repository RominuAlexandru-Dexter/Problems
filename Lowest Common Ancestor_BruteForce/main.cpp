#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

using namespace std;

typedef vector < int > vi;
vector < vi > ListaAdiacenta;
bitset < 1000 > beenThere;
bitset < 1000 > LCA;
int N, M, first_node, second_node,radacina;

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

    f >> first_node >> second_node;
}

void DFS_first( int nod ){
  beenThere[nod] = true;
  if ( nod != radacina )
  for ( auto &it: ListaAdiacenta[nod] )
    {
      if ( !beenThere[it] )
      {
        LCA[it] = true;
        DFS_first( it );
      }
    }

}

void DFS_second( int nod ){
  beenThere[nod] = true;
  for ( auto &it: ListaAdiacenta[nod] )
    {
      if ( !beenThere[it] )
      {
        if (LCA[it] == true)
          {
            g << it;
            break;
          }
        else
          DFS_second( it );
      }
    }

}
int main()
{

  read();
  LCA[first_node] = true;
  DFS_first(first_node);
  beenThere.reset();
  if (LCA[second_node] != true)
    DFS_second(second_node);
  else
    g << second_node;

}
