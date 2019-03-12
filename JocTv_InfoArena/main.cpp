#include <iostream>
#include <fstream>

using namespace std;

int N, mat[101][101] , sumaGlobala;
int row[101];
int dp[101];

void Kadane(){
    dp[1] = row[1];
    for ( int i = 2 ; i <= N ; ++ i )
    {
        if (dp[i-1] < 0)
            dp[i] = row[i];
        else
            dp[i] = dp[i-1] + row[i];
    }

    int maxim = dp[1];
    for ( int i = 2 ; i <= N ; ++ i )
        if ( dp[i] > maxim )
            maxim = dp[i];

    if(sumaGlobala < maxim )
        sumaGlobala = maxim;

    //cout << sumaGlobala << " si maximul local " << maxim;
}
void solve(){
    int Left, Right;

    for ( int Left = 0; Left <= N ; ++ Left )
    {
        fill(row, row+101, 0);
        for ( int Right = Left ; Right <= N ; ++ Right )
        {

            for ( int i = 1; i <= N ; ++ i )
                row[i] += mat[i][Right];

            fill(dp, dp+101, 0);
            Kadane();

           // cin.get();
           // cout << endl << endl;
           //for ( int i = 1; i <= N ; ++ i )
                //cout << row[i] << " " ;

            //cin.get();
        }
        //cout << endl;
    }
}
int main()
{
    ifstream f("joctv.in");
    f >> N;

    for ( int i = 1 ; i <= N ; ++ i)
        for ( int j = 1 ; j <= N ; ++ j)
            f >> mat[i][j];
    f.close();
    solve();
    //ofstream g("joctv.out");
    cout << sumaGlobala;
    return 0;
}
