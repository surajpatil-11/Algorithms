#include <bits/stdc++.h>
using namespace std ;
#define N 200005
int n,m,st[4*N],lazy[4*N],qs,qe,us,ue,a[N] ;

void bst(int i,int s,int e)
{
    if( s == e )
    {
        st[i] = a[s] ;
        return ;
    }
    int m = (s+e)/2 ;
    bst( 2*i+1 , s, m ) ;
    bst( 2*i+2 , m+1 ,e ) ;
    st[i] = st[2*i+1] + st[2*i+2] ;
}

int qry(int i,int s,int e)
{
    if( lazy[i]%2 == 1 )
    {
        st[i] = ( e - s + 1 ) - st[i] ;
        if( s != e )
        {
            lazy[2*i+1]++ ;
            lazy[2*i+2]++ ;
        }
    }

    lazy[i] = 0 ;
    if( e < qs or qe < s ) return 0 ;
    if( qs <= s and e <= qe ) return st[i] ;
    int m = ( s + e )/2 ;
    return qry( 2*i+1 ,s , m ) + qry( 2*i+2 ,m+1 , e ) ;
}

void updt(int i,int s,int e)
{
     if( lazy[i]%2 == 1 )
    {
        st[i] = ( e - s + 1 ) - st[i] ;
        if( s != e )
        {
            lazy[2*i+1]++ ;
            lazy[2*i+2]++ ;
        }
    }

    lazy[i] = 0 ;
      if( e < us or ue < s ) return  ;
      if( us <= s and e <= ue )
      {
          st[i] = (e-s+1) - st[i] ;
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

    for(int i=0;i<=4*n;i++) lazy[i] = 0 ;

    string str ;
    cin >> str ;
    n-- ;
    for( int i=0;i<n;i++ )
    {
        if( str[i] == '>' ) a[i] = 1 ;
        else a[i] = 0 ;
    }
    bst(0,0,n-1) ;
    while( m-- )
    {
        int c ;
        cin >> c ;
        if( c == 1 )
        {
            cin >> us >> ue ;
            us-- ;
            ue-- ;
            ue-- ;
            updt(0,0,n-1) ;
        }
        else
        {
            cin >> qs >> qe ;
            qs-- ;
            qe-- ;

            if( qs <= qe )
            {
                qe-- ;
                cout <<  ( qe - qs +1 ) - qry(0,0,n-1) << endl ;
            }
            else
            {
                qs-- ;
                swap( qs , qe ) ;
                cout <<  qry(0,0,n-1) << endl ;
            }
        }
    }

    return 0 ;
}
//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/monk-and-otakuland-1/description/
