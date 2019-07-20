// https://practice.geeksforgeeks.org/problems/egg-dropping-puzzle/0

#include <iostream>
using namespace std;
int dp[11][51];
int f(int n,int k)
{
    if(n==1) return k ;
    if(k < 2) return k ;
    if(dp[n][k] != -1  ) return dp[n][k] ;
    int ans = 1000000000;
    for(int i=1;i<=k;i++)
    {
        int temp = 1+max( f(n-1,i-1) , f(n,k-i) );
        ans = min(ans,temp);
    }
    return  dp[n][k] = ans ;
}

int main() {
	int t;
	cin >> t ;
	while(t--)
	{
	    int n,k;
	    cin >> n >> k ;
	    for(int i=0;i<=n;i++)
	        for(int j=0;j<=k;j++)
	            dp[i][j] = -1;
	    cout << f(n,k) << endl ;
	}
	return 0;
}
