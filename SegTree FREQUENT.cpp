#include <bits/stdc++.h>
using namespace std ;
#define N 100001

struct node{
    int lc,rc,ln,rn,mc ;
} ret , st[4*N] ;
int n,a[N],qs,qe ;

void bst(int i,int s,int e)
{
    if( s == e )
    {
        st[i].ln = st[i].rn = a[s] ;
        st[i].lc = st[i].rc = st[i].mc = 1 ;
        return ;
    }
    int m = (s+e)/2 ;
    int lf = 2*i+1 ;
    int rg = 2*i+2 ;
    bst( lf , s , m ) ;
    bst( rg , m+1 ,e ) ;
    st[i].ln = st[lf].ln ;
    st[i].rn = st[rg].rn ;
    if( st[lf].ln == st[rg].ln )
        st[i].lc = st[lf].lc + st[rg].lc ;
    else
        st[i].lc = st[lf].lc ;
    if( st[lf].rn == st[rg].rn )
        st[i].rc = st[lf].rc + st[rg].rc ;
    else
         st[i].rc =  st[rg].rc ;
    st[i].mc = max( st[lf].mc , st[rg].mc ) ;

    if( st[lf].rn == st[rg].ln )
        st[i].mc = max( st[i].mc , st[lf].rc + st[rg].lc ) ;
}

node query( int i,int s,int e )
{
    if( qs > e or s > qe ) // qs  s  e  qe
    {
        return ret ;
    }
    if( qs <= s and e<= qe ) return st[i] ;

//    cout << "ok2" << endl ;

    int m = (s+e)/2 ;
    int left = 2*i+1,right = 2*i+2 ;
    node a = query( left ,s , m ) ;
    node b = query( right , m+1,e ) ;
    node c ;
    c.ln = a.ln ;
    c.rn = b.rn ;
    if( a.ln == b.ln )
        c.lc = a.lc + b.lc ;
    else
        c.lc = a.lc ;
    if( a.rn == b.rn )
        c.rc = a.rc + b.rc ;
    else
        c.rc = b.rc ;
    c.mc = max( a.mc , b.mc ) ;
    if( a.rn == b.ln )
        c.mc = max( c.mc , a.rc + b.lc  ) ;

    return c ;

}

int main()
{
    ret.lc = ret.rc = ret.mc = 0 ;
    ret.ln = ret.rn = -100000000 ;
    while( true )
    {
        cin >> n ;
        if( n == 0 ) break ;
        int q ;
        cin >> q ;

        for( int i=0;i<n;i++ ) cin >> a[i] ;
        bst(0,0,n-1) ;
      //  cout << "ok" << endl ;
        while( q-- )
        {
            cin >> qs >> qe ;
            qs-- , qe-- ;
            //cout << "ok2" << endl ;
            cout << query( 0 , 0 ,n-1 ).mc << endl ;
        }


    }


    return 0;
}

// https://www.spoj.com/problems/FREQUENT/
//https://github.com/jiteshsunhala/spoj-solutions/blob/master/FREQUENT.cpp
