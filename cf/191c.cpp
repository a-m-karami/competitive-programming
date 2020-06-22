//#include <GOD>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define pb push_back
#define len length
#define freo freopen("output.txt","w",stdout)
#define frei freopen("input.txt","r",stdin)

ll n,k;
vector <ll> nei[100000+10],ind,hei;
vector <pair<ll,ll>> ed;
ll mark[100000+10],mark0[100000+10],cnt[100000+10],fi[100000+10],h[100000+10],dpc[100000+10],dp[200000+10][28],ans[200000+10][28];

void dfs(ll u){
    mark[u]=1;
    ind.pb(u);
    hei.pb(h[u]);
    fi[u]=ind.size()-1;
    for(auto v:nei[u]){
        if(!mark[v]){
            h[v]=h[u]+1;
            dfs(v);
            ind.pb(u);
            hei.pb(h[u]);
        }
    }
}
void dfs0(ll u){
    mark0[u]=1;
    dpc[u]+=cnt[u];
    for(auto v:nei[u]){
        if(!mark0[v]){
            dfs0(v);
            dpc[u]+=dpc[v];
        }
    }
}
int main(){
	FAST_IO;

	cin>>n;
	for(int i=0;i<n-1;i++){
        ll u,v;
        cin>>u>>v;
        nei[u].pb(v);
        nei[v].pb(u);
        ed.pb({u,v});
	}
	dfs(1);
	for(int i=0;i<ind.size();i++){
        dp[i][0]=hei[i];
        ans[i][0]=ind[i];
       // cout<<ind[i]<<' '<<hei[i]<<endl;
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
	cin>>k;
	for(int i=0;i<k;i++){
        ll a,b;
        cin>>a>>b;
        cnt[a]++;
        cnt[b]++;
        if(fi[a]>fi[b]){
            swap(a,b);
        }
        ll le=(int)log2(fi[b]-fi[a]+1);
        ll lc;
        if(dp[fi[b]-(1<<le)+1][le]>dp[fi[a]][le]){
            lc=ans[fi[a]][le];
        }else{
            lc=ans[fi[b]-(1<<le)+1][le];
        }
       // cout<<lc<<endl;
        cnt[lc]-=2;
	}
	dfs0(1);
for(int i=0;i<n-1;i++){
        ll u=ed[i].first;
        ll v=ed[i].second;
        if(h[u]<h[v]){
            swap(u,v);
        }
        cout<<dpc[u]<<' ';
	}
//	for(int i=1;i<=n;i++){
  //      cout<<cnt[i]<<endl;
	//}
}
