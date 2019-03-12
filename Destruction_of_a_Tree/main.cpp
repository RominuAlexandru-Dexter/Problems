#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

/**
    Destruction of a Tree - 963B Codeforces


    You are given a tree (a graph with n vertices and n-1 edges in which
    it's possible to reach any vertex from any other vertex using only its edges).

    A vertex can be destroyed if this vertex has even degree.
    If you destroy a vertex, all edges connected to it are also deleted.

    Destroy all vertices in the given tree or determine that it is impossible.

    Metoda de abordare:

    1) DFS-ul nu porneste mereu din 1.
    2) Pornesc un DFS care imi cauta un element care are degree par .
    3) Daca degree e par, atunci degree-ul lui devine 0 , si degree-ul vecinilor lui scad.
    4) Continui un DFS in toti copii lui sperand sa gasesc ceva bun
    5) Resetez beenThere ca sa pot urca pe nivelele de mai sus
    6) Repet procesul pana cand nu mai am ce sa fac.




        1 - 4
       / \
      2   3
     / \
    5   6
         \
          7

    1)Pe exemplul de mai sus se duce prima data pe 6 , ii scade degree-ul lui 3 si 7 si degree[6] = 0;
    2)Incearca sa isi faca algoritmul pe 7 dar e oprit de if.
    3)A iesit din recursivitate si beenThere e din nou 0 peste tot
    4)Se duce pe 2 vede ca acum are un degree par si face acelasi analog 1).


    E putin brute-force. Din pacate imi pica pe testul 7 si nu pot vedea ce e gresit.
*/

typedef vector < int > vi;

vector < vi > ListaAdiacenta;
vector < int > beenThere(200016);
vi degree(200016);
vi afiseaza;
bool isEven = true;
bool isGood = true;
bool restNoduri[200016];
int N;
void read(){
    ifstream f("date.in");
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> N;
    ListaAdiacenta.assign( N+1, vi() );
    for ( int i = 1 ; i <= N ; ++i )
    {
        int x;
        cin >> x;
        if ( x != 0)
            degree[i]++;

        degree[x]++;
        ListaAdiacenta[x].push_back(i);
        ListaAdiacenta[i].push_back(x);
    }
}

void DFS(int nod){
    ///cout << nod << " " << degree[nod] << endl ;
    beenThere[nod] = true;
    /// Am if-ul asta pentru ca vreau sa mearga doar pe nodurile in cauza un DFS special.
    if ( degree[nod] % 2 == 0 && degree[nod] != 0 )
    {
        ///cout << nod << " Pe asta " << degree[nod] <<  endl;

        beenThere[nod] = true;
        afiseaza.push_back(nod);
        degree[nod] = 0;
        /// Ii scad copiii conectati direct la nodul in cauza
        for ( auto &it: ListaAdiacenta[nod] )
        {
            if ( degree[it] > 0 )
                degree[it]--;
           /// cout << it << " " << degree[it] << endl;
        }
        /// Incerc sa ma duc in continuare pe copii lui in caz ca gasesc ceva bun
        for ( auto &it: ListaAdiacenta[nod] )
        {

            if(!beenThere[it])
                DFS(it);
        }
        /// Dupa ce DFS-ul de sus se intoarce recursiv la nodul de la care a pornit resetez beenThere
        beenThere.assign(N+1, false);
    }

    else
        /// Continui sa caut , avand posibilitatea de a ma intoarce datorita a ce am facut mai sus.
    {
        for ( auto &it: ListaAdiacenta[nod] )
        {
            if(!beenThere[it])
                DFS(it);
        }
    }

}



int main()
{

    read();
      /**for ( int i = 1 ; i <= N ; ++i )
        cout << i << " " << degree[i] << endl;
        cin.get();

    for ( int i = 1; i <= N ; ++i )
        for ( auto &it : ListaAdiacenta[i] )
            cout << i << " " << it << endl;
    */
    cout.tie(NULL);

    DFS(1);

    ///cin.get();
    for ( int i = 1 ; i <= N ; ++i )
        if (degree[i] != 0 )
            isGood = false;
    if( isGood )
    {
        cout << "YES" << endl;
        for (int i = 0 ; i < afiseaza.size() ; ++i )
            cout << afiseaza[i] << endl,
            restNoduri[afiseaza[i]] = true;

        for ( int i = 1 ;i <= N ; ++i )
            if (restNoduri[i] == false )
                cout << i << endl;


    }
    else
        cout << "NO";


    return 0;
}
