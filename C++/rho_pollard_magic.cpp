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

namespace factorization {
    ll isqrt(ll n) {
        ll k = sqrt(n) + 1;
        while (k * k > n) k--;
        return k;
    }

    ll modadd(ll a, ll b, ll m) {
        ll res = a + b;
        if (res >= m) res -= m;
        return res;
    }

    ll modmul(ll a, ll b, ll m) {
        __int128 x = a, y = b, z = m;
        return (ll)((x * y) % z);
    }

    ll rho_pollard(ll n) {
        ll x = 0, y = 0, p = 2, c = 1, t = 0, q;
        auto f = [&](ll x) { return modmul(x, x, n) + c; };
        while (t++ % 128 || __gcd(p, n) == 1) {
            if (x == y) c++, y = f(x = 2);
            if (q = modmul(p, x > y ? x - y : y - x, n)) p = q;
            x = f(x); y = f(f(y));
        }
        return __gcd(p, n);
    }

    ll power(ll a, ll b, ll M) {
        ll r = 1;
        for (; b; b /= 2, a = modmul(a, a, M))
            if (b & 1) r = modmul(r, a, M);
        return r;
    }
    bool is_prime(ll n) {
        if (n < 2 or n % 6 % 4 != 1) return (n | 1) == 3;
        auto magic = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        ll s = __builtin_ctzll(n - 1), d = n >> s;
        for (ll x : magic) {
            ll p = power(x % n, d, n), i = s;
            while (p != 1 && p != n - 1 && x % n && i--)
                p = modmul(p, p, n);
            if (p != n - 1 && i != s) return 0;
        }
        return 1;
    }

    void factorize_impl(ll n, vector<ll> &pf) {
        if (n == 1) { return ; }
        if (is_prime(n)) { pf.push_back(n); return ; }

        ll d = rho_pollard(n);

        if (1 < d && d < n) {
            factorize_impl(d, pf); factorize_impl(n / d, pf);
            return ;
        }
        pf.push_back(n);
    }

    void factorize(ll n, vector<ll> &pf) {
        while (!(n & 1)) {
            n /= 2; pf.push_back(2);
        }
        factorize_impl(n, pf);
    }
}

void solve() {

    ll n;
    vector<ll> pf;
    pf.reserve(64);

    cin >> n;

    factorization::factorize(n, pf);

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
