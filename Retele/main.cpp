#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

#define DIM 50016
using namespace std;

typedef vector < int > vi;

vector < vi > Graph_Normal;
vector < vi > Graph_Transpose;
vector < vi > Componente;
stack < int > Stack;
bool beenThere[DIM];
int N, M, NrComp;

void Read()
{
    ifstream f("retele.in");

    f >> N >> M;

    Graph_Normal.assign( N+1, vi() );
    Graph_Transpose.assign( N+1, vi() );
    Componente.assign( N+1, vi() );

    for ( int i = 0 ; i < M ; ++i )
    {
        int x, y;
        f >> x >> y;

        Graph_Normal[x].push_back(y);
        Graph_Transpose[y].push_back(x);
    }

    f.close();

}

void DFS_Normal ( int node )
{
    beenThere[node] = true;
    for ( auto &i : Graph_Normal[node])
        if(!beenThere[i])
            DFS_Normal(i);

    Stack.push(node);
}

void DFS_Transpose ( int node )
{
    beenThere[node] = true;
    Componente[NrComp].push_back(node);

    for ( auto &i : Graph_Transpose[node] )
        if(!beenThere[i])
            DFS_Transpose(i);

}
void Kosaraju()
{
    for ( int i = 1; i <= N ; ++i)
        if (!beenThere[i])
            DFS_Normal(i);

    fill(beenThere, beenThere+N+1, false);

    while(!Stack.empty())
    {
        int nod = Stack.top();
        Stack.pop();

        if(!beenThere[nod])
        {
            DFS_Transpose(nod);
            NrComp++;
        }
    }
}
bool comp( vector<int>& vec1,  vector<int>& vec2){


    for(unsigned i = 0; i < vec1.size() && i < vec2.size(); i++)
    {
         if(vec1[i] > vec2[i])
         {
             return false;
         }
    else
         if(vec1[i] < vec2[i])
         {
             return true;
         }
    }
    return false;
}
int main()
{
    Read();
    Kosaraju();
    ofstream g("retele.out");
    g << NrComp << endl;
    sort( Componente.begin(), Componente.end(), comp);



    for ( int i = 0; i < NrComp ; ++i )
    {
        sort(Componente[i].begin(), Componente[i].end());
        g << Componente[i].size() << " ";

        for ( auto &elem : Componente[i] )
            g << elem << " ";
        g << endl;
    }
    return 0;
}
