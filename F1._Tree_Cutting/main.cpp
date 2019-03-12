#include <iostream>
#include <fstream>
#include <vector>



using namespace std;

/**

    Tree Cutting (Easy Version) - 1181 F1 Codeforces
You are given an undirected tree of n vertices.

Some vertices are colored blue, some are colored red and some are uncolored.
It is guaranteed that the tree contains at least one red vertex and at least one blue vertex.

You choose an edge and remove it from the tree. Tree falls apart into two connected components.
Let's call an edge nice if neither of the resulting components contain vertices of both red and blue colors.

How many nice edges are there in the given tree?
 */


/**
    Metoda de abordare:
    1) Calculez dinamic pentru fiecare nod numarul de noduri care ii intra in componenta si pastrez in 2 categorii rosii si albastre
        si salvez rezultatele intr-un vector dp[] de tip infoNod
    2) Gasesc toate muchiile care pot fi 'punti'
    3) Verific puntiile cu ajutorul vectorului dp[] calculat anterior si cu putina logica matematica explicata mai jos daca sunt
        "nice"

*/
 /// Un struct care trebuie sa retina numarul de noduri anterioare in functie de culoare
struct infoNod{
    int nrRosi;
    int nrAlbastre;
};
typedef vector < int > vi;
vector < vi > ListaAdiacenta;
int N, cnt;
vi cul(300000);
vi parinte,disc;
vector < infoNod > dp(300000);
vector < bool > beenThere(300000);

void read()
{
    ifstream f("date.in");
    cin >> N;
    cin.tie(0);
    ListaAdiacenta.assign(N+1, vi());

    for ( int i = 1 ; i <= N ; ++i )
    {
        /// 1 == rosu , 2 == albastru
        int x;
        cin >> x;
        cul[i] = x;
        if ( x == 1 )
            dp[i].nrRosi = 1;
        else if ( x == 2)
                dp[i].nrAlbastre = 1;
    }

    for ( int i = 1 ; i < N ; ++i )
    {
        int x, y;
        cin >> x >> y;
        ListaAdiacenta[x].push_back(y);
        ListaAdiacenta[y].push_back(x);
    }

   /* cout << "Cate culori se afla intr-un nod:" << endl;
    cout << "Nod\tRosii\tAlbastre" << endl;
    for ( int i = 1 ; i <= N ; ++i )
    {
        cout << i << "\t"<<  dp[i].nrRosi << "\t" << dp[i].nrAlbastre << endl;
    }   */
}
/// DFS-ul pentru calculul vectorului DP[];
void DFS( int nod ){
    beenThere[nod] = true;
    int rosii = 0;
    int albastre = 0;
    for ( int i = 0 ; i < ListaAdiacenta[nod].size() ; ++i )
    {
        if (!beenThere[ ListaAdiacenta[nod][i] ])
             {

              DFS( ListaAdiacenta[nod][i] );

                rosii += dp[ ListaAdiacenta[nod][i] ].nrRosi;
                albastre += dp[ ListaAdiacenta[nod][i] ].nrAlbastre;
             }
        //cout << "Bag in " << nod << " " << rosii << " " << albastre << " de la " << ListaAdiacenta[nod][i] << endl;

    }
    dp[nod].nrRosi += rosii;
    dp[nod].nrAlbastre += albastre;
}

int moment;

void IS_BRIDGE ( int A, int B ){
    /// nu vreau sa-mi pierd vectorul dp asa ca il clonez, doar ce am nevoie din el
    int mainCloneAlbastra = dp[1].nrAlbastre;
    int mainCloneRosie = dp[1].nrRosi;
    int bCloneAlbastra = dp[B].nrAlbastre;
    int bCloneRosie = dp[B].nrRosi;
    /** extrag din nodul meu principal, '1' care stocheaza totalul nodurilor colorate
        nodul clona[B], adica cel care face legatura catre componenta a doua, toate nodurile in functie de culori;
    */
    mainCloneAlbastra -= bCloneAlbastra;
    mainCloneRosie -= bCloneRosie;
    /**
        O data ce am extras nodurile din componenta a doua fac verificarea daca ce a ramas in clona[1],
        este sau nu de o singura culoare si apoi verific si daca clona[B],
        respecta si el ca componenta lui sa fie de o singura culoare

    */
    if (((mainCloneRosie == 0 && mainCloneAlbastra != 0) || (mainCloneRosie != 0 && mainCloneAlbastra == 0))
                                                            &&
        ((bCloneRosie == 0 && bCloneAlbastra != 0) || (bCloneRosie != 0 && bCloneAlbastra == 0)))
            //cout << A << " " << B << endl,
            cnt++;


}
/// Algoritmul pentru noduri critic e foarte util si pentru punti :)

void muchiiCritice ( int curent , int p = -1 ){
    beenThere[curent] = true;
    parinte[curent] = disc[curent] = ++moment;

    for ( int i = 0 ; i < ListaAdiacenta[curent].size() ; ++i )
    {
        int vecin = ListaAdiacenta[curent][i];
        if ( vecin == p )
            continue;

        if ( beenThere[vecin] )
            parinte[curent] = min ( parinte[curent] , disc[vecin] );
        else
        {
            muchiiCritice( vecin , curent );
            parinte[curent] = min ( parinte[curent] , parinte[vecin] );
            if ( parinte[vecin] >= disc[curent] )
                IS_BRIDGE(curent , vecin); /// Transmit informatiile la functia de mai sus;
        }
    }
}
int main()
{
    read();
    DFS(1);
   /* cout << "Cate culori se afla intr-un nod:" << endl;
    cout << "Nod\tRosii\tAlbastre" << endl;
    for ( int i = 1 ; i <= N ; ++i )
    {
        cout << i << "\t"<<  dp[i].nrRosi << "\t" << dp[i].nrAlbastre << endl;
    }*/

    beenThere.assign(N+1, false);
    parinte.assign(N+1, -1);
    disc.assign(N+1, -1);
    muchiiCritice(1);

    cout << cnt;
    return 0;
}
