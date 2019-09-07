//  https://www.spoj.com/problems/KGSS/
//  Whenever you want to merge two nodes then first merge leaf node
//  In point update  first update the array then do as it is in query
#include <bits/stdc++.h>
using namespace std ;
#define N 100005
int n,a[N] ;
struct node
{
    int fmax,smax ; // first max , second max
}ret;
node st[4*N] ;
void bst(int i,int s,int e)
{
    if( s == e )
    {
        st[i].fmax = a[s] ,st[i].smax = 0 ;
        return ;
    }
    int m = (s+e)/2 ;
    bst( 2*i+1 , s , m ) ;
    bst( 2*i+2 , m+1 , e ) ;
    st[i].fmax = max( st[2*i+1].fmax , st[2*i+2].fmax ) ;
    st[i].smax = max(  min( st[2*i+1].fmax , st[2*i+2].fmax ) , max(st[2*i+1].smax , st[2*i+2].smax) ) ;
}
int pt ;
void updt( int i ,int s,int e)
{
    if( pt < s or e < pt ) return ;
    if( s == e )
    {
        st[i].fmax = a[s] , st[i].smax = 0;
        return ;
    }
    int m = (s+e)/2 ;
    updt( 2*i+1 , s , m ) ;
    updt( 2*i+2 , m+1 , e ) ;
    st[i].fmax = max( st[2*i+1].fmax , st[2*i+2].fmax ) ;
    st[i].smax = max(  min( st[2*i+1].fmax , st[2*i+2].fmax ) , max(st[2*i+1].smax , st[2*i+2].smax) ) ;
}

int qs,qe ;
node query(int i,int s,int e)
{
    if( qe < s or e < qs ) return ret ;
    if( qs <= s and e <= qe )
    {
        return st[i] ;
    }
    int mid = (s+e)/2 ;
    node left = query(2*i+1,s,mid) ;
    node right = query(2*i+2,mid+1,e) ;
    node cur ;
    cur.fmax = max( left.fmax , right.fmax ) ;
    cur.smax = max(  min( left.fmax , right.fmax ) , max(left.smax , right.smax) ) ;
    return cur ;
}

int main()
{
    ret.fmax = ret.smax = 0  ;
    cin >> n ;
    for( int i=0 ; i < n ; i++ ) cin >> a[i] ;
    bst(0,0,n-1) ;
    int m;
    cin >> m ;
    while( m-- )
    {
        string ch ;
        cin >> ch ;
        if( ch == "Q" )
        {
            cin >> qs >> qe ;
            qs--,qe--;
            node ans = query( 0 , 0 , n-1 ) ;
            cout << ans.fmax + ans.smax << endl ;
        }
        else
        {
            int val ;
            cin >> pt >> val ;
            pt--;
            a[pt] = val ;
            updt( 0 , 0 , n-1 ) ;
        }

    }
    return 0 ;
}
