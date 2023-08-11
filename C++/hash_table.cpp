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

struct hasher {
    int operator()(int x) const {
        return x ^ 7272727;
    }
};

template<int cute_size, typename cht_hasher>
struct cute_hash_table {
    vector<int> vals, keys;
    cht_hasher cute_hasher;

    cute_hash_table() {
        keys.resize(cute_size, -1);
        vals.resize(cute_size, 0);
    }

    void clear() {
        for (int i = 0; i < cute_size; i++) {
            keys[i] = -1;
            vals[i] = 0;
        }
    }

    int& operator[](const int& key) {
        int h = cute_hasher(key) % cute_size;
        while (keys[h] != key && keys[h] != -1) {
            h++;
            if (h == cute_size) {
                h = 0;
            }
        }
        keys[h] = key;
        return vals[h];
    }
};

void solve() {
    ll ans;
    int n, i, j;
    vector<int> a, b, c, d;
    cute_hash_table<9999991, hasher> htp, htn;

    htp.clear();
    htn.clear();

    cin >> n;

    a.resize(n);
    b.resize(n);
    c.resize(n);
    d.resize(n);

    for (i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (c[i] + d[j] >= 0) {
                htp[c[i] + d[j]]++;
            } else {
                htn[-(c[i] + d[j])]++;
            }
        }
    }

    ans = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (a[i] + b[j] > 0) {
                ans += htn[a[i] + b[j]];
            } else {
                ans += htp[-(a[i] + b[j])];
            }
        }
    }

    cout << ans;
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
