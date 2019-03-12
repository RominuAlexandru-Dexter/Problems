#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
/**
Se da un graf conex neorientat G cu N noduri si M muchii, fiecare muchie avand asociat un cost.
Se cere sa se determine un subgraf care cuprinde toate nodurile si o parte din muchii,
astfel incat subgraful determinat sa aiba structura de arbore si suma costurilor muchiilor care il formeaza sa fie minim posibila.
Subgraful cu proprietatile de mai sus se va numi arbore partial de cost minim pentru graful dat.
**/

struct nod{
    int weight;
    int x;
    int y;
};

bool compare( nod x, nod y ){
    return x.weight < y.weight;
}

vector < nod > Graf;
vector < pair < int , int > > ArboreNou;

int N, M, parinte[100];

void read(){
    ifstream f("date.in");

    f >> N >> M;

    for ( int i = 1 ; i <= N ; ++i )
        parinte[ i ] = i;

    for ( int i = 0 ; i < M ; ++i )
    {
        int x, y, w;
        f >> x >> y >> w;
        w += 1000; /// ByPass For Negative Values
        nod Date;

        Date.weight = w;
        Date.x = x;
        Date.y = y;

        Graf.push_back(Date);
    }
    f.close();
    sort ( Graf.begin(), Graf.end(), compare );/// Sortate Crescatoare in Functie de Weight

}

int Find( int x ){
    if( parinte[ x ] == x )
        return x;
    else
        Find( parinte[ x ] );
}

void Unite( int x, int y ){
    int fx = Find(x);
    int fy = Find(y);
    parinte[ fy ] = fx;
}

void solve(){
    int muchiiTotal = 0, greutateTotala = 0, nodCurent = 0; /// muchiiTotal -> nr.muchii ale noului arbore, greutateTotala -> greutatea noului arbore

    while ( nodCurent < M )
    {
        int greutateCurenta = Graf[nodCurent].weight;
        int xCurent = Graf[nodCurent].x;
        int yCurent = Graf[nodCurent].y;

        if ( Find( xCurent ) != Find ( yCurent ) )
        {
            Unite( xCurent , yCurent );
            greutateTotala += greutateCurenta;
            muchiiTotal ++;

            ArboreNou.push_back( make_pair(xCurent , yCurent) );
        }

        nodCurent++;
    }

    cout << "Greutatea Noului Arbore este: " << greutateTotala -  (muchiiTotal*1000)<< endl; /// Scot ce am adaugam pt ByPass;
    cout << "Numarul de muchii este: " << muchiiTotal << endl ;

    for ( auto &comp : ArboreNou )
        cout << comp.first << " " << comp.second << endl;

}
int main()
{
    read();
    solve();
    return 0;
}
