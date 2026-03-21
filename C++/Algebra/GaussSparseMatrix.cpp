// #define _USE_MATH_DEFINES

#pragma GCC optimize("O3")
//#include <vector>
//#pragma GCC target("avx2")
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ff first
#define ss second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define ROWS(a) (int)a.size()
#define COLS(a) (int)a[0].size()

using ll = long long int;
using ld = long double;

template<typename KEY_TYPE,
typename VALUE_TYPE,
typename COMP>
using ordered_set = tree<KEY_TYPE, VALUE_TYPE, COMP,
rb_tree_tag, tree_order_statistics_node_update>;

const int kInf = 1'000'000'007;
const int kMod =   998'244'353;

const int kMaxN = 202'048;

template <typename K, typename V>
ostream& operator<<(ostream& out, const pair<K, V>& p) {
    cout << "(" << p.first << ", " << p.second << ")";
    return out;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& xs) {
    cout << "vector{";
    for (auto x : xs) {
        cout << x << ' ';
    }
    cout << "}";
    return out;
}

template <typename T>
ostream& operator<<(ostream& out, const set<T>& xs) {
    cout << "set{";
    for (auto x : xs) {
        cout << x << ' ';
    }
    cout << "}";
    return out;
}

template <typename K, typename V>
ostream& operator<<(ostream& out, const unordered_map<K, V>& xs) {
    cout << "umap{\n";
    for (auto [k, v] : xs) {
        cout << k << " => " << v << '\n';
    }
    cout << "}";
    return out;
}

vector<pair<int, int>> line[kMaxN];
vector<int> lines_by_non_zero[kMaxN];

int mulmod(int a, int b) {
    return static_cast<int>((static_cast<ll>(a)*static_cast<ll>(b)) % kMod);
}

int solve_mod(int a, int b, int m) {
    a = ((a % m) + m) % m;
    b = ((b % m) + m) % m;
    if (a == 0) {
        return a;
    }
    if (b % a == 0) {
        return b / a;
    }
    int k = solve_mod(m, -b, a);
    return (b + 1ll * k * m) / a;
}

int inv(int a) {
    return solve_mod(a, 1, kMod);
}

void dbg_mtx(int n) {
    cout << "===matrix begin===\n";
    for (int i = 0; i < n; ++i) {
        vector<int> coef(n, 0);
        for (auto [idx, val] : line[i]) {
            coef[idx] = val;
        }
        for (int j = 0; j < n; ++j) {
            cout << coef[j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int used[kMaxN];

void sparse_matrix_gauss(int n) {
    vector<pair<int, int>> new_line;

    for (int col = 0; col < n; ++col) {
        // dbg_mtx(n);
        int row = -1;
        while (!lines_by_non_zero[col].empty()) {
            int cand = lines_by_non_zero[col].back();
            lines_by_non_zero[col].pop_back();

            if (line[cand].empty()) {
                continue;
            }
            if (line[cand][0].first != col) {
                continue;
            }
            if (used[cand]) {
                continue;
            }
            row = cand;
            break;
        }
        // cout << col << ' ' << row << '\n';
        if (row == -1) {
            continue;
        }
        used[row] = 1;

        for (int i : lines_by_non_zero[col]) {
            if (i == row) {
                continue;
            }
            if (used[i]) {
                continue;
            }
            if (line[i].empty() || line[i][0].first != col) {
                continue;
            }
            // int c = a[i][col] / a[row][col];
            // assert(line[i][0].first == col);
            int c = mulmod(line[i][0].second, inv(line[row][0].second));

            int j1 = 0;
            int j2 = 0;

            while (j1 < line[i].size() || j2 < line[row].size()) {
                if (j1 == line[i].size()) {
                    new_line.push_back({line[row][j2].first, (kMod - mulmod(line[row][j2].second, c)) % kMod});

                    if (new_line.back().second != 0) {
                        lines_by_non_zero[line[row][j2].first].push_back(i);
                    }
                    ++j2;
                    continue;
                }
                if (j2 == line[row].size()) {
                    new_line.push_back(line[i][j1]);

                    ++j1;
                    continue;
                }
                if (line[i][j1].first < line[row][j2].first) {
                    new_line.push_back(line[i][j1]);

                    ++j1;
                    continue;
                }
                if (line[i][j1].first > line[row][j2].first) {
                    new_line.push_back({line[row][j2].first, (kMod - mulmod(line[row][j2].second, c)) % kMod});

                    if (new_line.back().second != 0) {
                        lines_by_non_zero[line[row][j2].first].push_back(i);
                    }
                    ++j2;
                    continue;
                }
                new_line.push_back({line[i][j1].first, (line[i][j1].second - mulmod(line[row][j2].second, c) + kMod) % kMod});
                if (new_line.back().second != 0) {
                    lines_by_non_zero[line[row][j2].first].push_back(i);
                }

                ++j1;
                ++j2;
            }
            // cout << row << " with " << i << '\n';

            line[i].clear();
            for (auto [idx, val] : new_line) {
                if (idx == col) {
                    continue;
                }
                if (val == 0) {
                } else {
                    line[i].push_back({idx, val});
                }
            }
            new_line.clear();
        }

        lines_by_non_zero[col].clear();
        lines_by_non_zero[col].push_back(row);
    }

    // dbg_mtx(n);
}

int inv_parity(vector<int> p) {
    int ans = 0, n = p.size();
    ordered_set<int, int, less<>> was;

    for (int i = 0; i < n; ++i) {
        ans += (i - was.order_of_key(p[i]));
        ans %= 2;
        was[p[i]] = p[i];
    }

    return ans;
}

void solve() {
    int n, m;


    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int v, u;

        cin >> v >> u;
        v--, u--;

        line[v].push_back({u, 1});
        line[u].push_back({v, 1});
    }

    for (int i = 0; i < n; ++i) {
        sort(all(line[i]));
    }
    /*
    sort(line, line + n, [](auto lhs, auto rhs) -> bool {
        if (lhs.empty() || rhs.empty()) {
            return false;
        }
        return lhs[0].first < rhs[0].first;
    });
    */

    for (int i = 0; i < n; ++i) {
        for (auto [idx, val] : line[i]) {
            lines_by_non_zero[idx].push_back(i);
        }
    }

    sparse_matrix_gauss(n);

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }

    sort(all(p), [](auto i, auto j) -> bool {
        auto lhs = line[i];
        auto rhs = line[j];
        if (lhs.empty() || rhs.empty()) {
            return false;
        }
        return lhs[0].first < rhs[0].first;
    });

    int det = 1;
    for (int i1 = 0; i1 < n; ++i1) {
        int i = p[i1];
        if (line[i].empty()) {
            det = 0;
            break;
        }
        auto [idx, val] = line[i][0];
        // assert(idx >= i1);
        if (idx != i1) {
            det = 0;
            break;
        }

        det = mulmod(det, val);
    }

    if (inv_parity(p) == 1) {
        det = (kMod - det) % kMod;
    }

    cout << det << '\n';
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    // cin >> t;

    for (int i = 0; i < t; i++) {
        solve();
    }

    return 0;
}
