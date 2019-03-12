#include <iostream>
#include <fstream>


using namespace std;

int mat[1005][1005], sum[1005];
int N;


void solve(){
    for ( int i = 1 ; i <= N ; ++ i)
        for ( int j = 1 ; j <= N ; ++ j)
        {
            if (mat[i][j])
                mat[i][j] = 1 + min ( mat[i-1][j-1],  min( mat[i-1][j] , mat[i][j-1] ) );
                sum[mat[i][j]]++;

        }

}
int main()
{
    ifstream f("custi.in");
    f >> N;
    int x;
    for ( int i = 1 ; i <= N ; ++ i )
        for ( int j = 1 ; j <= N ; ++ j )
        {
            f >> x;
            if ( x == 1 )
                mat[i][j] = 1;
        }

    solve();
    for ( int i = N-1 ; i >= 1; -- i )
        sum[i] += sum[i+1];
    ofstream g("custi.out");
    for ( int i = 1 ; i <= N; ++ i )
        g << sum[i] << endl;
    return 0;
}
