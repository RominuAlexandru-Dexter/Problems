#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

/** RO: Se da un arbore binar din care ai voie sa stergi O SINGURA data o muchie
    si sa adaugi O SINGURA muchie astfel incat sa ajungi la cel mai lung lant.

    EN: You are given a binary tree from which you are allowed to delete SINGLE times a edge
    and add a SINGLE edge to reach the longest chain
**/

/** Explicatii cum am gandit problema:
    Daca o sa facem DFS-ul pentru a afla diametrul pe mai multi arbori binari, o sa observam ca diametrul
    mereu este dat de nodul cu cel mai jos nivel al ramuri stanga si cel mai jos nivel ar ramurei dreapta.
    ?Diametrul trebuie sa contina radacina? - oricum nu este relevanta pt rezolvare

    Ce vreau eu sa fac este sa-mi alungesc pe cat de mult posibil arborele pentru a putea fi parcurs la capacitate maxima;

        1
       /  \
      2    3
     / \  / \
    4  5 6   7
       |
       8

    Din asta algoritmul meu il va transforma in :

    1 - 3 - 6 - 8 - 5 - 2 - 4( Privit din lateral )
         \
          7

    Algoritmul se desfasoara astfel:
    1) Aflu in ramura din stanga, respectiv ramura din dreapta care este nodul care are cel mai mare nivel.
    3) Tai legatura dintre radacina si ramura care are nodul cu cel mai mare nivel ( irelevant daca o sa fie egal si stanga si dreapta)
    3) Adaug o legatura intre nodurile care au cel mai mare nivel.
    4) Imi transform arborele nou in ceva ce poate fi parcurs bipart. Explic mai jos de ce e nevoie de asta.
    5) Fac un algoritm simplu de Diametru graf.
    5.1) Parcurg 1 DFS pentru a afla cel mai indepartat nod
    5.2) Pornesc 1 DFS din ce am aflat la 5.1 ca sa-mi rezulte lantul maximal.


**/
/// Imi creez un struct ca sa-mi fie mai usor sa retin datele despre nodurile care ma intereseaza
struct infoNode{
    int maxLevel;
    int nodPatriarh;
};
map < int , infoNode > nodeWithMaxLevel;  /// Salveaza nodul cu pricina , nivelul lui maxim si "patriarhul" de care apartine
/**
Folosesc un map pentru ca prin intermediu lui mai tarziu pot sa generalizez pe orice tip de arbore
Map-ul e smecher, o sa pot sa le ordonez in functie de maxLevel dar sa nu pierd nod ul al cui apartin datele
**/
typedef vector < int > vi;
vi temporar (2);
vector < vi > Arbore;

int N;
bool beenThere[100];

void read(){
    ifstream f("date.in");
    f >> N;
    Arbore.assign( N+1, vi() );

    for ( int i = 0 ; i < N - 1 ; ++i )
    {
        int x, y;
        f >> x >> y;
        Arbore[x].push_back(y);
    }

}


void DFS(int nod, int nivelCurent, int &nodNivelMaxim, int &nivelMaxim)
{
    beenThere[nod] = true;

    if ( nivelCurent > nivelMaxim )
    {
        nivelMaxim = nivelCurent;
        nodNivelMaxim = nod;
    }

    for ( unsigned int i = 0 ; i < Arbore[nod].size() ; ++i )
    {
        if( !beenThere[Arbore[nod][i]] )
            DFS( Arbore[nod][i], nivelCurent + 1 , nodNivelMaxim, nivelMaxim );
    }
}
/**
Ce am facut aici a fost sa-mi impart DFS-ul in bucati mai mici ca sa-mi fie mai usor sa obtin datele.
Imi impart arborele in alti 2 arbori, eliminand radacina lor si calculez ce am nevoie pt fiecare din ei,
astfel aflu pe fiecare ramura care este nivelul maxim.
Complexitatea este la fel ca DFS-ul pe arborele mare.
De asemenea am facut asta pentru ca mai tarziu merge transformat pe orice tip de arbore.
**/
void getNodeData(){

    int nodNivelMaxim;
    for ( unsigned int i = 0 ; i < Arbore[1].size() ; ++i )
    {
        int nivelMaxim = 1;
        int nodNivelMaxim = 0;
        DFS ( Arbore[1][i], 1, nodNivelMaxim, nivelMaxim);

        infoNode pushNodeToMap;
        /// Aici aflu prin intermediul DFS-ului spart in bucati care este nivelul maxim pe fiecare ramura
        pushNodeToMap.maxLevel = nivelMaxim;
        pushNodeToMap.nodPatriarh = i+2; /// e + 2 pt ca i-ul incepe de la 0 si vecinii radacinii sunt mereu 2 si 3
        nodeWithMaxLevel[nodNivelMaxim] = pushNodeToMap;
    }
}

void bipartArbore(){
    cout << "Imi marchez noul arbore sa fie bipart pt a ma putea deplasa fara probleme" << endl;
      for (int i = 0; i < Arbore.size(); i++)
        for (int j = 0; j < Arbore[i].size(); j++)
        {
            Arbore[Arbore[i][j]].push_back(i);
        }
}

int maxLevel, pozMax;
void darb( int nod, int nivel ){
    beenThere[nod] = true;

    if ( nivel > maxLevel )
        maxLevel = nivel,
        pozMax = nod;


    for ( unsigned int i = 0 ; i < Arbore[nod].size() ; ++i )
    {
        if( !beenThere[Arbore[nod][i]] )
            darb( Arbore[nod][i], nivel + 1 );
    }

}
void solve(){

    cout << "Unesc el mai de jos nod din ramura stanga cu cel mai de jos nod din ramura dreapta " << endl;
    cout << "pentru a pastra lantul maxim initial: ";
    cout << temporar[0] << " si " << temporar[1] << endl << endl;
    Arbore[temporar[0]].push_back(temporar[1]);

    cout << "Iar acum elimin muchia prin care legam patriarhul nodului de nivel maxim de radacina: " ;
    int toDelete =  nodeWithMaxLevel[temporar[1]].nodPatriarh;
    cout << toDelete << endl << endl;
    Arbore[1].erase(Arbore[1].begin() + (toDelete-2));

    /**
    Am observat ca intervine o problema in functie de directia pe care o dau si ca nu o sa-mi ia lantul maxim datorita directiei,
    asa ca am transformat arborele nou in unul "dus-intors".
         1
       /  \
      2    3
     / \  / \
    4  5 6   7
       |
       8

    Daca vreau sa parcurg lantul dupa ce tai muchia 1-2 si unesc 8-6, o sa am o problema pt ca nu o sa am voie sa merg 8-5,
    doar 5-8 de aceea il fac bipart.
    **/
    bipartArbore();
    /// Aici pentru ca deja nu mai este un arbore normal avem nevoie sa facem un DFS de 2 ori ca sa aflam diametrul noului arbore
    cout << endl;
    fill(beenThere, beenThere + N + 1 , false);
    darb(1,0);
    fill(beenThere, beenThere + N + 1 , false);
    darb(pozMax,0);
    cout << "Lantul maxim care se poate obtine este: " << maxLevel + 1;

}
int main()
{
    read();
    getNodeData();
    int LantInitial = 1;
    int k = 0;

    for ( auto &i : nodeWithMaxLevel )
    {
        cout << "Nodul " << i.first << " se afla pe cel mai jos nivel " << i.second.maxLevel << " si este un fiu al lui " << i.second.nodPatriarh << endl;
        temporar[k++] = i.first; /// am nevoie mai departe de imformatia asta astfel ca o stochez intr-un vector de dimensiuni 2, sau mai mult pt generalizare
        LantInitial += i.second.maxLevel;
    }
    cout << endl;
    cout << "Lantul maxim (diamentrul) initial are lungimea de: " << LantInitial<< endl <<endl;

    solve();
}
