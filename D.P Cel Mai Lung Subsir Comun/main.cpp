#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
int result;
int tmp1,tmp2;
int v[1050][1050];
int dp[1050][1050];
int main()
{
    vector < int > vecN(1050);
    vector < int > vecM(1050);
    vector < int > v(1050);
    int N, M;
    ifstream f("cmlsc.in");
    ofstream g("cmlsc.out");
    f >> N >> M;

    for ( int i = 1 ; i <= N ; ++i )
        f >> vecN[i];
    for ( int i = 1 ; i <= M ; ++i )
        f >> vecM[i];



    for ( int i = 0 ; i <= N; ++ i)
        for ( int j = 0 ; j <= M; ++ j)
        {
           if ( i == 0 || j == 0 )
                dp[i][j] = 0;
           else
            if ( vecN[i] == vecM[j] )
                dp[i][j] = 1 + dp[i-1][j-1];
           else
                dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
        }

    g << dp[N][M] << endl;

    int i = N;
    int j = M;
    int index = 0;
    while ( i > 0 && j > 0 )
    {
        if(vecN[i] == vecM[j])
            v[++index] = vecN[i],
            --i,
            --j;
        else if (dp[i-1][j] > dp[i][j-1])
         i--;
      else
         j--;
    }

    for ( int i = index ; i >= 1; --i)
        g << v[i] << " ";
    return 0;
}
