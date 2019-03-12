
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

ifstream f( "date.in" );
ofstream g( "date.out" );


struct Punct { int x, y; };
Punct start;

vector < Punct > vNou;

int orientare2( Punct A, Punct B, Punct C )
{
    int val = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    //cout << "val = " << val << endl;

    if( val == 0 )
        return 0;
        else if( val > 0 )
                return 2; ///Stanga, trigonometric
            else
                return 1; ///Dreapta, orar
}

///Punctul de dinainte de cel curent
Punct intermediar( stack<Punct> &st )
{
    Punct vf = st.top();
    st.pop();

    /// il copiez
    Punct interm = st.top();

    /// bag fostul varf
    st.push( vf );
    return interm;
}

///Pastrez patratul, nu extrag radicalul ca sa nu am pb de aproximare
int distanta( Punct A, Punct B )
{
    return (A.x - B.x)*(A.x - B.x) + (A.y - B.y) * (A.y - B.y);
}

bool cmp( Punct A, Punct B )
{
    int val = orientare2( start, A, B );
    int distA = distanta( start, A );
    int distB = distanta( start, B );
    g << "Dist intre " << start.x << ", " << start.y  << "   si   " << A.x << ", " << A.y  << ": " << distA << endl;
    g << "Dist intre " << start.x << ", " << start.y  << "   si   " << B.x << ", " << B.y  << ": " << distB << endl;
    g << endl << endl;
    if( val == 0 )
        return ( distA <= distB );
    else
        return ( val == 2 );
}

void afiseaza_vct( vector<Punct> v )
{
    for( int i = 0; i < v.size(); ++i )
        g << "(" << v[ i ].x << ", " << v[ i ].y << ")  ";
    g << endl;
}

void interschimba( Punct &A, Punct &B )
{
    Punct aux = A;
    A = B;
    B = aux;
}

void afiseaza_stiva( stack<Punct> s )
{
    stack<Punct> cop;
    cop = s;
    Punct P;
    while( !cop.empty() )
        {
            P = cop.top();
            g << "(" << P.x << ", " << P.y << ")  ";
            cop.pop();
        }
    g << endl;
}
void convertStackToVector ( stack < Punct > st )
{
    stack < Punct > copie;
    copie = st;
    Punct pct;

    while ( !copie.empty() )
    {
        pct = copie.top();
        vNou.push_back(pct);
        copie.pop();
    }

}

int punctInConvexHull( vector <Punct> st , int muchii , Punct test)
{
    vector < Punct > copie;
    copie = st;
    int ok = 0 , i , j;
   for (i = 0, j = muchii-1; i < muchii; j = i++)
    {
        if ( ((copie[i].y > test.y) != (copie[j].y > test.y)) &&
            ( test.x < (copie[j].x - copie[i].x) * (test.y - copie[i].y ) / (copie[j].y - copie[i].y) + copie[i].x) )
            ok = !ok;
    }

    return ok;
}
int main()
{
    stack<Punct> st;
    vector<Punct> puncte;
    vector<Punct> oameni;
    int dim, i, n , m;
    /// Se introduce punctul cel mai de jos si de la stanga
    /// Se sorteaza: functia de comparare sa fie in functie de orientare.
    /// se modifica astfel incat daca mai multe puncte sunt la fel orientate la
    /// stanga, sa se aleaga cel mai indepartat
    /// Prelucrez vectorul sortat: elimin din vector pe cele care sunt coliniare
    /// suprascriind in stanga elementele care le pastrez

    Punct pct;
    f >> n;
    for( i = 0; i < n; ++i )
        f >> pct.x >> pct.y, puncte.push_back( pct );

    //for( i = 0 ; i < m; ++i)
       // f >> pct.x >> pct.y, oameni.push_back( pct );

    g << "Orientarile a trei puncte consecutive" << endl;
    for(i = 2; i < n; ++i )
        g << "("<< puncte[i-2].x << ", " << puncte[i-2].y << "),  "<< "("<< puncte[i-1].x << ", " << puncte[i-1].y << "),  "<< "("<< puncte[i].x << ", " << puncte[i].y << ") au orientarea  " << orientare2(puncte[i-2], puncte[i-1], puncte[i]) << endl;


    ///Gasesc punctul cel mai de jos, de la stanga
    int ymin, xmin, poz_min;
    poz_min = 0;
    ymin = puncte[ 0 ].y;
    xmin = puncte[ 0 ].x;
    for( i = 1; i < puncte.size(); ++i )
        {
            if( puncte[ i ].y  <  ymin )
                ymin = puncte[ i ].y, xmin = puncte[ i ].x, poz_min = i;
            if( puncte[ i ].y  ==  ymin )
                if( puncte[ i ].x < xmin )
                    xmin = puncte[ i ].x, poz_min = i;
        }
    /// Punctul de minim il voi trage pe prima pozitie in vector si apoi sortez din dreapta lui pana la sf
    /// daca e chiar pe prima pozitie, il las acolo, altfel il inlocuiesc cu elementul de pe prima pozitie
    g << endl << "Pozitia punctului de start in planul cartezian : " << xmin << ", " << ymin << endl;
    g << "Pozitia minimului in vct: " << poz_min << endl << endl;

    afiseaza_vct( puncte );
    interschimba( puncte[ 0 ], puncte[ poz_min ] );
    g << endl;
    afiseaza_vct( puncte );


    //Daca instr de mai jos nu se adauga, strica toata aranjarea deoarece pct de referinta va fi (0, 0)
    start = puncte[ 0 ];

    sort( puncte.begin() + 1, puncte.end(), cmp );
    g << endl << endl << "Vectorul sortat mai putin capatul din stanga" << endl;
    afiseaza_vct( puncte );

    g << endl << endl << "IN VECTORUL SORTAT:" << endl;
    g << "Orientarile a trei puncte consecutive" << endl;
    for(i = 2; i < n; ++i )
        g << "("<< puncte[i-2].x << ", " << puncte[i-2].y << "),  "<< "("<< puncte[i-1].x << ", " << puncte[i-1].y << "),  "<< "("<< puncte[i].x << ", " << puncte[i].y << ") au orientarea  " << orientare2(puncte[i-2], puncte[i-1], puncte[i]) << endl;






    //return 0;

    Punct primul = puncte[ 0 ];


    g << "PASTREEZ PUNCTELE CELE MAI INDEPARTATE." << endl;
    dim = 1;
    for( i = 1; i < n; ++i )
        {
            g << "("<< puncte[0].x << ", " << puncte[0].y << "),  "<< "("<< puncte[i].x << ", " << puncte[i].y << "),  "<< "("<< puncte[i+1].x << ", " << puncte[i+1].y << ") au orientarea  " << orientare2(puncte[i-2], puncte[i-1], puncte[i]) << endl;
            while( i < n - 1  &&  orientare2( primul, puncte[ i ], puncte[ i + 1 ] )  ==  0 )
                ++i;
            puncte[ dim ] = puncte[ i ];
            ++dim;
        }

    //return 0;

    g << endl << "Vectorul dupa pastrarea doar a elementelor cu rotatie st" << endl;
    g << "Ce este peste DImensiune =   " << dim << "    va fi ignorat" << endl;
    afiseaza_vct( puncte );


    if( dim >= 3 )
        {
            st.push( puncte[ 0 ] );
            st.push( puncte[ 1 ] );
            st.push( puncte[ 2 ] );
            g << endl << "Stiva initiala" << endl;
            afiseaza_stiva( st );
            g << endl << "Evolutia stivei" << endl;


            for( i = 3; i < dim; ++i )
                {
                    //cout << puncte[ i ].x << puncte[ i ].y <<  endl;
                    while( orientare2( intermediar( st ), st.top(), puncte[  i ] ) == 1 )
                        {
                            g << "       <--SCOT " << endl;
                            //cin.get();
                            st.pop();

                        }

                    g << "      -> Introduc: " << "(" << puncte[ i ].x << ", " << puncte[ i ].y << ")  ";
                    st.push( puncte[ i ] );

                }


        }

    g << endl << "Acoperirea convexa este: " << endl;

    afiseaza_stiva( st );
    convertStackToVector( st );

    cout << "Acoperirea convexa este: " << endl;
    for (auto &i : vNou )
        cout << "( " << i.x << " , " << i.y << " )" << " ";

    cout << endl;
    cout << "Cate puncte doriti sa verificati: ";

    int nrPuncte;
    cin >> nrPuncte;
    cout << "Introduceti puncte pentru a le verifica daca sunt in acoperirea conexa( x , y ): " << endl;

    for ( int i = 0 ; i < nrPuncte ; ++ i )
    {
        int x, y;
        cin >> x >> y;
        Punct test;
        bool colt = false;
        test.x = x;
        test.y = y;
        /// Exceptii cand punct-ul e un colt;
        for ( int i = 0 ; i < vNou.size() ; ++i )
        {
            if (vNou[i].x == test.x && vNou[i].y == test.y)
                colt = true;
        }
        if ( colt )
            cout << "E in convex hull";
        else if( punctInConvexHull( vNou , vNou.size(), test) )
                cout << "E in convex hull " << endl << endl;
            else
                cout << "E in afara" << endl << endl;;
    }
    return 0;
}
