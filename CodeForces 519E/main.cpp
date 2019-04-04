#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

using namespace std;
/**
  Descriere problema:
    Se da un arbore si sunt numar de querries. Pentru fiecare querry avem 2 noduri: x, y.
    Fiecare nod reprezinta o sala unde invata un elev. Pentru fiecare querry vreau sa aflu:
    Numarul de sali la o distanta egala fata de ambii elevi.
    Exemplu simplist:
      1
     / \
    2   3
    Pentru querry : 2,3 -> raspuns = 1 , o singura sala la distanta egala (nodul 1)
    Pentru querry : 1,3 -> rapuns = 0, nu exista sali la o distanta egala fata de ambii elevi.

  x, y -> nodurile date in querry
  Metoda de abordare:
    O sa folosesc: sizeTree[] - Programarea dinamica pentru a afla numarul de noduri intr-un subarbore;
                   adancime[]
                   beenThere[]

    Am identificat 4 cazuri posibile cu 4 rezolvari pentru fiecare:
    1) x = y , se afla in aceeasi sala, deci toate salile sunt la distanta egala fata de ambii elevi
      Raspunsul este N;
    2) Distanta de la x la y este impara -> raspuns 0
      1
      |
      2
     / \
    3   4
        |
        5 Pentru (2,4), (2,3) , (2,1), (4,5), (1,5) -> raspuns 0, se demonstreaza logic matematic.

    3) Calculez un nod LCA (il notam nLCA). Daca distanta de la (x,nLCA) == (nLca,y)
    Din numarul total de noduri N, o sa scad tatal lui x, aflat imediat sub nLCA, respectiv lui y;
    Notam (tatal lui x, aflat imediat sub nLca) - ancestorX
    Notam (tatal lui y, aflat imediat sub nLca) - ancestorY
    -> raspuns : N - sizeTree[ancestorX] - sizeTree[ancestorY]

    1
    |
    2
   / \
  3   4  Pentru (5,6) - > nLCA = 2 ;
  |   |   ancestorX = 3 , ancestorY = 4
  5   6   Raspuns ->  N - sizeTree[3] - sizeTree[4] => 6 - 2 - 2 = 2 ( raspuns final, adica nodurile ramase 1 si 2 )

    4) In restul tuturor cazurilor ne aflam in situatia cand salile care se afla la o distanta egala
    fata de X si Y, se afla intr-un subarbore delimitat de ele, cu noul punct de interesat aflat la
    jumatatea distantelor dintre cele 2 ;( adancime[x] + adancime[y] ) / 2 si ce se intampla acolo.
    Notam nodul acesta de interes ca fiind : MidNode
    Trebuie sa mai aflam si nodul care vine din cel mai de jos nod ( adancime[x] > adancime[y] ; sau invers ),
    Si sa flam tatal lui X, care se afla imediat sub MidNode, il vom nota MidAncestorX;

    Raspunsul o sa fie sizeTree[MidNode] - sizeTree[MidAncestorX];

    1
    |
    2
   / \
  3   4
 / \   \
5   6   7
    |
    8    (4,8) - > Distanta de la 4 la nLCA (2) este 1 si pentru 8 la nLCA este 3; Distanta de la x la y este 4
                -> cautam jumatatea lantului delimitat de x (4) si y (8) -> dist pana la MidNode e 2
                ,pronind din x sau y, cautand al vecinul comun la distanta 2 din ambele rezulta nodul 3'
                MidNode = 3;
                MidAncestorX = 6;
                Raspuns : sizeTree[3] - sizeTree[6] = 4 - 2 = 2 ( nodurile 3 si 5 );

  */

ifstream f("date.in");
typedef vector < int > vi;
vector < vi > ListaAdiacenta;
vector < vi > UP;
bitset < 100064 > beenThere;
vi adancime, sizeTree, tin, tout;

int N, L, timer;


void read(){
  cin >> N;
  ListaAdiacenta.assign(N+1, vi());
  for ( int i = 0 ; i < N - 1; ++i ){
    int x, y;
    cin >> x >> y;
    ListaAdiacenta[x].push_back(y);
    ListaAdiacenta[y].push_back(x);
  }

}
bool is_ancestor( int a, int b){
  return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void DFS_UP ( int nod , int p ){
  tin[ nod ] = ++timer;
  UP[ nod ][0] = p;

  for ( int i = 1 ; i <= L ; ++i )
    UP[ nod ][i] = UP[ UP[nod][i-1] ][ i - 1 ];

  for ( auto &it: ListaAdiacenta[ nod ])
    if ( it != p )
      DFS_UP(it, nod);

  tout[ nod ] = ++timer;
}

int LCA ( int a, int b ){
  if( is_ancestor(a, b) )
    return a;
  if( is_ancestor(b, a) )
    return b;

  for ( int i = L ; i >= 0 ; --i )
    if(!is_ancestor(UP[a][i], b) )
      a = UP[a][i];

  return UP[a][0];
}

void DFS_INFO ( int nod, int nivel ){

  beenThere[ nod ] = true;
  adancime [ nod ] = nivel;
  int TreeSum = 0;
  for ( auto &it : ListaAdiacenta[ nod ]){
    if (!beenThere[it]){
      DFS_INFO(it, nivel + 1);
      TreeSum += sizeTree[it];
    }
  }

  sizeTree[ nod ] += TreeSum;
}

void preProcess(int root){
  tin.resize( N + 1 );
  tout.resize( N + 1 );
  timer = 0;
  L = ceil(log2(N));
  UP.assign( N + 1, vi(L + 1) );
  adancime.resize( N + 1 );
  sizeTree.assign( N + 1, 1 );
  DFS_UP( root, root ); /// DFS ce imi construiesti matricea de LCA;
  DFS_INFO( root, 0 );
}

void writeINFO(){
  for ( int i = 1; i <= N ; ++i ){
    cout << "Adancimea nodului " << i << " este " << adancime[i] << endl;
    cout << "Numarul de noduri in componenta lui " << i << " este " << sizeTree[i] << endl;
    cout << "Vecinii nodului " << i << " sunt: ";
    for ( auto &jt : ListaAdiacenta[i])
      cout << jt << " ";
    cout << endl;
  }
}

/*PreProcesare si construirea chestiilor de care am nevoie sa lucrez cu ele*/
/*==============================================================================*/
/*Algoritmul pentru problema*/
void dist_AB( int a, int tinta, int distance, int &deIntors ){
  beenThere[a] = true;
  if ( a != tinta)
    for ( auto &it: ListaAdiacenta[a] ){
        if(!beenThere[it]){
           dist_AB(it, tinta, distance + 1, deIntors);
        }
      }
  else{
    deIntors = distance;
  }


}

int ancestor ( int nod, int tinta ){
  beenThere[nod] = true;

  for ( auto &it: ListaAdiacenta[ nod ] ) {
    if ( it != tinta ){
      if (!beenThere[it])
        return ancestor(it, tinta);
    }
    else
      return nod;
  }
}

int nodeAtHalfLenght( int nod, int range, int lungimeCurenta ){
  beenThere[nod] = true;
  if ( lungimeCurenta < range ){
    for (auto &it: ListaAdiacenta[nod])
      if(!beenThere[it])
       return nodeAtHalfLenght(it, range, lungimeCurenta + 1);
  }
  else
    return nod;

}
void querry( int x, int y ){
  int nLCA = LCA(x, y);
  int distXY, distXLCA, distYLCA;

  beenThere.reset();
  dist_AB(x, y, 0, distXY);
  beenThere.reset();
  dist_AB(x, nLCA, 0, distXLCA);
  beenThere.reset();
  dist_AB(y, nLCA, 0, distYLCA);

  if( x == y ){
    cout << N;
    return;
  }
  if ( distXY % 2 == 1 ){
    cout << 0;
    return;
  }

  if ( distXLCA == distYLCA ){
    beenThere.reset();
    cout << N - sizeTree[ancestor(x, nLCA)] - sizeTree[ancestor(y, nLCA)];
    return;
  }

  int lungimeLant = distXY;

  if ( adancime[x] > adancime[y] ){
    beenThere.reset();
    int midNode = nodeAtHalfLenght(x, lungimeLant/2, 0);
    beenThere.reset();
    int midAncestor = ancestor(x, midNode);
    cout << sizeTree[midNode] - sizeTree[midAncestor];
    return;
  }
  else{
    beenThere.reset();
    int midNode = nodeAtHalfLenght(y, lungimeLant/2, 0);
    beenThere.reset();
    int midAncestor = ancestor(y, midNode);
    cout <<sizeTree[midNode] - sizeTree[midAncestor];
    return;
  }
}
int main(){
  cin.tie(NULL);
  cout.tie(NULL);
  ios::sync_with_stdio(false);
  read();
  preProcess( 1 );
  //writeINFO();

  int nrQuerries;
  cin >> nrQuerries;
  for ( int i = 0; i < nrQuerries ; i++ ){
    int x, y;
    cin >> x >> y;
    querry(x, y);
    cout << endl;
    beenThere.reset();
  }
}
