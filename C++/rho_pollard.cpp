#pragma GCC optimize("O3,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("avx2")

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include <algorithm>
#include <cmath>
#include <random>
#include <functional>
#include <chrono>

#include <cassert>

#include <complex>

using namespace std;

using ll = long long;
using ld = long double;

const int         INF   = 1000000007;
const int         LMT   = 1000000;
const long long   INF64 = 1000000000000000003LL;
const int         MOD   = 998244353;
const long double PI    = atan2l(0, -1);

namespace debug {

	template<typename T1, typename T2>
	void print(const pair<T1, T2> &a) {
		cout << "PAIR{";
		cout << a.first << ", ";
		cout << a.second << "} ";
	}

	template<typename T>
	void print(T n) {
		cout << n << ' ';
	}

	template<typename T>
	void println(const vector<T> &a, string msg) {
		cout << msg << ' ';
		for (const T &elem : a) {
			print(elem);
		}
		cout << '\n';
	}
}

template<typename T>
T read() { T v; cin >> v; return v; }

ll isqrt(ll n) {
    ll k = sqrt(n);
    k += 1;

    while (k * k > n) {
        k--;
    }

    return k;
}

ll modadd(ll a, ll b, ll m) {
    ll res = a + b;
    if (res >= m) {
        res -= m;
    }
    return res;
}

ll modmul(ll a, ll b, ll m) {
    __int128 x = a, y = b, z = m;
    return (ll)((x * y) % z);
}

ll rho_pollard(ll n, ll c, ll seed) {

    ll x, y;

    auto f = [c, n](ll w) -> ll {
        return modadd(modmul(w, w, n), c, n);
    };

    x = seed;
    y = seed;

    int lmt = min(isqrt(isqrt(n)) + 10, 45000LL);
    ll d = 1;

    for (int i = 0; i < lmt; i++) {
        x = f(x);
        y = f(f(y));

        d = modmul(d, abs(x - y), n);
        if (i & 31) {
            d = __gcd(d, n);
            if (1 < d && d < n) {
                return d;
            }
            d = 1;
        }
    }
    d = __gcd(d, n);
    if (1 < d && d < n) {
        return d;
    }

    return n;
}

bool is_prime(ll n) {
    return false;
}

void factorize_impl(ll n, vector<ll> &pf) {
    if (n == 1) {
        return ;
    }
    if (is_prime(n)) {
        pf.push_back(n);
        return ;
    }

    mt19937_64 rnd(time(NULL));
    uniform_int_distribution<ll> uid(0, n - 1);

    for (ll c : {2, 1, -1}) {
        for (int i = 0; i < 7; i++) {
            ll d = rho_pollard(n, c, uid(rnd));

            if (1 < d && d < n) {
                factorize_impl(d, pf);
                factorize_impl(n / d, pf);
                return ;
            }
        }
    }

    pf.push_back(n);
}

void factorize(ll n, vector<ll> &pf) {
    while (!(n & 1)) {
        n /= 2;
        pf.push_back(2);
    }
    factorize_impl(n, pf);
}

void solve() {

    ll n;
    vector<ll> pf;
    pf.reserve(64);

    cin >> n;

    factorize(n, pf);

    sort(begin(pf), end(pf));

    cout << pf.size() << ' ';

    for (int i = 0; i < pf.size(); i++) {
        cout << pf[i] << ' ';
    }
    cout << '\n';
}

int main() {

#ifndef LOCAL
    ios::sync_with_stdio(false);
	cin.tie(0);
#endif

    int t;

    for (cin >> t; t; t--) {
        solve();
    }

#ifdef LOCAL
    cerr << '\n';
    system("pause");
#endif

    return 0;
}
