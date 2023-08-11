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

template<typename T>
struct point {
    T x, y;

    point() {}

    point(T x0, T y0) {
        x = x0;
        y = y0;
    }

    point operator+(const point& other) {
        return point(x + other.x, y + other.y);
    }

    point operator-(const point& other) {
        return point(x - other.x, y - other.y);
    }

    point operator*(const T& k) {
        return point(x * k, y * k);
    }

    T operator*(const point& other) {
        return x * other.x + y * other.y;
    }

    T operator^(const point& other) {
        return x * other.y - y * other.x;
    }

    T length2() {
        return x * x + y * y;
    }

    ld length() {
        return sqrtl(length2());
    }

    bool operator==(const point& other) {
        if (x == other.x && y == other.y) {
            return true;
        }
        return false;
    }
};

bool bad(point<ll> a, point<ll> b, point<ll> c) {
    if (((b - a) ^ (c - b)) < 0) {
        return false;
    }
    return true;
}

void solve() {
    ll i, n, k, s;
    point<ll> pp;
    vector<point<ll>> p, ch;

    cin >> n;

    p.resize(n);

    for (i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    sort(begin(p), end(p), [](point<ll>& p1, point<ll>& p2)->bool {
         return (p1.y < p2.y);
    });

    pp = p[0];

    sort(begin(p), end(p), [pp](point<ll>& p1, point<ll>& p2)->bool {
         point<ll> v1, v2;

         v1 = p1 - pp;
         v2 = p2 - pp;

         if ((v1 ^ v2) == 0) {
            return (v1.length2() > v2.length2());
         } else {
             return ((v1 ^ v2) < 0);
         }
    });
/*
    cout << "SORTED\n";

    for (i = 0; i < n; i++) {
        cout << p[i].x << ' ' << p[i].y << '\n';
    }

    cout << "\n";
*/
    ch.push_back(p[0]);
    ch.push_back(p[1]);
    k = 2;

    for (i = 2; i < n; i++) {
        while (k > 1 && bad(ch[k - 2], ch[k - 1], p[i])) {
            ch.pop_back();
            k--;
        }

        ch.push_back(p[i]);
        k++;
    }

    while (k > 2 && bad(ch[k - 2], ch[k - 1], ch[0])) {
        ch.pop_back();
        k--;
    }

    cout << k << '\n';

    for (i = 0; i < k; i++) {
        cout << ch[i].x << ' ' << ch[i].y << '\n';
    }

    s = 0;
    for (i = 2; i < k ; i++) {
        s += (ch[i - 1] - ch[0]) ^ (ch[i] - ch[0]);
    }

    cout << fixed;

    cout.precision(18);

    cout << (ld)abs(s) / 2.0;
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
