#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
    
const int MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const ll INF = 2e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    return 0;
}

// bitset
//
// deve ser inicializado com um valor constante
const int N = 50;
bitset<N> bit;
// pode receber uma string binaria ou um int
bit = "1010", bit = 13;
bit.count() // quantas posicoes acesas
bit.set() // acende tudo
bit.set(3) // acende a posicao 3
bit.reset() // apaga tudo
bit.reset(4) // apaga a posicao 4
bit.flip() // flipa tudo
bit.flip(2) // flipa a posicao 2
string a = bit.to_string() // transforma em string
bit &= bit
bit |= bit
bit ^= bit 

// __int128_t
//
// nao pode ler nem printar
// pra ler use a to128
// pra printar use a tostring

__int128_t to128(string s) {
    __int128_t a = 0;
    __int128_t pot = 1;
    int n = s.size();
    for (int i = n - 1; i >= 0; i--, pot *= 10) {
        a += (s[i] - '0') * pot;
    }
    return a;
}
string tostring(__int128_t a) {
    string s;
    while (a) {
        s += (a % 10) + '0';
        a /= 10;
    }
    reverse(s.begin(), s.end());
    return (s.empty() ? "0" : s);
}