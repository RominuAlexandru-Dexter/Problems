#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define NMAX 405
ifstream f("ferma3.in");

int mat[NMAX][NMAX];
int matFill[NMAX][NMAX];
int v[NMAX*NMAX];
int N, M, nr_zona , maxim, culoarea;

int di[4] = { -1,  0 , 1 , 0 };
int dj[4] = { 0 , 1 , 0 , -1 };
int stop = 0;
bool ok( int i , int j )
{
    if(i < 1 || j < 1 || i > N || j > M)
        return false;
    if ( matFill[i][j] != 0)
        return false;
    return true;
}
void algFill ( int x , int y)
{
     matFill[x][y] = nr_zona;
     v[nr_zona]++;

    for ( int i = 0 ; i < 4 ; ++i )
    {
        int nou_i = x + di[i];
        int nou_j = y + dj[i];
        if ( ok(nou_i, nou_j) && mat[x][y] == mat[nou_i][nou_j])
            algFill( nou_i, nou_j);
    }
}
/*void verifica ( int x , int y )
{
    for ( int i = 0 ; i < 4 ; ++i )
    {
        int nou_i = x + di[i];
        int nou_j = y + dj[i];
        if ( mat[nou_i][nou_j] != culoarea)
        {
            cout << nou_i << " " << nou_j << " " << mat[nou_i][nou_j] << endl;
            stop = 1;
            break;
        }
    }
}*/
int main()
{
    f >> N >> M;
    for ( int i = 1 ; i <= N ; ++i )
        for ( int j = 1 ; j <= M ; ++j )
        {
            char c;
            f >> c;
            mat[i][j] = (int) c;
        }

    for(int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= M; j++)
        {
            if(matFill[i][j] == 0)
            {
                nr_zona++;
                //cout << nr_zona << " ";
                algFill(i, j);
                if(maxim < v[nr_zona])
                    maxim = v[nr_zona],
                    culoarea = mat[i][j];
            }
        }
    }
    cout << maxim  << " " << culoarea << endl ;

   /* for ( int i = 1 ; i <= N ; ++i )
    {
        for ( int j = 1 ; j <= M ; ++j )
            if(mat[i][j] == culoarea && stop == 0)
                verifica(i, j);
    }*/
    return 0;
}
