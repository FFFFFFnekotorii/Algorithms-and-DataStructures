#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <bitset>
#include <random>

#include <chrono>
#include <cassert>

using namespace std;

typedef long long int ll;
typedef long double ld;

#define    INF 1000000007
#define  INF64 1000000000000000003LL
#define    LMT 1000000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define    MOD 998244353LL

#ifdef LOCAL
    #define cout cerr
#endif

template<int p1, int p2, int mod>
struct hash_string2d {
    vector<vector<int>> h, pq;

    void init(vector<vector<int>>& a) {
        int i, j, n, m;

        n = a.size(), m = a[0].size();

        h.resize(n + 1, vector<int>(m + 1, 0));
        pq.resize(n + 1, vector<int>(m + 1, 1));

        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                h[i + 1][j + 1] = (1LL * h[i][j + 1] * p1 + 1LL * h[i + 1][j] * p2 - 1LL * h[i][j] * p1 * p2 + 1LL * a[i][j]) % (1LL * mod);
                pq[i + 1][j + 1] = (1LL * pq[i][j] * p1 * p2) % (1LL * mod);
                pq[i + 1][j] = (1LL * pq[i][j] * p1) % (1LL * mod);
                pq[i][j + 1] = (1LL * pq[i][j] * p2) % (1LL * mod);
            }
        }
    }

    int get(int x1, int y1, int x2, int y2) {
        int ans;
        ans = (1LL * h[x2][y2] - 1LL * h[x1][y2] * pq[x2 - x1][0] % (1LL * mod));
        ans = (1LL * ans - 1LL * h[x2][y1] * pq[0][y2 - y1] + 1LL * h[x1][y1] * pq[x2 - x1][y2 - y1]) % (1LL * mod);
        return (ans + mod) % mod;
    }
};

void solve() {
	
	int h1, h2;
	vector<vector<int>> a;
	
	a.resize(3);
	a[0] = {0, 0, 1, 1};
	a[1] = {1, 0, 1, 0};
	a[2] = {0, 0, 1, 0};
	
	hash_string2d<727, 1337, 1000000007> h;
	
	h.init(a);
	
	h1 = h.get(0, 0, 0, 2);
	h2 = h.get(2, 0, 2, 2);
	
	cout << (h1 == h2 ? "YES" : "NO") << "\n";
	
	h1 = h.get(0, 1, 2, 3);
	h2 = h.get(1, 1, 3, 3);
	
	cout << (h1 == h2 ? "YES" : "NO") << "\n";
	
}

int main() {
 
    #ifndef LOCAL
        INPUT;
    #endif
	
    int t;
 
    for (t = 1; t; t--) {
        solve();
    }
 
    #ifdef LOCAL
        cerr << '\n';
        system("pause");
    #endif
 
    return 0;
}
