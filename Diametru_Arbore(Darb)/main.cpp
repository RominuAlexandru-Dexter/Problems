#include <iostream>
#include <fstream>
#include <vector>

#define NLIM 100005
using namespace std;

vector < vector < int > > Edges;
vector < int > Help;

ifstream f ("darb.in");
ofstream g ("darb.out");
bool beenThere[NLIM];
int N;
int pozitieNivel, nivelMaxim;

void DFS( int node , int nivel)
{
    beenThere[node] = true;

    if (nivel > nivelMaxim)
        nivelMaxim = nivel,
        pozitieNivel = node;

    for ( unsigned int i = 0 ; i < Edges[node].size() ; ++i )
        if (!beenThere[Edges[node][i]])
            DFS(Edges[node][i], nivel + 1);
}
void Read()
{
    int x, y;
    f >> N;
    Edges.assign(N+1 , Help);

    for ( int i = 1; i <= N; ++i )
    {
        f >> x >> y;
        Edges[x].push_back(y);
        Edges[y].push_back(x);
    }

    DFS(1,0);

    fill(beenThere, beenThere + N+1, false);

    DFS(pozitieNivel,0);

    g << nivelMaxim + 1;
}
int main()
{
    Read();
    return 0;
}
