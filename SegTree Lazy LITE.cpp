#include <bits/stdc++.h>
using namespace std ;
#define N 100005
int n,m,st[4*N],lazy[4*N],qs,qe,us,ue ;

int qry( int i,int s,int e )
{
    if( lazy[i]%2 == 1 ) // same in update section
    {
        st[i] = (e-s+1) - st[i] ;
        if( s != e )
        {
            lazy[2*i+1]++ ;
            lazy[2*i+2]++ ;
        }
    }
    lazy[i] = 0 ;
    if( e < qs or qe < s ) // qs s e qe
        return 0 ;
    if( qs <= s and e <= qe )
        return st[i] ;
    int m = (s+e)/2 ;
    return qry( 2*i+1 , s ,m ) + qry( 2*i+2 , m+1 , e ) ;
}

void updt( int i,int s,int e )
{
    if( lazy[i]%2 == 1 )
    {
        st[i] = (e-s+1) - st[i] ;
        if( s != e )
        {
            lazy[2*i+1]++ ;
            lazy[2*i+2]++ ;
        }
    }
    lazy[i] = 0 ;
    if( e < us or ue < s  ) // us s e ue
        return ;
    if( us <= s and e <= ue )
    {
        st[i] = ( e - s + 1 ) - st[i] ;
        if( s != e )
        {
            lazy[2*i+1]++ ;
            lazy[2*i+2]++ ;
        }
        return ;
    }
    int m = (s+e)/2 ;
    updt( 2*i+1 , s , m ) ;
    updt( 2*i+2 , m+1 ,e ) ;
    st[i] = st[2*i+1] + st[2*i+2] ;

}

int main()
{
    cin >> n >> m ;
    for( int i=0;i<=4*n;i++ ) st[i] = lazy[i] = 0 ;

    while( m-- )
    {
        int c ;
        cin >> c ;
        if( c == 0 )
        {
            cin >> us >> ue ;
            us-- ;
            ue-- ;
            updt( 0 , 0 , n-1 ) ;
        }
        else
        {
            cin >> qs >> qe ;
            qs-- ;
            qe-- ;
            cout << qry( 0 , 0 , n-1 ) << endl ;
        }
    }


    return 0;
}
