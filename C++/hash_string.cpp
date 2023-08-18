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

template<ll base, ll mod>
struct hash_string {
    vector<ll> base_power, prefix_hash;

    void init(const string& s) {
        prefix_hash.resize(s.size() + 1, 0);
        base_power.resize(s.size() + 1, 1);
        for (int i = 0; i < s.size(); i++) {
            prefix_hash[i + 1] = (prefix_hash[i] * base + (s[i] - 'a' + 1)) % mod;
            base_power[i + 1] = (base_power[i] * base) % mod;
        }
    }

    ll get_hash(int l, int r) {
        return ((prefix_hash[r] - (prefix_hash[l] * base_power[r - l]) % mod) + mod) % mod;
    }
};

void solve() {
	
	string s;
	hash_string<31, 1000000007> hs;
	
	s = "uwuowouwu";
	
	hs.init(s);
	
	cout << (hs.get_hash(0, 2) == hs.get_hash(6, 8) ? "YES" : "NO") << '\n';
	
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
