
#include <bits/stdc++.h>
using namespace std ;
#define N 50000
#define endl '\n'
struct node
{
    int l,m,r,sum;
} ret ;
int a[N] , qs , qe ,pt,val ;
node st[4*N+5] ;

void bst(int i,int s,int e)
{
    if( s == e )
    {
       st[i].sum = st[i].m = st[i].l = st[i].r = a[s] ;
        return ;
    }
    int mid = (s+e)/2 ;
    bst(2*i+1,s,mid);
    bst(2*i+2,mid+1,e);
    st[i].m = max( st[2*i+1].r + st[2*i+2].l , max(  st[2*i+1].m , st[2*i+2].m )  ) ;
    st[i].sum = st[2*i+1].sum + st[2*i+2].sum ;
    st[i].l = max( st[2*i+1].l , st[2*i+1].sum + st[2*i+2].l );
    st[i].r = max( st[2*i+2].r , st[2*i+2].sum + st[2*i+1].r );
}

node query( int i,int s,int e )
{
    if( e < qs or s > qe )
        return ret ;
    if( s == e ) return st[i] ;
    if( qs <= s and e<=qe ) return st[i] ;
    int mid = ( s + e )/2 ;
    node left = query( 2*i+1,s,mid ) ;
    node right = query(2*i+2,mid+1,e) ;
    node cur ;
    cur.m = max( left.r+right.l , max( left.m , right.m ) ) ;
    cur.l = max( left.l , left.sum+right.l ) ;
    cur.r = max( right.r , right.sum + left.r );
    cur.sum = left.sum + right.sum ;
    return cur ;
}

void updt( int i , int s , int e )
{
    if( pt < s or pt > e ) return ;
    if( s == e )
    {
        st[i].sum = st[i].m = st[i].l = st[i].r = a[s] ;
        return ;
    }

    int mid = (s+e)/2 ;
    updt(2*i+1,s,mid);
    updt(2*i+2,mid+1,e);
    st[i].m = max( st[2*i+1].r + st[2*i+2].l , max(  st[2*i+1].m , st[2*i+2].m )  ) ;
    st[i].sum = st[2*i+1].sum + st[2*i+2].sum ;
    st[i].l = max( st[2*i+1].l , st[2*i+1].sum + st[2*i+2].l );
    st[i].r = max( st[2*i+2].r , st[2*i+2].sum + st[2*i+1].r );

}

int main()
{
    ret.l = ret.sum = ret.r = ret.m = -10000000 ;
    int n ;
    cin >> n ;
    for( int i=0 ; i < n ; i++ ) cin >> a[i] ;
    bst(0,0,n-1) ;
    int m;
    cin >> m ;
    while(m--)
    {
        int choice ;
        cin >> choice ;
        if(choice == 1){
            int l,r ;
            cin >> l >> r ;
            l--,r--;
            qs=l,qe=r ;
            cout << query(0,0,n-1).m << endl ;
        }
        else{
            cin >> pt >> val ;
            pt-- ;
            a[pt] = val ;
            updt(0,0,n-1) ;
        }
    }


    return 0 ;
}
