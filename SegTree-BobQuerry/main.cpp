#include <iostream>
#include <vector>
#include <fstream>
#include <climits>

#define INF INT_MAX;
using namespace std;
const  int DIM = 5000000;

vector < int > tree(DIM);
vector < int > v(DIM);

ifstream f("date.in");
ofstream g("date.out");
int N, Q;

void write( long long int dim ){
  for ( int i = 1; i <= 2*dim ; ++i )
    g << "Tree[" << i << "] = " << tree[i] << endl;
  g << endl << endl;
}


int querry( int tata, int x, int y, int st, int dr  )
{
    if( x <= st && y >= dr )
        {
            return tree[tata];
        }

    int mij = ( st + dr ) / 2 ,fs, fd;

    if ( y < st || x > dr )
      return 0;

    fs = querry( 2 * tata, x, y, st, mij );
    fd = querry( 2 * tata + 1, x, y, mij + 1, dr );
    return fd + fs;
}

void updateType1(int tata, int st, int dr, int pos){
  if ( st == dr )
  {
    tree[tata] += 1;
    return;
  }
  int mij = ( st + dr ) / 2;
  if ( pos <= mij )
    updateType1 ( tata * 2, st , mij, pos);
  else
    updateType1 ( tata * 2 + 1 , mij+ 1, dr, pos);

  tree[tata] =  tree[tata*2] + tree[tata * 2 + 1];
}

void updateType2(int tata, int st, int dr, int pos){
  if ( st == dr )
  {
    if(tree[tata] > 0)
    {
    tree[tata] -= 1;
    return;
    }
    else
    return;
  }
  int mij = ( st + dr ) / 2;
  if ( pos <= mij )
    updateType2 ( tata * 2, st , mij, pos);
  else
    updateType2 ( tata * 2 + 1 , mij+ 1, dr, pos);

  tree[tata] = tree[tata*2] + tree[tata * 2 + 1];
}

int main()
{
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);
  cin >> N >> Q;
  for ( int i = 0 ; i < Q ; ++i )
    {
      int type ;
      cin >> type;
      if ( type == 1 ){
        int pos;
        cin >> pos;
        updateType1(1,1,N,pos);
      }
      if ( type == 2 ){
        int pos;
        cin >> pos;
        updateType2(1,1,N,pos);
      }

      if ( type == 3 ){
        int x, y;
        cin >> x >> y;
        cout << querry(1,x,y,1,N) << endl;
      }

    }

return 0;
}
