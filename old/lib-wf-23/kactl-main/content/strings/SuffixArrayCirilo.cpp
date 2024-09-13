// Suffix Array
//
// Para MAXN = 1e6, MAXB deve ser maior que 20

const int MAXB = 20;
 
struct suffix_array{
    const int alpha = 300;
 
    int c[MAXB][MAXN] , p[MAXN] , cn[MAXN] , pn[MAXN] , cnt[MAXN];
    string s;
 
    void suffix_ini(){
        memset(cnt,0,sizeof cnt);
        memset(c,-1,sizeof c);
 
        int n = s.size();
 
        for(int i = 0;i < n;i++) cnt[s[i]] ++;
        for(int i = 1;i < alpha;i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1;i >= 0;i--) p[--cnt[s[i]]] = i;
 
        int cla = 0;
        c[0][p[0]] = 0;
 
        for(int i = 1;i < n;i++){
            if(s[p[i]] != s[p[i - 1]]) ++cla;
            c[0][p[i]] = cla;
        }
    }
 
    void suffix(){
        int n = s.size();
 
        for(int h = 0;(1 << h) < n;h++){
            for(int i = 0;i < n;i++){
                pn[i] = p[i] - (1 << h);
                if(pn[i] < 0) pn[i] += n;
            }
 
            memset(cnt,0,sizeof cnt);
 
            for(int i = 0;i < n;i++) cnt[c[h][pn[i]]] ++;
            for(int i = 0;i < n;i++) cnt[i] += cnt[i - 1];
            for(int i = n - 1;i >= 0;i--) p[--cnt[c[h][pn[i]]]] = pn[i];
 
            int cla = 0;
            cn[p[0]] = 0;
 
            for(int i = 1;i < n;i++){
                pair<int,int> cur = {c[h][p[i]],c[h][(p[i] + (1 << h)) % n]};
                pair<int,int> pre = {c[h][p[i - 1]],c[h][(p[i - 1] + (1 << h)) % n]};
 
                if(cur.first != pre.first || cur.second != pre.second) cla ++;
                cn[p[i]] = cla;
            }
 
            for(int i = 0;i < n;i++) c[h + 1][i] = cn[i];
        }
    }
    
    // Pre-calcula o vetor P e C (essa funcao deve ser a primeira a ser chamada)
    void sdo(string S){
        s = S;
        s += "&";
        suffix_ini();
        suffix();
    }
    
    // retorna o tamanho do maior prefixo comum
    // entre os sufixos que comecam em x e y
    int comp(int x,int y){
        int res = 0;
        int n = s.size();
 
        for(int i = MAXB - 1;i >= 0;i--){
            if(c[i][x] == -1 || c[i][y] == -1 || c[i][x] != c[i][y])
                continue;
 
            x += (1 << i);
            y += (1 << i);
            res += (1 << i);
 
            if(x >= n)
                x -= n;
            if(y >= n)
                y -= n;            
        }
 
        return res;
    }
 
    void printP(){
        cout << s << endl;
        for(int i = 0;i < s.size();i++){
            cout << p[i] << " "; 
        }
        cout << endl;
    }
};