#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

typedef vector < int > v;
vector < v > Edges;
stack < int > Stack;
bool beenThere[100];
int N, M;
void Read()
{
    ifstream f("date.in");
    f >> N >> M;

    Edges.assign(N+1 , v() );
    for ( int i = 0 ; i < M ; ++i)
    {
        int x , y;
        f >> x >> y;
        Edges[x].push_back(y);
    }
}

void DFS(int node)
{


    beenThere[node] = true;

    for ( auto vecin : Edges[node] )
        if (!beenThere[vecin])
            DFS(vecin);

    Stack.push(node);
}
int main()
{
    Read();
    for (int i = 1 ; i <= N ; ++i)
        if (!beenThere[i])
             DFS(i);

    while (!Stack.empty())
    {
        cout << Stack.top() << " ";
        Stack.pop();
    }
    return 0;
}
