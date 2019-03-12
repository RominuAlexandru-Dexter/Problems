#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
/**
    B. Chamber of Secrets - Codeforces 173B

    Metoda de abordare:
    1) Transform matricea in graf.
    2) Execut BFS pt Shorthest Path.
    3) Nu inteleg de ce imi iau runtime error pe test 46. :) /// Am rezolvat-o, am crescut de la 1000 la 2019 vectorii
*/
typedef vector < long long > vi;
vector < vi > ListaAdiacenta;

int N, M;
vi disc(2019), parinte(2019);
vector < bool > beenThere(2019);
queue < int > Q;


void read(){
    ifstream f("date.in");
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> N >> M;
    ListaAdiacenta.assign( N + 10016, vi() );

   for ( int i = 0; i < N ; ++i )
        for ( int j = 0; j < M ; ++j )
        {
            char x;
            cin >> x;
            if ( x == '#' )
            {
                /// Folosesc + N pentru ca vreau sa conectez, ideea e ca raza de lumina e pe intreaga distanta.
                ListaAdiacenta[i].push_back(j+N);
                ListaAdiacenta[j+N].push_back(i);
            }
        }
}
/** Aparent BFS-ul e mult mai util decat credeam.
    Mi-am dat seama ca trebuie sa fac shorthest path pe unweight graph... initial am incercat cu DFS si cu nivele dar nu am reusit
    Apoi am cautat pe net ( din pacate ) cum se face un shorthest path pe unweight graph si am aflat ca cu BFS.
*/
void BFS ( int nod ){
    Q.push(nod);
    beenThere[nod] = true;
    parinte[nod] = -1;

    while( !Q.empty() )
    {
        int curent = Q.front();
        Q.pop();

        for ( auto &vecin: ListaAdiacenta[curent] )
        {
            if(!beenThere[vecin])
            {
                beenThere[vecin] = true;
                Q.push(vecin);
                disc[vecin] = disc[curent] + 1;
                parinte[vecin] = curent;
            }
        }
    }
}
int main()
{
    read();
    BFS(0);
    cout.tie(NULL);
    if (disc[N-1])
        cout << disc[N-1];
    else
        cout << -1;
    return 0;
}
