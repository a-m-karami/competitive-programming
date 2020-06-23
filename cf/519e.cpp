//#include <GOD>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define pb push_back
#define len length
#define freo freopen("output.txt","w",stdout)
#define frei freopen("input.txt","r",stdin)
const ll maxn=100000+10;
const ll lg=28;

ll n,m,tim;
ll h[maxn],par[maxn],st[maxn],stn[maxn],anc[maxn][lg],ft[maxn];
vector <ll> nei[maxn];

void dfs(ll u){
    h[u]=h[par[u]]+1;
    st[u]=tim++;
    stn[u]=1;
    anc[u][0]=par[u];
    for(int i=1;i<lg;i++){
        anc[u][i]=anc[anc[u][i-1]][i-1];
    }
    for(auto v:nei[u]){
        if(v!=par[u]){
            par[v]=u;
            dfs(v);
            stn[u]+=stn[v];
        }
    }
    ft[u]=tim++;
}
bool ch_anc(ll u,ll v){
    return st[u]<=st[v]&&ft[v]<=ft[u];
}
ll go_up(ll u,ll v){
    for(int i=lg-1;i>=0;i--){
        if(!ch_anc(anc[u][i],v)){
            u=anc[u][i];
        }
    }
    return u;
}
ll lca(ll u,ll v){
    if(ch_anc(u,v)){
        return u;
    }else if(ch_anc(v,u)){
        return v;
    }else{
        return anc[go_up(u,v)][0];
    }
}
ll qu(ll u,ll v){
    ll lc=lca(u,v);
    if(v==u){
        return n;
    }else if(h[u]-h[lc]==h[v]-h[lc]){
        u=go_up(u,lc);
        v=go_up(v,lc);
        return n-stn[u]-stn[v];
    }else{
        ll dis=h[u]-h[lc]+h[v]-h[lc];
        if(dis%2){
            return 0;
        }else{
            if(h[u]<h[v]){
                swap(u,v);
            }
            ll ta=u;
            for(int i=lg-1;i>=0;i--){
                if(h[u]-h[anc[ta][i]]<dis/2){
                    ta=anc[ta][i];
                }
            }
            return stn[anc[ta][0]]-stn[ta];
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
    }
	par[1]=1;
    dfs(1);
    cin>>m;
    while(m--){
        ll a,b;
        cin>>a>>b;
        cout<<qu(a,b)<<endl;
    }
}

