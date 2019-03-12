#include <iostream>
#include <fstream>
#include <vector>

#define NLIM 1000005
using namespace std;

ifstream f("berarii2.in");
ofstream g("berarii2.out");

vector < vector < int > > Edges;
vector < int > Help;
vector < int > Beers;
vector < int > Res;

bool beenThere[NLIM];

int N, M, P; /// noduri , muchii , nr.berarii;
void Read()
{
    f >> N >> M >> P;
    int x, y;
    Edges.assign(N+1,Help);

    for ( int i = 1 ; i <= M; i++ )
    {
        f >> x >> y;
        Edges[y].push_back(x);
    }

    for ( int i = 1 ; i <= P; i++ )
    {
        f >> x;
        Beers.push_back(x);
    }
    /*for ( int j = 1;  j <= N ; ++j )
    {
        cout << j << " ";
        for ( unsigned int i = 0 ; i < Edges[j].size() ; ++i )
            cout << i << " ",
            cout << Edges[j][i] << " " << endl ;
        cout << endl;
    }
    cin.get();*/
}

void DFS( int node )
{
    beenThere[node] = true;
    for ( unsigned int i = 0 ; i < Edges[node].size() ; i++ )
    {
        if(!beenThere[Edges[node][i]])
            DFS(Edges[node][i]);
    }
}

void Solve()
{
    for ( unsigned int i = 0; i < Beers.size() ; i++)
        if(!beenThere[Beers[i]])
            DFS(Beers[i]);

    for ( int i = 1 ; i <= N ; i++ )
        if (!beenThere[i])
            Res.push_back(i);

    g << Res.size() << "\n";

    for ( unsigned int i = 0 ; i < Res.size() ; i++ )
        g << Res[i] << "\n";
}
int main()
{
    Read();
    Solve();
    return 0;
}
