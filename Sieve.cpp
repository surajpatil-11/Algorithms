#include <bits/stdc++.h>
using namespace std;
int n ;
void sieve()
{
    bool flag[n+1];
    memset( flag , true ,sizeof flag ) ;
    for( int i=2; i*i<= n ; i++ )
    {
        if( flag[i] == true )
        {
            for(int j=i*i ; j<=n ; j+=i )
                flag[j] = false ;
        }
    }

    for(int i=2;i<=n;i++)
        if( flag[i] )
            cout << i << " " ;


}

int main()
{
    cin >> n ;
    sieve() ;
}
