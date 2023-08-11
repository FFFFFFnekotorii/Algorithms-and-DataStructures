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

ll ext_gcd(const ll& a, const ll& b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1, g;
    g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - ((a / b) * y1);
    return g;
}

ll inv(ll a, ll m) {
    ll a1, tmp;
    ext_gcd(a, m, a1, tmp);
    a1 = ((a1 % m) + m) % m;
    return a1;
}

void solve() {
    ll c, c1, ans, alpha, i, j, n, cur, last, q, n_minus_one_fact, alpha_fact, n_plus_alpha_fact;
    vector<int> uwu(LMT + 1, -1), min_div(LMT + 1), primes(LMT + 1), min_prime_max_power(LMT + 1);
    vector<int> uwu_by_prime_power;

    cin >> n >> c;

    uwu_by_prime_power.resize(64);

    for (i = 1; i <= LMT; i++) {
        min_div[i] = i;
    }

    n_minus_one_fact = 1;
    for (i = 2; i < n; i++) {
        n_minus_one_fact = (1LL * n_minus_one_fact * i) % MOD;
    }
    n_plus_alpha_fact = n_minus_one_fact;

    alpha_fact = 1;
    for (alpha = 1, i = n; alpha < 64; alpha++, i++) {
        n_plus_alpha_fact = (1LL * n_plus_alpha_fact * i) % MOD;
        alpha_fact = (1LL * alpha_fact * alpha) % MOD;

        uwu_by_prime_power[alpha] = (1LL * n_plus_alpha_fact * inv(n_minus_one_fact, MOD)) % MOD;
        uwu_by_prime_power[alpha] = (1LL * uwu_by_prime_power[alpha] * inv(alpha_fact, MOD)) % MOD;
    }

    uwu[1] = 1LL;

    last = 0;
    ans = 1LL;

    for (i = 2; i <= c; i++) {
        if (min_div[i] == i) {
            primes[last++] = i;
            for (j = i, alpha = 1; j <= c; j *= i, alpha++) {
                uwu[j] = uwu_by_prime_power[alpha];
                min_prime_max_power[j] = j;
                min_div[j] = i;
            }
        }
        c1 = min(c / i, (ll)min_div[i]);
        for (j = 0; j < last && primes[j] <= c1; j++) {
            min_div[i * primes[j]] = primes[j];
            if (min_div[i] == primes[j]) {
                uwu[i * primes[j]] = (1LL * uwu[i / min_prime_max_power[i]] * uwu[primes[j] * min_prime_max_power[i]]) % MOD;
                min_prime_max_power[i * primes[j]] = min_prime_max_power[i] * primes[j];
                break;
            } else {
                uwu[i * primes[j]] = (1LL * uwu[i] * uwu[primes[j]]) % MOD;
                min_prime_max_power[i * primes[j]] = primes[j];
            }
        }
        ans = (ans + 1LL * uwu[i]) % MOD;
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
