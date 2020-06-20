// weakly tested on cses
struct bipartite_match{ // 1 indice
  int n , m;
  vector<vi> g; vi vis , match;
  int ans=0;
  bipartite_match(int n , int m) : n(n) , m(m), vis(n+m+2) , match(n+m+2) , g(n+m+2){}
 
  void add(int x,int y){
    g[x].pb(y + n);
    g[y + n].pb(x);
  }
  bool dfs(int x){
    allin(w,g[x]){
      if(vis[w]) continue;
      vis[w] = true;
      if(match[w] == 0 || dfs(match[w])){
        match[w] = x, match[x] = w; 
        return true;
      }
    }
    return false;
  }
  int solve(){
     bool haspath;
    do{
      haspath = false;
      fill(all(vis) , false);
      for(int i = 1 ; i<= n + m; i ++){
        if(!match[i] && dfs(i)) haspath = 1 , ans ++ ;
      }
    } while(haspath);
    return ans;
  }

  // status: weakly tested
  void dfs2(int v){
    vis[v] = 1;
    for(auto w : g[v]){
      if(vis[w])continue;
      if(v<=n){
          if(match[w]!=v)dfs2(w);
      }else{
        if(match[v]==w)dfs2(w);
      }
    }
  }
  vector<int> vertex_cover(){
    vector<int> res;
    fill(all(vis),false);
    for(int i=1;i<=n;i++){
      if(match[i]==0){
        dfs2(i);
      }
    }
    for(int i=1;i<=n;i++){
      if(match[i]!=0 and !vis[i]){
        res.pb(i);
      }
    }
    for(int i=n+1;i<=n+m;i++){
      if(vis[i]){
        res.pb(i);// change the index if needed
      }
    }
    assert(sz(res)==solve());
    return res;
  }
  // end of vertex cover
  // status: not tested
  vector<int> independent_set(){
    vi cover = vertex_cover();
    fill(all(vis),false);
    for(int x : cover)vis[x]=1;
    vi res;
    for(int i=1;i<=n+m;i++)if(!vis[i])res.pb(i);
    assert(sz(res) == n - solve());
    return res;
  }
  // not tested:
  vector<pii> edge_cover(){
    vector<pii> res;
    for(int i=1;i<=n;i++){
      if(match[i]){
        for(auto w : g[i]){
          res.pb(pii(i,w));
        }
      }
    }
    for(int i=n+1;i<=n+m;i++){
      if(match[i]){
        for(auto w : g[i]){
          if(!match[w])res.pb(pii(w,i));
        }
      }
    }
    assert(sz(res) == n - solve());
    return res;
  }

  int matchL(int x){return (match[x] ? match[x] - n : 0);}
  int matchR(int x){return match[x+n];}
};
