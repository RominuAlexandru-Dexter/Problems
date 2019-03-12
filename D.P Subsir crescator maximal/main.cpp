#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rebuild (int n , vector < int > &v , int sol, int pos, vector < int > &tata )
{
    vector < int > sir;
    /// v[tata[tata[tata[pos]]]];
    for ( int i = 1 ; i <= sol ; ++i )
        sir.push_back(v[pos]),
        pos = tata[pos];

    reverse(sir.begin(), sir.end());

    for ( int i = 0;  i < sol ; ++i )
        cout << sir[i] << " ";

}
void scmax(int n , vector < int > &v )
{
    vector < int > dp(n+1);
    vector < int > tata(n+1);

    dp[1] = 1;
    tata[1] = 0;

    for ( int i = 2 ; i <= n; ++i )
    {
        dp[i] = 1;
        tata[i] = 0;

        for ( int j = 1 ; j < i ; ++j )
        {
            if ( v[j] < v[i] )
                if ( dp[j] + 1 > dp[i] )
                    dp[i] = dp[j] + 1,
                    tata[i] = j;
        }
    }

    int sol = dp[1] , pos = 1;

    for ( int i = 2; i <= n ; ++i )
        if ( sol < dp[i] )
            sol = dp[i],
            pos = i;


    cout << sol << endl;;

    rebuild(n , v , sol , pos , tata );
}
int main()
{
    int n;
    cin >> n;
    vector < int > v(n+1);


    for ( int i = 1 ; i <= n ; ++i )
        cin >> v[i];

    scmax(n , v);
    return 0;
}
