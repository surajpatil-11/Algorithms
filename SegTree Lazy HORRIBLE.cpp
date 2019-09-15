//ref : gfg

// Agar hum kisi node par aaye hai toh usko update karo chahe vo range mai ho ya na ho Query and Update dono mai

#include <bits/stdc++.h>
using namespace std ;
#define N 100005
#define int long long int
int st[4*N],lazy[4*N],qs,qe,us,ue,n,q,val ;

int qry(int i,int s,int e)
{
    st[i] += (e-s+1)*lazy[i] ;
    if( s != e )
    {
        lazy[2*i+1] += lazy[i] ;
        lazy[2*i+2] += lazy[i] ;
    }
     lazy[i] = 0 ;

    if( e < qs or s > qe ) // qs  s e  qe
        return 0 ;

    if( qs <= s and e <= qe )
        return st[i] ;
    int m = (s+e)/2 ;
    int ans = qry( 2*i+1 ,s ,m ) + qry( 2*i+2 , m+1 , e ) ;
   // st[i] = st[2*i+1] + st[2*i+2] ;
    return ans ;
}

// simple hai yrr kisi particular node par aao toh us pr segtree  update krke uske children k lazy mai update krdo .Agar range se bahar ho
// toh return krdo . Agar puri tarah range mai ho toh oos node k segtree ko update karo aur uske children k lazy ko update krdo.

void updt( int i,int s,int e )
{
    st[i] += ( e-s+1 )*lazy[i] ; // first update node
    if( s != e )
    {
        lazy[2*i+1] += lazy[i] ;
        lazy[2*i+2] += lazy[i] ;
    }
    lazy[i] = 0 ;

    if( e < us or ue < s  )  // Out of range
        return ;

    if( us <= s and e <= ue ) // fully in range
    {
        st[i] += ( e-s+1 )*val ;
         if( s != e )
        {
            lazy[2*i+1] += val ;
            lazy[2*i+2] += val  ;
        }
        return ;
    }
    int m = (s+e)/2 ; // partially in range
    updt( 2*i+1 , s , m ) ;
    updt( 2*i+2 , m+1 ,e ) ;
    st[i] = st[2*i+1] + st[2*i+2] ; // don't forget
}

void display(int i,int s,int e)
{
    if( s == e )
    {
        cout << s << " " << e << " | " << st[i] << " lazy : " << lazy[i] << endl ;
        return ;
    }
    int m = (s+e)/2 ;
    display( 2*i+1 ,s,m ) ;
    display( 2*i+2,m+1,e ) ;
    cout << s << " " << e << " | " << st[i] << " lazy : " << lazy[i] << endl ;
}

signed main()
{
    int tt;
    cin >> tt ;
    while( tt-- )
    {
        cin >> n >> q ;
        for(int i=0;i<=4*n;i++) st[i] = lazy[i] = 0 ;

        while( q-- )
        {
            int choice ;
            cin >> choice ;
            if( choice == 0 )
            {
                cin >> us >> ue >> val ;
                us-- ;
                ue-- ;
                updt( 0 , 0 , n-1 ) ;

             //   display(0,0,n-1) ;

            }
            else
            {
                cin >> qs >> qe ;
                qs--;
                qe--;
                cout << qry( 0 ,0 , n-1 ) << endl ;
            }
        }

    }

    return 0 ;
}

// https://www.spoj.com/problems/HORRIBLE/

