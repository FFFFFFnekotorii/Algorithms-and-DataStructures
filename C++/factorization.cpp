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

const int       INF   = 1000000007;
const int       LMT   = 1000000;
const long long INF64 = 1000000000000000003LL;
const long long MOD   = 998244353LL;

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

namespace number_theory {
	
	using i64  = long long;
	using i128 = __int128;
	
	i64 mulmod(i64 a, i64 b, i64 c) {
		i128 x = a, y = b, z = c;
		return (i64)((x * y) % z);
	}

	i64 powmod(i64 base, i64 e, i64 mod) {
		i64 result = 1;
		base %= mod;
		while (e) {
			if (e & 1) {
				result = mulmod(result, base, mod);
			}
			base = mulmod(base, base, mod);
			e >>= 1;
		}
		return result;
	}
	
	i64 isqrt(i64 n) {
		i64 res = n;
		for (i64 i = 0; i < 64; i++) {
			res = (res + n / res) >> 1;
		}
		return res;
	}

	bool check_composite(i64 n, i64 a, i64 d, int s) {
		i64 x = powmod(a, d, n);
		if (x == 1 || x == n - 1) {
			return false;
		}
		for (int r = 1; r < s; r++) {
			x = (i128)x * x % n;
			if (x == n - 1) {
				return false;
			}
		}
		return true;
	}
	
	bool MillerRabin(i64 n) {
		if (n < 2) {
			return false;
		}

		int r = 0;
		i64 d = n - 1;
		while ((d & 1) == 0) {
			d >>= 1;
			r++;
		}

		for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
			if (n == a) {
				return true;
			}
			if (check_composite(n, a, d, r)) {
				return false;
			}
		}
		return true;
	}
	
	i64 f(i64 x, i64 c, i64 mod) {
		i64 r = mulmod(x, x, mod);
		r += c;
		if (r >= mod) {
			r -= mod;
		}
		return r;
	}
	
	i64 brent(i64 n, i64 x0, i64 c) {
		i64 x = x0;
		i64 g = 1;
		i64 q = 1;
		i64 xs = 0;
		i64 y = 0;
	 
		i64 m = 128;
		i64 l = 1;
		while (g == 1) {
			y = x;
			for (i64 i = 1; i < l; i++) {
				x = f(x, c, n);
			}
			i64 k = 0;
			while (k < l && g == 1) {
				xs = x;
				for (i64 i = 0; i < m && i < l - k; i++) {
					x = f(x, c, n);
					q = mulmod(q, abs(y - x), n);
				}
				g = __gcd(q, n);
				k += m;
			}
			l *= 2;
		}
		if (g == n) {
			do {
				xs = f(xs, c, n);
				g = __gcd(abs(xs - y), n);
			} while (g == 1);
		}
		return g;
	}
	
	i64 fermat(i64 n) {
		i64 x = isqrt(n) + 1;
		for (i64 i = 0; i < 100; i++) {
			i64 y = isqrt(x * x - n);
			
			if (x * x - y * y == n) {
				return x - y;
			}
			x++;
		}
		return n;
	}
	
	void factorization_rec(i64 n, vector<i64> &prime_divisors) {
		if (n == 1) {
			return ;
		}
		
		i64 s = isqrt(n);
		if (s * s == n) {
			factorization_rec(s, prime_divisors);
			factorization_rec(s, prime_divisors);
			return ;
		}
		
		if (MillerRabin(n)) {
			prime_divisors.push_back(n);
			return ;
		}
		
		i64 d = fermat(n);
		if (1 < d && d < n) {
			factorization_rec(n / d, prime_divisors);
			factorization_rec(d, prime_divisors);
			return ;
		}
		
		i64 x0 = 2, c = 1;
		while (true) {
			i64 d = brent(n, x0, c);
			
			if (1 < d && d < n) {
				factorization_rec(n / d, prime_divisors);
				factorization_rec(d, prime_divisors);
				return ;
			}
			c++;
		}
	}
	
	void factorization(i64 n, vector<i64> &prime_divisors) {
		i64 d, c;
		
		c = min(isqrt(n), 1000LL);
		
		for (d = 2; d < c; d++) {
			while (n % d == 0) {
				n /= d;
				prime_divisors.push_back(d);
			}
		}
		
		factorization_rec(n, prime_divisors);
	}
}

void solve() {
	
	long long n;
	vector<long long> p;
	
	cin >> n;
	
	number_theory::factorization(n, p);
	
	sort(begin(p), end(p));
	
	cout << p.size() << '\n';
	
	for (long long prime : p) {
		cout << prime << ' ';
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
