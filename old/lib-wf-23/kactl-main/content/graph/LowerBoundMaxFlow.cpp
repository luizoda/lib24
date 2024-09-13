/**
 * Author: Ber
 * Description: Max flow com lower bound nas arestas
 * add(a, b, l, r):
 * 	adiciona aresta de a pra b, onde precisa passar f de fluxo, l <= f <= r
 * add(a, b, c):
 * 	adiciona aresta de a pra b com capacidade c
 * Mesma complexidade do Dinic
 * INF tem que ser int, de preferencia 1e9
*/
#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const int INF = 1e9;

struct dinic {
	const bool scaling = false;
	int lim;
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};

	vector<vector<edge>> g;
	vector<int> lev, beg;
	ll F;
	dinic(int n) : g(n), F(0) {}

	void add(int a, int b, int c) {
		g[a].emplace_back(b, c, g[b].size(), false);
		g[b].emplace_back(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vector<int>(g.size(), -1); lev[s] = 0;
		beg = vector<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = INF) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};

struct lb_max_flow : dinic {
	vector<int> d;
	lb_max_flow(int n) : dinic(n + 2), d(n, 0) {}
	void add(int a, int b, int l, int r) {
		d[a] -= l;
		d[b] += l;
		dinic::add(a, b, r - l);
	}
	void add(int a, int b, int c) {
		dinic::add(a, b, c);
	}
	bool has_circulation() {
		int n = d.size();

		ll cost = 0;
		for (int i = 0; i < n; i++) {
			if (d[i] > 0) {
				cost += d[i];
				dinic::add(n, i, d[i]);
			} else if (d[i] < 0) {
				dinic::add(i, n+1, -d[i]);
			}
		}

		return (dinic::max_flow(n, n+1) == cost);
	}
	bool has_flow(int src, int snk) {
		dinic::add(snk, src, INF);
		return has_circulation();
	}
	ll max_flow(int src, int snk) {
		if (!has_flow(src, snk)) return -1;
		dinic::F = 0;
		return dinic::max_flow(src, snk);
	}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

	// recebo o numero de vertices e m arestas do tipo
	// vai de a pra b e fluxo tem que estar entre [c, d]
	// note que nao preciso adicionar uma source nem uma sink
	// o algoritmo ja faz isso por mim
    int n, m;
	cin >> n >> m;
	lb_max_flow ber(n);
	map<pii, int> id;
	vector<int> ans(m);
	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--, b--;
		id[{a, b}] = i;
		ans[i] = c;
		ber.add(a, b, c, d);
	}

	// Se tem um fluxo que atende todas as exigencias
	if (ber.has_circulation()) {
		cout << "YES" << endl;
		
		// Importante: n eh a qtd de vertices
		for (int i = 0; i < n; i++) {
			for (auto edge : ber.g[i]) {
				if (edge.res) {
					int j = edge.to;
					if (j >= n) continue;
					ans[id[{j, i}]] -= edge.flow;
				}
			}
		}

		// imprime fluxo em cada aresta
		for (int x : ans) cout << x << '\n';
	}
	else {
		cout << "NO\n";
	}
    return 0;
}