#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

/**
     Book of Evil - 337D Codeforces

     Metoda de abordare:
     1) Observ ca cea mai buna abordare ar fi sa impart problema in probleme mai mici, asa ca o sa-mi
     pornesc un DFS din fiecare oras afectat dat ca si query si o sa merg in adancime pana la range-ul
     care afecteaza cartea.
     2) Intr-un vector Vec cresc mereu cu +1, cand trec printr-un oras.
     3) La finalul zilei obtin un vector Vec cu valori diferite si prin logica realizez ca toate pozitiile
     care au numarul de cate ori s-a dus DFS-ul prin ele, este egal cu nr. orase Infectate, pot sa le
     contorizez ca posibile centre ale infectiei.
     3.1) Mai explicit este ca un oras ca sa fie punct de infectie trebuie sa fie atins de toate DFS-urile

            6
           /
     1 - 5
          \
           4
          /
     2 - 3
     Vec = {0 , 0 , 0 , 0 ,0 , 0 }
     Orasele afectate sunt 1 si 2 si range-ul este de 3.
     DFS(1) se duce astfel -> 5,4,3,6 - > Vec = { 1, 0 , 1 , 1 , 1 , 1 }
     DFS(2) se duce astfel -> 3,4,5 - > Vec = { 1, 1 , 2 , 2 , 2 , 1 }

     -> Orasele de pe pozitiile ale carui valori == nrOraseInfectate -> sunt posibile locatii ale cartii

     Isi ia un TLE pe test-ul 6
*/

typedef vector < int > vi;
vector < vi > ListaAdiacenta;
bitset <100016> beenThere;
vi Curata;
vi oraseInfectate(100016), Vec(100016);

int N, nrInfectate, range, cnt;
void read(){
    ifstream f("date.in");
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> N >> nrInfectate >> range;

    ListaAdiacenta.assign( N+1 , vi() );
    for ( int i = 1 ; i <= nrInfectate ; ++i )
        cin >> oraseInfectate[i];

    for ( int i = 0 ; i < N - 1 ; ++i )
    {
        int x, y;
        cin >> x >> y;
        ListaAdiacenta[x].push_back(y);
        ListaAdiacenta[y].push_back(x);
    }
}

void DFS( int nod, int nivel ){
    beenThere[nod] = true;
    Curata.push_back(nod);

    if ( nivel <= range )
        for ( auto &it: ListaAdiacenta[nod] )
        {
            if (!beenThere[it]  )
            {
                DFS( it, nivel+1 );
                Vec[it]++;
            }
    }
}
int main()
{
    read();

    for ( int i = 0 ; i <= nrInfectate ; ++i )
    {
        /**
            Am luat in calcul ca chiar un orase care mi se da infectat de la inceput, poate fi un focar
            asa ca il incrementez si pe el.
        */

        Vec[oraseInfectate[i]]++;
        DFS(oraseInfectate[i],1);
        /**
            Daca as folosi assign mi-as omora si mai rau programul asa ca stochez intr-un vector
            valorile la care a ajuns DFS-ul si le curat pentru urmatorul.
        */
        for ( auto &k : Curata)
            beenThere[k] = false;

        //beenThere.assign(N+1, false);

        /**
        cout << oraseInfectate[i] << endl << endl;
        for ( int j = 1; j <= N; ++j )
            cout << j << "\t" << Vec[j] << endl;

        cin.get(); */
    }

    for ( int j = 1; j <= N; ++j )
        if ( Vec[j] == nrInfectate )
            ++cnt;

    cout.tie(NULL);

    cout << cnt;
    return 0;
}
