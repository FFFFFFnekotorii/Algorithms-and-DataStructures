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

bool in_angle(point<ll> a, point<ll> b, point<ll> c, point<ll> t) {
    point<ll> v1, v2, v3;

    v1 = a - b;
    v2 = t - b;
    v3 = c - b;

    if ((v1 ^ v2) <= 0 && (v2 ^ v3) <= 0) {
        return true;
    }
    return false;
}

void solve() {
    ll n, m, k, i, lb, rb, mid, res;
    point<ll> t;
    vector<point<ll>> p;

    cin >> n >> m >> k;

    p.resize(n);

    for (i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
    }

    res = 0;
    for (i = 0; i < m; i++) {
        cin >> t.x >> t.y;

        if (!in_angle(p[n - 1], p[0], p[1], t)) {
            continue;
        }

        lb = 1;
        rb = n;

        while (rb - lb > 1) {
            mid = (lb + rb) / 2;

            if (in_angle(p[mid], p[0], p[1], t)) {
                rb = mid;
            } else {
                lb = mid;
            }
        }

        //cout << t.x << ' ' << t.y << '\n';
        //cout << lb << '\n';

        if (!in_angle(p[lb], p[lb + 1], p[0], t)) {
            continue;
        }

        res++;
    }

    //cout << res << '\n';

    if (res < k) {
        cout << "NO";
    } else {
        cout << "YES";
    }
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
