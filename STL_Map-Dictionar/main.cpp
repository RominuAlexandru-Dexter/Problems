#include <iostream>
#include <iterator>
#include <map>
#include <string>

using namespace std;

map < int , int > quiz;
void basicFunctionAndSyntax(){
    /// Inserare elemente in Map
    quiz.insert(pair < int , int > (10,10) );
    quiz.insert(pair < int , int > (1,10) );
    quiz.insert(pair < int , int > (2,20) );
    quiz.insert(pair < int , int > (2,100) );
    quiz.insert(pair < int , int > (2,200) );
    quiz.insert(pair < int , int > (2,300) );
    quiz.insert(pair < int , int > (2,400) );
    quiz.insert(pair < int , int > (3,30) );
    quiz.insert(pair < int , int > (4,40) );

    /// Map-ul accepta o singura aparitie de cheie, luata in ordinea inserarii.
    /// Map-ul sorteaza AUTOMAT crescator dupa cheie.
    cout << "Structura Dictionarului este data de ordinea: " << endl;
    cout << "KEY\tELEMENT" << endl << endl;

    map< int , int > ::iterator itr;
    /// Afisare elemente din Map
    cout << "Primul Dictionar este: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( itr = quiz.begin() ; itr != quiz.end() ; ++itr )
        cout << itr->first << "\t" << itr->second << endl;


    cout << endl;

    /// Copiere elemente dintr-o Map in alta Map
    map < int, int > quiz2 ( quiz.begin(),quiz.end() );
    cout << "Am copiat primul Dictonar in al 2-lea si acesta este: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( itr = quiz2.begin() ; itr != quiz2.end() ; ++itr )
        cout << itr->first << "\t" << itr->second << endl;

    cout << endl;
    /// Stergere elementulu si cheii in functie de cheie


    quiz2.erase(2);
    cout << "Am sters elementele care aveau cheia 2 din Dictionarul 2: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( itr = quiz2.begin() ; itr != quiz2.end() ; ++itr )
        cout << itr->first << "\t" << itr->second << endl;

    cout << endl;

    /// Folosesc find() ca sa afisez elementele pana la o valoarea
    cout << "Elementele pana la key 3 din Dictionar 1 sunt: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( itr = quiz.begin() ; itr != quiz.find(3); ++itr )
        cout << itr->first << "\t" << itr->second << endl;
    cout << endl;

    /// Stergerea tutoror elementelor dinaintea key
    quiz.erase( quiz.begin(), quiz.find(3) );
    cout << "Sterg toate elementele pana la elementul cu cheia 3 (fara el) din Dictionarul 1: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( itr = quiz.begin() ; itr != quiz.end() ; ++itr )
        cout << itr->first << "\t" << itr->second << endl;

    cout << endl;
    /// Lower_Bound si Upper_Bound pentru Dictionarul 2 ca sa afisezi Elementul Specific unei Key
    cout << "Afisez Key Si Element din Dictionarul 2 cu lower si upper bound: " << endl;
    cout << "KEY\tELEMENT\n";
    cout << quiz2.lower_bound(4)->first << "\t" << quiz2.lower_bound(4)->second << endl;
    cout << quiz2.upper_bound(4)->first << "\t" << quiz2.upper_bound(4)->second << endl;

    cout << endl;

    cout << endl;
}
void secondSyntax(){
    cout << endl;
    /// Alta syntax de a insera elemente + auto for iterator

    quiz.insert({11,110});
    quiz.insert({12,120});
    quiz.insert({13,130});
    cout << "Adaug Elemente in Dictionarul 1: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( auto i = quiz.begin() ; i != quiz.end() ; ++i )
        cout << i->first << "\t" << i->second << endl;

    cout << endl;

    /// Verificam daca exista o cheie in Dictionarul 1
    /// count() Afiseaza numarul de aparitii intr-un multimap
    if (quiz.count(11))
        cout << "Exista Key 11 in Dictionarul 1" << endl;
    else
        cout << "Nu exista Key 11 in Dictionarul 1" << endl;

    if (quiz.count(14))
        cout << "Exista Key 14 in Dictionarul 1" << endl;
    else
        cout << "Nu exista Key 14 in Dictionarul 1" << endl;

    cout << endl;

}
void multiMapExample(){
    /// MultiMap Example
    multimap<int, int> mp;
    cout << endl;
    ///insert elements in random order
    mp.insert({ 2, 30 });
    mp.insert({ 1, 40 });
    mp.insert({ 2, 60 });
    mp.insert({ 2, 20 });
    mp.insert({ 1, 50 });
    mp.insert({ 4, 50 });

    cout << "Exemplu de MultiMap: " << endl;
    cout << "KEY\tELEMENT\n";
    for ( auto i = mp.begin() ; i != mp.end() ; ++ i )
        cout << i->first << "\t" << i->second << endl;

    cout << endl;
    cout << "Key 1 exista de : " << mp.count(1) << " ori in multimap";
    cout << endl;
    cout << "Elementele care au key = 1 sunt: " << endl;
    for ( auto i = mp.begin() ; i != mp.end() ; ++ i )
        if(i->first == 1)
            cout << i->second << endl << "si l-am crescut cu 1 acum :",
            i->second = i->second + 1,
            cout << i->second << endl;

    cout << endl;
}
void thirdSyntax(){
    cout << endl << endl;

    /// Alta Syntax a Dict
    map < string, int > dict;

    dict["Ana"] = 10;
    dict["Andrei"] = 17;
    dict["Adrian"] = 20;

    cout << dict["Adrian"];
    cout << endl << endl;
    /// Cautarea unei Element si afisarea Key

    for (auto &i : dict)
        if(i.second == 17)
            cout << "' " << i.first << " ' a fost gasita pentru elementul " << i.second << endl;
}
int main()
{
    basicFunctionAndSyntax();

    for ( int i = 0; i <= 9 ; ++i)
        cout << "---";

    secondSyntax();

    for ( int i = 0; i <= 9 ; ++i)
        cout << "---";

    multiMapExample();

    for ( int i = 0; i <= 9 ; ++i)
        cout << "---";

    thirdSyntax();
    return 0;
}
