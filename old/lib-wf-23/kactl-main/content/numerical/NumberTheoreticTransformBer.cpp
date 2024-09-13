/**
 * Author: NTT do KACTL
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all $k$, where $g=\text{root}^{(MOD-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of the form $2^a b+1$,
 * where the convolution result has size at most $2^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, MOD).
 * Time: O(N \log N)
 * Status: stress-tested
 */
const ll MOD = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
#pragma once

void ntt(vector<ll> &a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<ll> rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, fexp(root, MOD >> s)};
		for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % MOD;
	}
	vector<int> rev(n);
	for(int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for(int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2) {
		for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                ll z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                ai += (ai + z >= MOD ? z - MOD : z);
            }
		}
    }
}
vector<ll> conv(const vector<ll> &a, const vector<ll> &b) {
	if (a.empty() || b.empty()) return {};
	int s = a.size() + b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = fexp(n, MOD - 2);
	vector<ll> L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	for(int i = 0; i < n; i++) out[-i & (n - 1)] = (ll)L[i] * R[i] % MOD * inv % MOD;
	ntt(out);
	return {out.begin(), out.begin() + s};
}