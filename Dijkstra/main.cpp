#include <iostream>
#include <fstream>
#include <vector>
#include <queue>


#define INF 999999999

using namespace std;

ifstream f("date.in");

typedef pair < int, int > ii;
typedef vector < ii > vii;
vector < vii > ListaAdiacenta;

typedef vector < int > vi;
vi drum;
vi dist;
int N, M;
int parinte[2018];
bool beenThere[2018];

void Read()
{
    f >> N >> M;

    int x, y, w;

    ListaAdiacenta.assign(N+1 , vii());

    for ( int i = 1 ; i <= M ; ++i)
    {
        f >> x >> y >> w;
        ListaAdiacenta[x].push_back( ii(y,w) );
        ListaAdiacenta[y].push_back( ii(x,w) );
    }

}

void Dijkstra(int node)
{
    beenThere[node] = true;
    parinte[node] = -1;

    dist.assign(N+1, INF);
    dist[node] = 0;
    priority_queue < ii , vector<ii> , greater <ii> > pq;

    pq.push( ii(0,node));

    while(!pq.empty())
    {
        ii curent = pq.top();
        pq.pop();

        int nod = curent.second;
        int distanta = curent.first;

        if ( distanta > dist[nod] )
            continue;

        for( unsigned int i = 0 ; i < ListaAdiacenta[nod].size(); ++i)
        {
            ii vecin = ListaAdiacenta[nod][i];

            if (dist[nod] + vecin.second < dist[vecin.first])
            {
                if(!beenThere[vecin.first])
                    parinte[vecin.first] = nod;

                cout << "Cel mai apropiat tata al lui " << vecin.first << " este " << nod << endl;
                cin.get();

                dist[ vecin.first ] = dist[nod] + vecin.second;
                pq.push( ii( dist[vecin.first], vecin.first ) );
            }

        }
    }
}

void Write_Way( int nod)
{
    while( nod != -1 )
        {
            drum.push_back( nod );
            nod = parinte[ nod ];
        }
    for( int i = drum.size() - 1; i > 0; --i )
        cout << drum[ i ] << ' ';
    cout << drum[ 0 ];
}
int main()
{
    Read();
    //cout << ListaAdiacenta[5][1].second;
    Dijkstra(1);

    cout << endl << "Drumul catre n";
    cin.get();

    cout << endl << endl;
    Write_Way( N );
    return 0;
}
