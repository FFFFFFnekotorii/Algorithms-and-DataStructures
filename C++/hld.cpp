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
#define    LMT 200000
#define  INPUT ios::sync_with_stdio(false); cin.tie(0);

#define    FST first
#define    SND second

#define    MOD 998244353LL

//#define DEBUG
//#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
    #define cout cerr
#endif

struct segment_tree_node_max {

    int val;

    segment_tree_node_max() {
        val = -INF;
    }

    segment_tree_node_max(ll ind0, ll val0) {
        val = val0;
    }

    segment_tree_node_max operator|(segment_tree_node_max other) {
        segment_tree_node_max res;

        res.val = max(val, other.val);

        return res;
    }

    void operator=(ll new_val) {
        val = new_val;
    }

};

template<typename segment_tree_node>
struct segment_tree {
    const segment_tree_node neutral = segment_tree_node();
    vector<segment_tree_node> tree;

    void resize(ll n) {
        tree.resize(n << 2);
    }

    void build(vector<ll>& a) {
        build(0, 0, tree.size() >> 2, a);
    }

    void build(ll v, ll l, ll r, vector<ll>& a) {
        if (r - l == 1) {
            tree[v] = segment_tree_node(l, a[l]);
            return;
        }
        ll m = (l + r) / 2;

        build(2 * v + 1, l, m, a);
        build(2 * v + 2, m, r, a);

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    segment_tree_node get(ll v, ll l, ll r, ll ql, ll qr) {
        if (r <= ql || qr <= l) {
            return neutral;
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }
        ll m = (l + r) / 2;

        return get(2 * v + 1, l, m, ql, qr) | get(2 * v + 2, m, r, ql, qr);
    }

    segment_tree_node get(ll ql, ll qr) {
        return get(0, 0, tree.size() >> 2, ql, qr);
    }

    void update(ll v, ll l, ll r, ll ind, ll new_val) {
        if (r - l == 1) {
            tree[v] = new_val;
            return ;
        }
        ll m = (l + r) / 2;

        if (ind < m) {
            update(2 * v + 1, l, m, ind, new_val);
        } else {
            update(2 * v + 2, m, r, ind, new_val);
        }

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    void update(ll ind, ll new_val) {
        update(0, 0, tree.size() >> 2, ind, new_val);
    }
};

template<typename inner_data_structure>
struct hld {
	inner_data_structure uwu;
	vector<vector<pair<int, int>>> g;
	vector<int> heavy, head, depth, size, parent, pos;
	
	void resize(int n) {
		uwu.resize(n);
		heavy.resize(n, -1);
		head.resize(n, -1);
		depth.resize(n, -1);
		size.resize(n, 0);
		parent.resize(n, -1);
		pos.resize(n, -1);
	}
	
	void dfs(int v) {
		int u, i, max_size;
		
		size[v] = 1;
		max_size = 0;
		
		for (i = 0; i < g[v].size(); i++) {
			u = g[v][i].FST;
			
			if (depth[u] == -1) {
				depth[u] = depth[v] + 1;
				parent[u] = v;
				dfs(u);
				size[v] += size[u];
				if (max_size < size[u]) {
					heavy[v] = u;
					max_size = size[u];
				}
			}
		}
	}
	
	void decomposition(int v, int h, int& t) {
		head[v] = h;
		pos[v] = t++;
		
		if (heavy[v] != -1) {
			decomposition(heavy[v], h, t);
		}
		int u, i, w;
		
		for (i = 0; i < g[v].size(); i++) {
			u = g[v][i].FST;
			w = g[v][i].SND;
			
			if (parent[v] == u) {
				continue;
			}
			
			if (heavy[v] != u) {
				decomposition(u, u, t);
			}
			uwu.update(pos[u], w);
		}
	}
	
	void build(vector<vector<pair<int, int>>>& g1) {
		int t;
		
		swap(g, g1);
		
		depth[0] = 0;
		t = 0;
		
		dfs(0);
		decomposition(0, 0, t);
	}
	
	int query(int v, int u) {
		int res;
		
		res = -INF;
		
		for (; head[v] != head[u]; u = parent[head[u]]) {
			if (depth[head[v]] > depth[head[u]]) {
				swap(v, u);
			}
			res = max(res, uwu.get(pos[head[u]], pos[u] + 1).val);
		}
		
		if (depth[v] > depth[u]) {
			swap(v, u);
		}
		
		res = max(res, uwu.get(pos[v] + 1, pos[u] + 1).val);
		
		return res;
	}
	
};

struct disjoint_set_union {
	vector<int> rk, par;
	
	void resize(int n) {
		rk.resize(n);
		par.resize(n);
	}
	
	void make_set(int x) {
		rk[x] = 0;
		par[x] = -1;
	}
	
	int find(int x) {
		if (par[x] == -1) {
			return x;
		}
		par[x] = find(par[x]);
		return par[x];
	}
	
	bool merge(int a, int b) {
		int v, u;
		
		v = find(a), u = find(b);
		
		if (v == u) {
			return false;
		}
		
		if (rk[v] < rk[u]) {
			swap(v, u);
		}
		
		rk[v]++;
		par[u] = v;
		
		return true;
	}
};

struct edge {
	int v, u, ind;
	ll w;
	
	edge() {}
	
	edge(int v0, int u0, int w0, int ind0) {
		v = v0;
		u = u0;
		w = w0;
		ind = ind0;
	}
	
	bool operator<(edge other) {
		return w < other.w;
	}
};

void solve() {
	
	int n, m, i, v, u, w;
	ll ans;
	vector<int> delta;
	vector<bool> included;
	vector<vector<pair<int, int>>> g;
	hld<segment_tree<segment_tree_node_max>> hld;
	vector<edge> edges;
	disjoint_set_union dsu;
	map<pair<int, int>, int> w_by_edge;
	
	cin >> n >> m;
	
	if (n == 1) {
		return ;
	}
	
	dsu.resize(n);
	g.resize(n);
	hld.resize(n);
	delta.resize(m);
	included.resize(m, false);
	edges.resize(m);
	
	for (i = 0; i < n; i++) {
		dsu.make_set(i);
	}
	
	for (i = 0; i < m; i++) {
		cin >> v >> u >> w;
		v--, u--;
		
		edges[i] = edge(v, u, w, i);
		w_by_edge[make_pair(v, u)] = w;
		w_by_edge[make_pair(u, v)] = w;
	}
	
	sort(begin(edges), end(edges));
	ans = 0;
	for (i = 0; i < m; i++) {
		v = edges[i].v;
		u = edges[i].u;
		w = edges[i].w;
		
		if (dsu.merge(v, u)) {
			ans += 1LL * w;
			included[edges[i].ind] = true;
			
			g[v].emplace_back(u, w);
			g[u].emplace_back(v, w);
		}
	}
	
	hld.build(g);
	
	for (i = 0; i < m; i++) {
		v = edges[i].v;
		u = edges[i].u;
		w = edges[i].w;
		
		if (!included[edges[i].ind]) {
			delta[edges[i].ind] = w * 1 - hld.query(v, u);
		}
	}
	
	for (i = 0; i < m; i++) {
		if (included[i]) {
			cout << ans << '\n';
		} else {
			cout << ans * 1 + 1LL * delta[i] << '\n';
		}
	}
}

int main() {
 
    #ifdef ONLINE_JUDGE
        INPUT;
    #endif
 
    int t;
 
    for (t = 1; t; t--) {
        solve();
    }
 
    #ifndef ONLINE_JUDGE
        cerr << '\n';
        system("pause");
    #endif
 
    return 0;
}
