#include <iostream>
#include <vector>

using namespace std;



int main()
{
    int N, x;
    cin >> N;

    vector < int > v(N);
    vector < int > dp(N);

    for ( int i = 0 ; i < N ; ++i )
        cin >> v[i];

    dp[0] = v[0];

    for ( int i = 1 ; i < N ; ++i )
    {
        if ( dp[i-1] < 0 )
            dp[i] = v[i];
        else
            dp[i] = v[i] + dp[i-1];
    }

    int max = dp[0];

    for ( int i = 1 ; i < N ; ++i )
        if ( max < dp[i] )
            max = dp[i];

    cout << max;
    return 0;
}
