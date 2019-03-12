#include <iostream>
#include <fstream>

using namespace std;

int N;
int val[100];
int greutate[100];
int MaxWeight;

ifstream f("date.in");
int main()
{
    int N;
    f >> N;
    for ( int i = 1 ; i <= N ; ++i )
        f >> greutate[i] ;

    for ( int i = 1 ; i <= N ; ++i )
        f >> val[i];

    f >> MaxWeight;

   int i, M;
   int dp[N+1][MaxWeight+1];

   for (i = 0; i <= N; i++)
   {
       for (M = 0; M <= MaxWeight; M++)
       {
           if (i==0 || M==0)
               dp[i][M] = 0;
           else if (greutate[i] <= M)
                    dp[i][M] = max(val[i] + dp[i-1][M-greutate[i]],  dp[i-1][M]);
                else
                    dp[i][M] = dp[i-1][M];
       }
   }


    cout << dp[N][MaxWeight];


    return 0;
}
