#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef vector < int > vi;

vector < vi > Arbore;

int N;
int DP[100];
bool beenThere[100];

/// RO: Se da un arbore. Sa se afiseze numarul de noduri aflate in compozitia acestuia.
/*
		1
	   / \
	  2   3
		 / \
		4   5
 4 are 1 nod in compozitie ( Incluzand-ul si pe el insusi )
 5 are 1 nod in compozitie
 3 are 3 noduri in compozitie ( 4, 5 si el insusi )
 2 are 1 nod in compozitie
 1 are 5 noduri in compozitie ( 4, 5, 3, 2 si el insusi )

*/
void read(){
    ifstream f("date.in");

    f >> N;
    Arbore.assign(N+1, vi());
    fill(DP, DP+N+1 ,1);
    for ( int i = 0 ; i < N-1 ; ++i )
    {
        int x, y;
        f >> x >> y;
        Arbore[x].push_back(y);
    }
    f.close();
}

void DFS ( int nod ){
    beenThere[nod] = true;
    int resultSum = 0; /// Suma finala a "frunzelor" pe care o aduni la radacina L - > R
    for ( int i = 0 ; i < Arbore[nod].size() ; ++i )
    {
        if( !beenThere[Arbore[nod][i]] )
            DFS( Arbore[nod][i] );
        resultSum += DP[Arbore[nod][i]];
    }

    DP[nod] += resultSum;

}
int main()
{
    read();
    DFS(1);

    for ( int i = 1; i <= N ; ++i )
        cout << "Nodul " << i << " are in componenta lui " << DP[i] << " nod(uri)." << endl;

    return 0;
}
