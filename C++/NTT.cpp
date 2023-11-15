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
const int       MOD   = 167772161;

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
	
	using i64 = long long;
	using i32 = int;
	
	i32 mulmod(i32 a, i32 b, i32 mod) {
		i64 x = a, y = b, z = mod;
		return (i32)((x * y) % z);
	}
	
	i32 addmod(i32 a, i32 b, i32 mod) {
		i32 c = a + b;
		if (c < mod) {
			return c;
		}
		return c - mod;
	}
	
	i32 submod(i32 a, i32 b, i32 mod) {
		i32 c = a - b;
		if (c < 0) {
			return c + mod;
		}
		return c;
	}

	i32 powmod(i32 base, i32 n, i32 mod) {
		if (n == 0) {
			return 1;
		}
		i32 d = powmod(base, n >> 1, mod);
		d = mulmod(d, d, mod);
		if (n & 1) {
			d = mulmod(base, d, mod);
		}
		return d;
	}
}

struct fft_t {
	int g = 3, maxn, maxnrev, w1, w1rev;
	
	fft_t(int k) {
		maxn     = (1 << k);
		maxnrev  = number_theory::powmod(maxn, MOD - 2, MOD);
		w1       = number_theory::powmod(g, (MOD - 1) / maxn, MOD);
		w1rev    = number_theory::powmod(w1, MOD - 2, MOD);
	}
	
	void fft(vector<int> &p, int wn) {
		int n = p.size();
		
		if (n == 1) return ;
		
		vector<int> a(n / 2), b(n / 2);
		
		for (int i = 0; i < n / 2; i++) {
			a[i] = p[i * 2];
			b[i] = p[i * 2 + 1];
		}
		
		fft(a, number_theory::mulmod(wn, wn, MOD));
		fft(b, number_theory::mulmod(wn, wn, MOD));
		
		int w = 1, h = n / 2;
		for (int i = 0; i < h; i++) {
			p[i] = (a[i] + number_theory::mulmod(b[i], w, MOD)) % MOD;
			p[i + h] = (a[i] - number_theory::mulmod(b[i], w, MOD) + MOD) % MOD;
			
			w = number_theory::mulmod(w, wn, MOD);
		}
	}
	
	void evaluate(vector<int> &a) {
		fft(a, w1);
	}

	void interpolate(vector<int> &a) {
		fft(a, w1rev);
		for (int i = 0; i < maxn; i++) {
			a[i] = number_theory::mulmod(a[i], maxnrev, MOD);
		}
	}

	vector<int> multiply(vector<int> a, vector<int> b) {
		a.resize(maxn, 0);
		b.resize(maxn, 0);
		
		evaluate(a);
		evaluate(b);
		
		vector<int> c(maxn);
		for (int i = 0; i < maxn; i++) {
			c[i] = number_theory::mulmod(a[i], b[i], MOD);
		}
		
		interpolate(c);
		
		return c;
	}
	
	vector<int> pow(vector<int> a, int e) {
		a.resize(maxn, 0);
		
		evaluate(a);
		
		vector<int> c(maxn);
		for (int i = 0; i < maxn; i++) {
			c[i] = number_theory::powmod(a[i], e, MOD);
		}
		
		interpolate(c);
		
		return c;
	}
};

void solve() {
	
	fft_t fft(20);
	vector<int> a, b;
	int n, k, x;
	
	cin >> n >> k;
	
	a.resize(1001);
	for (int i = 0; i < n; i++) {
		cin >> x;
		a[x] = 1;
	}
	
	a = fft.pow(a, k);
	for (int i = 0; i < a.size(); i++) {
		if (a[i]) {
			cout << i << ' ';
		}
	}
}

int main() {

#ifndef LOCAL
    ios::sync_with_stdio(false);
	cin.tie(0);
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
