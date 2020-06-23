//#include <GOD>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define pb push_back
#define len length
#define freo freopen("output.txt","w",stdout)
#define frei freopen("input.txt","r",stdin)

ll n,mod=1e9+7,k,sum;
vector <ll> ind,hei;
vector <pair<ll,ll>> ed,nei[100000+10];
ll mark[100000+10],mark0[100000+10],fi[100000+10],h[100000+10],ka[100000+10],dpc[100000+10],dp[200000+10][28],ans[200000+10][28],cnt[100000+10],st[1000000+10];

void dfs(ll u){
    mark[u]=1;
    ind.pb(u);
    hei.pb(h[u]);
    fi[u]=ind.size()-1;
    for(auto v:nei[u]){
        if(!mark[v.first]){
            h[v.first]=h[u]+1;
            dfs(v.first);
            ind.pb(u);
            hei.pb(h[u]);
            if(v.second){
                ka[v.first]=1;
            }
        }
    }
}
void dfs0(ll x){
    mark0[x]=1;
    dpc[x]+=cnt[x];
    for(auto v:nei[x]){
        ll y=v.first;
        if(!mark0[y]){
            dfs0(y);
            dpc[x]+=dpc[y];
        }
    }
}
ll power(ll a,ll b){
    if(!b){
        return 1;
    }
    ll c=power(a,b/2);
    if(b%2){
        return c*c%mod*a%mod;
    }else{
        return c*c%mod;
    }
}
int main(){
	FAST_IO;

    cin>>n;
    for(int i=0;i<n-1;i++){
        ll u,v,w;
        cin>>u>>v>>w;
        if(w){
            ed.pb({u,v});
        }
        nei[u].pb({v,w});
        nei[v].pb({u,0});
    }
    dfs(1);
    for(int i=0;i<ind.size();i++){
        dp[i][0]=hei[i];
        ans[i][0]=ind[i];
        //cout<<ind[i]<<' '<<hei[i]<<endl;
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
    st[0]=1;
    for(int i=1;i<=k;i++){
            cin>>st[i];
    }
    for(int i=0;i<k;i++){
        ll u=st[i];
        ll v=st[i+1];
        if(fi[v]<fi[u]){
            swap(u,v);
        }
        ll le=(int)log2(fi[v]-fi[u]+1);
        ll lc;
        if(dp[fi[u]][le]<dp[fi[v]-(1<<le)+1][le]){
            lc=ans[fi[u]][le];
        }else{
            lc=ans[fi[v]-(1<<le)+1][le];
        }
        cnt[u]++;
        cnt[v]++;
        cnt[lc]-=2;
        //cout<<lc<<endl;
    }
    dfs0(1);
   // for(int i=1;i<=n;i++){
      //  cout<<dpc[i]<<endl;
    //}
    for(int i=0;i<ed.size();i++){
        ll u,v;
        u=ed[i].first;
        v=ed[i].second;
        if(h[u]<h[v]){
            swap(u,v);
        }
        if(!ka[u]){
            ll y=(dpc[u]+1)/2;
            sum+=((power(2,y))-1+mod)%mod;
            sum%=mod;
        }else{
            sum+=((power(2,dpc[u]/2))-1+mod)%mod;
            sum%=mod;
        }
        //cout<<dpc[u]<<endl;
    }
    cout<<sum<<endl;
}
