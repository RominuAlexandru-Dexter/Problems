#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int N, S;
int v[100];
int main()
{
    ifstream f("date.in");
    f >> N >> S;

    for ( int i = 0 ; i < N ; ++i )
        f >> v[i];
    f.close();
    sort ( v, v+N );

    int cnt = N-1;
    int nrMonede = 0;
    while ( S != 0 )
    {
        if ( S - v[cnt] >= 0 )
            {
                S -= v[cnt];
                nrMonede++;

            }
        else if (cnt > 0)
                cnt -= 1;
             else
                break;
    }

    if (S!=0)
        cout << "-1";
    else
        cout << nrMonede;
    return 0;
}
