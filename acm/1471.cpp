//#include <GOD>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define pb push_back
#define len length
#define freo freopen("output.txt","w",stdout)
#define frei freopen("input.txt","r",stdin)

ll mark[100000+10],fi[100000+10],h[100000+10],dis[100000+10];
vector <ll> ind,hei;
vector <pair<ll,ll>> nei[100000+10];
ll n,q;
ll dp[100000+10][28],ans[100000+10][28];

void dfs(ll x){
    mark[x]=1;
    ind.pb(x);
    hei.pb(h[x]);
    fi[x]=ind.size()-1;
    for(auto v:nei[x]){
        if(!mark[v.first]){
			dis[v.first]=dis[x]+v.second;
            h[v.first]=h[x]+1;
            dfs(v.first);
            ind.pb(x);
            hei.pb(h[x]);
        }
    }
}
int main(){
    FAST_IO;

    cin>>n;
    for(int i=0;i<n-1;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        nei[u].pb({v,w});
        nei[v].pb({u,w});
    }
	dis[0]=0;
    dfs(0);
    for(int i=0;i<ind.size();i++){
        dp[i][0]=hei[i];
        ans[i][0]=ind[i];
    }
    for(int j=1;j<=(int)log2((int)ind.size());j++){
        for(int i=0;i+(1<<j)<ind.size();i++){
            dp[i][j]=dp[i][j-1];
            ans[i][j]=ans[i][j-1];
            if(dp[i+(1<<(j-1))][j-1]<dp[i][j]){
                dp[i][j]=dp[i+(1<<(j-1))][j-1];
                ans[i][j]=ans[i+(1<<(j-1))][j-1];
            }
        }
    }
    cin>>q;
    for(int i=0;i<q;i++){
        ll u,v;
        cin>>u>>v;
        if(fi[u]>fi[v]){
            swap(u,v);
        }
        ll y=(int) log2(fi[v]-fi[u]+1);
        ll lc;
		if(dp[fi[u]][y]<dp[fi[v]-(1<<y)+1][y]){
           lc=ans[fi[u]][y];
        }else{
           lc=ans[fi[v]-(1<<y)+1][y];
        }
		cout<<dis[u]-dis[lc]+dis[v]-dis[lc]<<endl;
    }
}
