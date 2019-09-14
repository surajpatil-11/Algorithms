#include <bits/stdc++.h>
#define N 30001


using namespace std;
struct node
{
    int l,r,k,idx ;
}   Q[200001] ;
int a[N],b[N],st[4*N],n,m,qs,qe,ans[200001],pt ;

pair <int,int> A[N] ;

bool comp( node a,node b )
{
    return a.k < b.k ;
}

void bst(int i,int s,int e)
{
    if( s == e )
    {
        st[i] = b[s] ;
        return ;
    }
    int m = (s+e)/2 ;
    bst( 2*i+1 , s , m ) ;
    bst( 2*i+2 ,m+1, e ) ;
    st[i] = st[2*i+1] + st[2*i+2] ;
}

int query(int i,int s,int e)
{
    if( qs>e or qe<s ) return 0 ; // qs  s  e  qe
    if(  qs<=s and e<= qe ) return st[i] ;
    if( s == e ) return st[i] ;
    int m = (s+e)/2 ;
    return query( 2*i+1 , s ,m ) + query( 2*i+2 , m+1 ,e ) ;
}

void udt(int i,int s,int e)
{
    if( pt < s or e < pt ) return ; // s  pt e
    if( s == e )
    {
        st[i] = b[s] ;
        return ;
    }
    int m = (s+e)/2 ;
    udt( 2*i+1 , s , m ) ;
    udt( 2*i+2 ,m+1, e ) ;
    st[i] = st[2*i+1] + st[2*i+2] ;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL) ;

   // cin >> n ;
   scanf("%d",&n) ;
    for(int i=0;i<n;i++) {
         //   cin >> a[i] ;
            scanf("%d",a+i) ;
            b[i] = 1 ;
            A[i] = {a[i],i};
    }
   // cin >> m ;
    scanf("%d",&m) ;
    bst(0,0,n-1) ;
    sort(A,A+n) ;

  //  for(int i=0;i<4*n+1;i++) st[i] = 1 ;

 //   for(int i=0;i<n;i++) cout << A[i].first << " " << A[i].second << endl ;
 int l,r,k,idx ;
    for(int i=0;i<m;i++)
    {

        scanf("%d%d%d",&l,&r,&k) ;
        l--;
        r--;
        Q[i].l = l ;
        Q[i].r = r ;
        Q[i].k = k ;
        Q[i].idx = i ;
    }
    sort( Q , Q+m , comp );


    int j=0;
    for( int i=0;i<m;i++ )
    {
        int l,r,k,idx ;
        l = Q[i].l;
        r = Q[i].r;
        k = Q[i].k;
        idx=Q[i].idx;
        if(j<n)
        while( A[j].first <= k )
        {
            pt = A[j].second ;
            b[pt] = 0 ;
            udt(0,0,n-1) ;
            j++ ;
            if(j==n) break ;
        }



        qs = l;
        qe = r;

        ans[idx] = query(0,0,n-1);
    }

    for(int i=0;i<m;i++) printf("%d\n",ans[i]) ;

    return 0 ;
}
//https://www.spoj.com/problems/KQUERY/
