//REFERENCES : https://www.youtube.com/user/vivekanandkhyade  watch articulation point in it.
//REF. geeksforgeeks implementation
/*
  STEP 1) Assign discovery time to each node while doing dfs and low time which is same as discovery time
          NOTE) While doing dfs maintain the order in which nodes are found and find parent of each node.
  STEP 2) Now for each node assign it low time which is minimum of all adj except its parent.Node with high discovery time must be processed first.
          NOTE) This is for simplicity actual reason find on gfg
  STEP 3) i) Root is AP if it has more than 1 child
          ii) Except root if low time child is greater than or equal to discovery time of parent than it is AP.
*/


#include <bits/stdc++.h>
using namespace std;
#define N 100001
#define pb push_back
int n;
int parent[N],disc_time[N],low_time[N];
vector <int> v; //stores nodes in descending order of their discovery time
bool visited[N];
vector <int> G[N];
int timer=1;


void dfs(int u)
{
    visited[u]=true;
    v.pb(u);
    low_time[u]=disc_time[u]=timer++;
    for(int i=0;i<G[u].size();i++)
    {
        if( visited[ G[u][i] ] == false )
        {
            parent[ G[u][i] ] = u;
            dfs( G[u][i] );
        }
    }
}

bool isAP[N];
void Articulation_point()
{
    memset(isAP,false,sizeof(isAP));

    // ASSIGNING LOW TIME TO EACH NODE FROM NODE WITH LARGE DIS_TIME TO LESS DIS_TIME
    for(int i=v.size()-1;i>=0;i--)
    {
        for(int j=0;j<G[ v[i] ].size() ; j++ )
        {
           if( parent[ v[i] ] != G[ v[i] ][j] )
           {
               low_time[ v[i] ] = min(low_time[ v[i] ] , low_time[ G[ v[i] ][j] ]);
           }
        }
    }

    for(int child=0;child<n;child++)
    {
        if( disc_time[parent[child] ] <= low_time[child]  )
        {
            isAP[ parent[child] ] = true;
        }
    }


}

int main()
{
    int m;
    cout<<"Number of nodes and no. of edges"<<endl;
    cin>>n>>m;
    cout<<"Enter edges in zero based index"<<endl;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        G[u].pb(v);
        G[v].pb(u);
    }
    dfs(0);
    Articulation_point();
    int root=0;
    // FOR ROOT IF NUMBER OF ITS CHILD ARE MORE THAN 1 THEN IT IS AP
    int children_counter=0;
    for(int i=1;i<n;i++)
    {
        if(parent[i]==root)
            children_counter++;
    }

   // for(int i=0;i<n;i++) cout<<i<<" "<<parent[i]<<endl;
   // cout<<children_counter<<endl;

  //  if(isAP[root]) cout<<"haat yr"<<endl;
    isAP[root]=false;
    if(children_counter>1)
    {
      //  cout<<"why"<<endl;
        isAP[root]=true;
    }
   // if(isAP[root]) cout<<"haat yr"<<endl;
   cout<<"Articulation points are : \n";
    for(int i=0;i<n;i++)
    {
        if(isAP[i])
            cout<<i<<" ";
    }


    return 0;
}
/*

7 8
0 2
0 1
2 1
1 6
1 3
1 4
3 5
4 5

ans:-  1
*/

/*

10 11
0 1
0 3
3 2
1 2
2 8
8 4
8 9
4 9
4 5
9 6
6 7
ans :- 2 4 6 8 9
*/











