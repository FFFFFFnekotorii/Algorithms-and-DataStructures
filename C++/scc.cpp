#include <bits/stdc++.h>

#define SND second
#define FST first
#define ALL(x) begin(x),end(x)
#define L(x,r) [&](auto x){r;}

#define CLEAR(u) u.back()++
#define HAS(u,x) u[x]==u.back()
#define ADD(u,x) u[x]=u.back()

using i32 = int;
using i64 = long long int;
using f64 = long double;
using i128 = __int128;

using namespace std;

const i32 INF   = 1000000007;
const i64 INF64 = 1000000000000000003LL;
const f64 EPS   = 1e-6;
const i32 MOD   = 998244353;

void dfs(vector<vector<i32>>& adj, i32 v, vector<i32>& c, vector<i32>& order) {
    c[v] = -1;

    for (i32 u : adj[v]) {
        if (c[u] == -2) {
            dfs(adj, u, c, order);
        }
    }

    order.push_back(v);
}

void dfs2(vector<vector<i32>>& adj, i32 v, vector<i32>& c) {
    for (i32 u : adj[v]) {
        if (c[u] == -1) {
            c[u] = c[v];
            dfs2(adj, u, c);
        }
    }
}

vector<i32> scc(vector<vector<i32>>& adj) {
    i32 n = adj.size();
    vector<vector<i32>> adj1(n);
    vector<i32> c(n, -2);

    for (i32 v = 0; v < n; v++) {
        for (i32 u : adj[v]) {
            adj1[u].push_back(v);
        }
    }

    vector<i32> order;
    for (i32 i = 0; i < n; i++) {
        if (c[i] == -2) {
            dfs(adj, i, c, order);
        }
    }
    reverse(ALL(order));

    for (i32 v : order) {
        if (c[v] == -1) {
            c[v] = v;
            dfs2(adj1, v, c);
        }
    }

    return c;
}

void solve() {
    vector<vector<i32>> adj;
    i32 n;

    cin >> n;

    adj.resize(n);
    for (i32 i = 0; i < n; i++) {
        i32 j;

        cin >> j;
        j--;

        if (i == j) continue;

        adj[j].push_back(i);
    }

    vector<i32> comp = scc(adj), indeg(n, 0);

    for (i32 v = 0; v < n; v++) {
        for (i32 u : adj[v]) {
            if (comp[v] != comp[u]) {
                indeg[u]++;
            }
        }
    }

    vector<i32> used(n, 0);
    i32 ans = 0;
    for (i32 i = 0; i < n; i++) {
        if (used[comp[i]]) continue;
        if (indeg[comp[i]] != 0) continue;

        queue<i32> q;
        q.push(i);
        used[comp[i]] = 1;

        while (!q.empty()) {
            i32 v = q.front();
            q.pop();

            for (i32 u : adj[comp[v]]) {
                if (!used[comp[u]]) {
                    used[comp[u]] = 1;
                    q.push(u);
                }
            }
        }

        ans++;
    }

    cout << ans;
}

i32 main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    i32 t = 1;
    //cin >> t;

    for (i32 i = 0; i < t; i++) {
        //cout << "Case #" << i + 1 << ": ";
        solve();

    }

    return 0;
}
