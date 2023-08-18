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

double unite(double a, double b) {
	return a + b - a * b;
}

void dfs(vector<vector<pair<int, int>>>& g, int s, vector<double>& dp, vector<int>& prev, vector<int>& dist) {
	
	int v, u;
	double p;
	bool added;
	vector<int> st;
	vector<pair<int, int>> par;
	vector<bool> visited;
	
	par.resize(prev.size(), make_pair(-1, -1));
	visited.resize(prev.size(), false);
	
	//<init the first vertex>
	dp[s] = 1.0;
	st.push_back(s);
	//</init>
	
	while (!st.empty()) {
		v = st.back();
		
		added = false;
		while (!g[v].empty()) {
			u = g[v].back().FST;
			p = g[v].back().SND;
			
			g[v].pop_back();
			
			if (par[v].FST == u) {
				continue;
			}
			
			//<condition: to run or not to run dfs(u)>
			if (dist[v] != dist[u] + 1) {
				continue;
			}
			//</condition: to run or not to run dfs(u)>
			
			par[u] = make_pair(v, p);
			added = true;
			
			//<init vertex for the first time>
			//if (!visited[u]) {
			//	dp[u] = smth;
			//  dfs(u);
			//}
			if (visited[u] == false) {
				if (dist[u] == 0) {
					dp[u] = 0.0;
				} else {
					dp[u] = 1.0;
				}
				visited[u] = true;
			}
			//</init vertex for the first time>
			
			st.push_back(u);
		}
		
		if (!added) {
			//<update value>
			u = par[v].FST;
			p = par[v].SND;
			if (u != -1) {
				if (dp[u] > unite(dp[v], p / 100.0)) {
					dp[u] = unite(dp[v], p / 100.0);
					prev[u] = v;
				}
			}
			//</update value>
			st.pop_back();
		}
	}
	
	
}

void solve() {
	
	int n, m, i, j, v, u, p, s, t, cur;
	vector<vector<pair<int, int>>> g, dg;
	deque<int> q;
	vector<int> dist, prev, ans;
	vector<double> dp;
	
	cin >> n >> m;
	
	cin >> s >> t;
	s--, t--;
	
	g.resize(n);
	dg.resize(n);
	for (i = 0; i < m; i++) {
		cin >> v >> u >> p;
		v--, u--;
		
		g[v].emplace_back(u, p);
		g[u].emplace_back(v, p);
	}
	
	dist.resize(n, -1);
	dist[s] = 0;
	q.push_back(s);
	while (!q.empty()) {
		v = q.front();
		q.pop_front();
		
		for (i = 0; i < g[v].size(); i++) {
			u = g[v][i].FST;
			
			if (dist[u] == -1) {
				dist[u] = dist[v] + 1;
				q.push_back(u);
			}
		}
	}
	
	prev.resize(n, -1);
	dp.resize(n, -1.0);
	dfs(g, t, dp, prev, dist);
	
    cout << dist[t] + 1 << ' ' << dp[t] << '\n';
	
	cur = t;
	while (cur != -1) {
		ans.push_back(cur);
		cur = prev[cur];
	}
	reverse(begin(ans), end(ans));
	
	for (i = 0; i < ans.size(); i++) {
		cout << ans[i] + 1 << ' ';
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
