/** Author: Ber
 * tamanho do alfabeto e soma dos tamanhos das strings
*/

const int ALPHA = 26, SIZE = 305;
int I = 1;
 
// nodes do aho
// fail eh o fail link
// ch eh o automato
// podemos colocar mais coisas, tp um inteiro que diz quantas palavras terminam ali
// lembrando que temos que fazer uma dfs pra computar esse inteiro, por exemplo
struct node {
    int fail, ch[ALPHA] = {};
    // int qtd;
} T[SIZE];
 
// adj eh o grafo dos fail links invertidos, para podermos fazer a dfs e computar algm coisa 
vector<int> adj[SIZE];
 
void insert(string s, int i) {
    int x = 1;
    for (int j = 0; j < (int)s.size(); j++) {
        // mudar pra '0' se estivermos lidando com digitos
        if (T[x].ch[s[j] - 'a'] == 0)
            T[x].ch[s[j] - 'a'] = ++I;
        x = T[x].ch[s[j] - 'a'];
    }
    // T[x].qtd++; 
}
 
void build() {
    queue<int> Q;
    int x = 1; 
    T[1].fail = 1;
    for (int i = 0; i < ALPHA; i++) {
        if (T[x].ch[i])
            T[T[x].ch[i]].fail = x, Q.push(T[x].ch[i]);
        else 
            T[x].ch[i] = 1;
    }
    while (!Q.empty()) {
        x = Q.front(); Q.pop();
        for (int i = 0; i < ALPHA; i++) {
            if (T[x].ch[i])
                T[T[x].ch[i]].fail = T[T[x].fail].ch[i], Q.push(T[x].ch[i]);
            else 
                T[x].ch[i] = T[T[x].fail].ch[i];
        }
    }
    for (int i = 2; i <= I; i++)
        adj[i].push_back(T[i].fail);
}
 
int vis[SIZE];
 
int dfs(int u) {
    if (vis[u]) return T[u].qtd;
    vis[u] = 1;
    for (int v : adj[u])
        T[u].qtd += dfs(v);
    return T[u].qtd;
}

// rodar uma string pelo automato e computar alguma coisa
void run(string s) {
    for (int i = 0, x = 1; i < s.size(); i++) {
        x = T[x].ch[s[i] - 'a'];
        // T[x].cnt++;
    }
}
