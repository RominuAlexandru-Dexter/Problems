#include <iostream>
#include <fstream>

using namespace std;

int N, M;
int output[100][100];
int maxim = 1;


void solve(){

    for ( int i = 1 ; i < N ; ++ i )
        for ( int j = 1; j < M ; ++ j )
            if (output[i][j])
            {
            output[i][j] = min(output[i-1][j-1], min(output[i-1][j], output[i][j-1])) + 1;
            if (output[i][j] > maxim )
                maxim = output[i][j];
            }
}
int main()
{
    ifstream f("date.in");
    f >> N >> M;
    int x;
    for ( int i = 0 ; i < N ; ++ i )
        for ( int j = 0 ; j < M ; ++ j )
        {
            f >> x;
            if ( x == 0 )
                output[i][j] = 1;
        }
    f.close();

    solve();
    cout << "Largest Sub-Square: "<<  maxim << endl;;


    for ( int i = 0 ; i < N ; ++ i )
        {
        for ( int j = 0 ; j < M ; ++ j )
            cout << output[i][j] << " ";
        cout << endl;
        }
    return 0;
}
