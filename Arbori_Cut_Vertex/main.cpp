#include <iostream>
#include <fstream>
#include <vector>

#define DIM 100
using namespace std;

typedef vector < int > v;

vector < v > Tree;

bool beenThere[DIM], CutVertex[DIM];
int parinte[DIM],disc[DIM];
int moment;
int N, M;

void Read()
{
    ifstream f("date.in");
    f >> N >> M;

    Tree.assign(N+1, v() );

    for ( int i = 1 ; i <= M ; ++i )
    {
        int x, y;
        f >> x >> y;
        Tree[x].push_back(y);
        Tree[y].push_back(x);
    }

}

void DFS( int curent , int p = -1 )
{
    beenThere[curent] = true;
    parinte[curent] = disc[curent] = ++moment;
    int child = 0;

    for ( auto vecin : Tree[curent])
    {
         if ( vecin == p )
            continue;
       // cout << beenThere[vecin]
         if (beenThere[vecin])
         {
             parinte[curent] = min ( parinte[curent] , disc[vecin]);
         }
             else
             {
                 DFS( vecin, curent );
                 parinte[curent] = min ( parinte[curent] , parinte[vecin]);
                 if ( parinte[vecin] >= disc[curent] && p != -1)
                    CutVertex[curent] = true,
                    child++;
             }
    }

    if ( p == -1 && child >= 1)
        CutVertex[curent] = true;
}
int main()
{
    Read();
    DFS(1);
    for ( int i = 1 ; i <= N ; ++ i)
        if( CutVertex[i] == true)
            cout << i << " ";
    return 0;
}
