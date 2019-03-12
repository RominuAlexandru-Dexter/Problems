#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

/**
    Cut 'em all! - 982C Codeforces
You're given a tree with n vertices.

Your task is to determine the maximum possible number of edges that can be removed in such a way that
all the remaining connected components will have even size.
*/

/**
Metoda de abordare:
    1) Observ din cateva exemple ca arborele trebuie de fie bidirectional ca sa aiba sens.
    2) Aplic un DFS si dinamica pentru drumurile bidirectionale ( adica calculez in if ce am nevoie)
    3) Alogritmul de Punti imi spune care sunt Nodurile din componenta sa.
    4) Preiau nodurile de mai sus si verific daca scazand nodurile componentei determinate de B din
    nodul 1 DP[1] - DP[B] % 2 == 0 (nodul principal) este par si daca DP[B] este si el par
*/
typedef vector < int > vi;

vector < vi > ListaAdiacenta;
vector < bool > beenThere(100016);
vi parinte(100016), disc(100016);
vi DP(100016);
int N;
void read(){
    ifstream f("date.in");
    cin >> N;
    ListaAdiacenta.assign(N+1, vi() );

    for ( int i = 0 ; i < N-1 ; ++i )
    {
        int x, y;
        cin >> x >> y;
        ListaAdiacenta[x].push_back(y);
        ListaAdiacenta[y].push_back(x);
    }

}

void DFS ( int nod ){
    beenThere[nod] = true;
    int resultSum = 0;
    for ( auto &it: ListaAdiacenta[nod] )
    {
        if (!beenThere[it])
            DFS(it),
            resultSum += DP[it];
    }

    DP[nod] += resultSum;
}
int cnt ;
void IS_BRIDGE( int A, int B ){

    if ( DP[B] % 2 == 0 )
    {
        if ( (DP[1] - DP[B]) % 2 == 0 )
            cnt++;
    }
}
int moment;

void Punte ( int curent , int p = -1 ){
    beenThere[curent] = true;
    parinte[curent] = disc[curent] = ++moment;

    for ( auto &vecin: ListaAdiacenta[curent] )
    {

        if ( vecin == p )
            continue;

        if ( beenThere[vecin] )
            parinte[curent] = min ( parinte[curent] , disc[vecin] );
        else
        {
            Punte( vecin , curent );
            parinte[curent] = min ( parinte[curent] , parinte[vecin] );
            if ( parinte[vecin] >= disc[curent] )
                IS_BRIDGE(curent , vecin); /// Transmit informatiile la functia de mai sus;
        }
    }
}
int main()
{
    read();

    DP.assign(N+1, 1);
    DFS(1);
   /* cout << "Nod\tCopii" << endl;
    for ( int i = 1; i <= N ; ++i )
        cout << i << "\t" << DP[i] << endl;*/

    beenThere.assign( N+1 , false );
    Punte(1,-1);

    /** Aici am trisat si m-am uitat la alta sursa sa vad de ce uneori e corect 0 si alteori -1
        Textul problemei e foarte ambiguu si PROST scris.
    */
    if (N%2 == 0)
        cout << cnt;
    else
        cout << -1;
    return 0;
}
