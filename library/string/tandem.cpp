#include "SuffixArray.h"

vector<array<int,3>> solve(str s) {
	int N = sz(s); SuffixArray A,B; 
	A.init(s); reverse(all(s)); B.init(s);
	vector<array<int,3>> runs;
	for (int p = 1; 2*p <= N; ++p) { // do in O(N/p) for period p
		for (int i = 0, lst = -1; i+p <= N; i += p) {
			int l = i-B.getLCP(N-i-p,N-i), r = i-p+A.getLCP(i,i+p);
			if (l > r || l == lst) continue;
			runs.pb({lst = l,r,p}); // for each i in [l,r],
		} // s.substr(i,p) == s.substr(i+p,p)
	}
	return runs;
}
