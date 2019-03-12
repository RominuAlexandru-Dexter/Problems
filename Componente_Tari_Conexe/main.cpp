#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#define DIM 100
using namespace std;

typedef vector < int > vi;


vector < vi > Graph_Normal;
vector < vi > Graph_Transpose;

stack < int > Stack;

bool beenThere[DIM];
vector < vi > componente;
int N, M, nrComp;

void Read()
{
    ifstream f("date.in");

    f >> N >> M;
    Graph_Normal.assign( N+1, vi() );
    Graph_Transpose.assign( N+1, vi() );
    componente.assign( N+1, vi() );

    for ( int i = 0 ; i < M ; ++i )
    {
        int x , y;
        f >> x >> y;
        Graph_Normal[x].push_back(y);
        Graph_Transpose[y].push_back(x);
    }

   /* for ( int i = 1 ; i <= N ; ++i)
        {
            cout << i << " -> ";
        for ( int j = 0 ; j < Graph_Normal[i].size() ; ++j)
            cout << Graph_Normal[i][j] << " ";
            cout << endl;
        }
    cout << endl;

    for ( int i = 1 ; i <= N ; ++i)
        {
            cout << i << " -> ";
        for ( int j = 0 ; j < Graph_Transpose[i].size() ; ++j)
            cout << Graph_Transpose[i][j] << " ";
            cout << endl;
        } */

}

void DFS_Normal ( int node )
{
    beenThere[node] = true;

    for ( auto &i : Graph_Normal[node] )
        if(!beenThere[i])
            DFS_Normal(i);

    Stack.push(node);
}

void DFS_Transpose (int node )
{
    beenThere[node] = true;
    componente[nrComp].push_back(node);

    for ( auto &i : Graph_Transpose[node] )
        if(!beenThere[i])
            DFS_Transpose(i);

}

void Kosaraju ()
{
    for ( int i = 1 ; i <= N ; ++i )
        if(!beenThere[i])
            DFS_Normal(i);

    fill(beenThere,beenThere+N+1,false);

    while (!Stack.empty())
    {
        int nod = Stack.top();
        Stack.pop();

        if(!beenThere[nod])
        {
            DFS_Transpose(nod);
            nrComp++;
        }
    }
}
int main()
{
    Read();
    Kosaraju();

    cout << "Numarul Componentelor Tari Conexe este: " << nrComp << endl << "Ele sunt: " << endl;
    for ( int i = 0 ; i < nrComp ; ++i)
    {
        cout << "Componenta formata din: ";
        for ( auto &comp : componente[i])
            cout << comp << " ";
        cout << endl;
    }
    return 0;
}
