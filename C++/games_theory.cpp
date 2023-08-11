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

int mex(vector<int> w) {
    int i, n;

    sort(begin(w), end(w));
    w.push_back(INF);
    w.erase(unique(begin(w), end(w)), end(w));

    n = w.size();

    for (i = 0; i < n; i++) {
        if (w[i] != i) {
            return i;
        }
    }
}

void solve() {
    int n, i, j, res, x, y, z;
    vector<vector<int>> grundy;
    vector<int> w;

    cin >> n;

    grundy.resize(101);

    for (i = 0; i < 101; i++) {
        grundy[i].resize(101, 0);
    }

    for (i = 0; i < 101; i++) {
		//<winning states>
        grundy[i][0] = INF;
        grundy[0][i] = INF;
        grundy[i][i] = INF;
		//</winning states>
    }

    for (i = 1; i < 101; i++) {
        for (j = 1; j < 101; j++) {
            if (i == j) {
                continue;
            }
			//<reachable states>
            for (x = 1; x <= i; x++) {
                w.push_back(grundy[i - x][j]);
            }
            for (y = 1; y <= j; y++) {
                w.push_back(grundy[i][j - y]);
            }
            for (z = 1; z <= min(i, j); z++) {
                w.push_back(grundy[i - z][j - z]);
            }
			//</reachable states>
            grundy[i][j] = mex(w);
            w.clear();
        }
    }
/*
    for (i = 1; i < 10; i++) {
        for (j = 1; j < 10; j++) {
            cout << grundy[i][j] << ' ';
        }
        cout << '\n';
    }
*/
    res = 0;
    for (i = 0; i < n; i++) {
		//<all figures>
        cin >> x >> y;

        res ^= grundy[x][y];
		//</all figures>
    }

    if (res) {
        cout << 'Y';
    } else {
        cout << 'N';
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
