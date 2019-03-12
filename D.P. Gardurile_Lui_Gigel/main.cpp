#include <iostream>
#include <vector>
#define MOD 1009
using namespace std;

/**
Gigel trece de la furat obiecte cu un rucsac la numarat garduri (fiecare are micile lui placeri :D).
 El doreste sa construiasca un gard folosind in mod repetat un singur tip de piesa.

O piesa are dimensiunile 4 x 1 (o unitate = 1m).
Din motive irelevante pentru aceasta problema, orice gard construit trebuie sa aiba inaltime 4m in orice punct.

O piesa poate fi pusa in pozitie orizontala sau in pozitie verticala.

Cerinta
Gigel se intreaba cate garduri de lungime n si inaltime 4 exista?
Deoarece celalalt prenume al lui este Bulănel, el intuieste ca acest numar este foarte mare,
 de aceea va cere restul impartirii acestui numar la 1009.
*/
int DP[1000001];

void solve( int n ){
    DP[1] = DP[2] = DP[3] = 1;
    DP[4] = 2;

    for ( int i = 5; i <= n; ++i )
        DP[i] = (DP[i-4] + DP[i-1]) % MOD;

    cout << DP[n];
}
int main()
{

    int n;
    cin >> n;

    if ( n <= 3)
        cout << 1;
    else if ( n == 4 )
            cout << 2;
        else
            solve(n);



    return 0;
}
