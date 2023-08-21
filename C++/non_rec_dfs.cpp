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

#define INF   1000000007
#define INF64 1000000000000000003LL
#define LMT   1000000
#define INPUT ios::sync_with_stdio(false);cin.tie(0);

#define FST   first
#define SND   second

#define MOD   998244353LL

#ifdef LOCAL
    #define cout cerr
#endif

void dfs(vector<vector<int>>& g, int s) {
	
	int v, u;
	bool added;
	vector<int> st;
	vector<int> par;
	
	par.resize(g.size(), -1);
	
	st.push_back(s);
    cout << s + 1 << '\n';
	
	while (!st.empty()) {
		v = st.back();
		
		added = false;
		while (!g[v].empty()) {
			u = g[v].back();
			
			g[v].pop_back();
			
			if (par[v] == u) {
				continue;
			}
			
			par[u] = v;
			added = true;
			
			st.push_back(u);
            cout << u + 1 << '\n';
            break;
		}
		
		if (!added) {
			st.pop_back();
            if (par[v] != -1) {
                cout << par[v] + 1 << '\n';
            }
        }
        
	}
	
	
}

void solve() {
	
	int n, m, i, v, u;
	vector<vector<int>> g;
	
	cin >> n >> m;
	
	g.resize(n);
	for (i = 0; i < m; i++) {
		cin >> v >> u;
		v--, u--;
		
		g[v].push_back(u);
		g[u].push_back(v);
	}
	
	dfs(g, 0);
    
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
