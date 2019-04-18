#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

#define INF INT_MAX;
using namespace std;
const int DIM = 10000;

vector < int > tree(DIM);
vector < int > v(DIM);

ifstream f("date.in");
ofstream g("date.out");
int N;
void read(){
  f >> N;

  for ( int i = 1; i <= N; ++i )
    f >> v[i];
}

void write( int dim ){
  for ( int i = 1; i <= 2*dim ; ++i )
    g << "Tree[" << i << "] = " << tree[i] << endl;
  g << endl << endl;
}


void build (int tata, int st, int dr){
  if ( st == dr )
  {
    tree[ tata ] = v[ st ];
    return;
  }
    int mij = ( st + dr ) / 2;
    build ( 2 * tata, st, mij ); // ramura stanga
    build ( 2 * tata + 1, mij + 1, dr ); // ramura stanga
    tree [ tata ] = min ( tree [ tata * 2 ] , tree[ tata * 2 + 1 ] );

}

int querry( int tata, int x, int y, int st, int dr  )
{
    if( x <= st && y >= dr )
        {
            return tree[tata];
        }

    int mij = ( st + dr ) / 2 ,fs, fd;

    if ( y < st || x > dr )
      return INF;

    fs = querry( 2 * tata, x, y, st, mij );
    fd = querry( 2 * tata + 1, x, y, mij + 1, dr );
    return min( fs, fd );
}

void update(int tata, int st, int dr, int pos, int new_val){
  if ( st == dr )
  {
    tree[tata] = new_val;
    return;
  }
  int mij = ( st + dr ) / 2;
  if ( pos <= mij )
    update ( tata * 2, st , mij, pos ,new_val);
  else
    update ( tata * 2 + 1 , mij+ 1, dr, pos, new_val);

  tree[tata] = min ( tree[tata*2], tree[tata * 2 + 1]);
}
int main()
{
  read();
  build(1, 1, N );
  write(N);
  g << endl;
  int m;
  f >> m;
  for ( int i = 0 ; i < m ; ++i )
    {
      int t;
      f >> t;
      if ( t == 0 )
      {
        int x, y;
        f >> x >> y;
        g << "Pe intervalul de indici (" << x << "," << y <<"), min = " << querry(1, x, y, 1, N) << endl;
      }
      else
      {
        int pos, val;
        f >> pos >> val;
        g << "Updated" << endl;
        update(1,1,N,pos,val);
        write(N);
      }
    }
}
