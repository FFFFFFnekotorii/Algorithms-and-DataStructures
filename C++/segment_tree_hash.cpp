#pragma GCC optimize("O3,fast-math,unroll-loops")

#include <memory>
#pragma GCC target("avx,bmi,sse4.2,popcnt,lzcnt")

#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <iomanip>
#include <optional>

using namespace std;

#define FST first
#define SND second
#define ALL(x) x.begin(), x.end()

using ll  = long long;
using ld  = long double;
using ull = unsigned long long;

const ll kInf64 = 1'000'000'000'000'000'003LL;
const int kInf  = 1'000'000'007;
const int kMod  = 998'244'353;

const int kMaxN = 1 << 19;
const int kSegTreeSize = kMaxN * 2;

struct EdgeGroup {
    int v, u, l, c;
};

EdgeGroup eds[kMaxN];
int color[kMaxN];
vector<int> by_color[kMaxN];

template <int mod>
int mulmod(int a, int b) {
    return ((ll)a * b) % mod;
}

template <int base, int mod>
struct segment_tree_node_hash {
    inline static int base_power[kSegTreeSize];
    int h = 0, len = 0;

    segment_tree_node_hash() = default;
    segment_tree_node_hash(int h, int len) : h(h), len(len) {}
    segment_tree_node_hash(int h) : h(h), len(1) {}

    static void init() {
        base_power[0] = 1;
        for (int i = 1; i < kSegTreeSize; ++i) {
            base_power[i] = mulmod<mod>(base_power[i - 1], base);
        }
    }

    segment_tree_node_hash operator|(segment_tree_node_hash oth) {
        int h1 = mulmod<mod>(h, base_power[oth.len]) + oth.h;
        if (h1 >= mod) {
            h1 -= mod;
        }
        // cout << "merge: " << h << ' ' << oth.h << ' ' << h1 << '\n';
        // cout << "merge2: " << base_power[oth.len] << '\n';
        return segment_tree_node_hash(h1, len + oth.len);
    }
};

template <typename node>
struct segment_tree {
    node tree[kSegTreeSize];
    int n;

    segment_tree() {}

    void resize(int new_n) {
        n = new_n;
    }

    template <typename Fn>
    void build(int v, int l, int r, Fn init) {
        if (r - l == 1) {
            tree[v] = init(l);
            return ;
        }
        int m = l + (r - l) / 2;

        build(2 * v + 1, l, m, init);
        build(2 * v + 2, m, r, init);

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    template <typename Fn>
    void build(Fn init) {
        build(0, 0, n, init);
    }

    void upd(int v, int l, int r, int idx, node val) {
        if (r - l == 1) {
            tree[v] = val;
            // cout << "upd: " << tree[v].h << "\n";
            return ;
        }
        int m = l + (r - l) / 2;
        if (idx < m) {
            upd(2 * v + 1, l, m, idx, val);
        } else {
            upd(2 * v + 2, m, r, idx, val);
        }

        tree[v] = tree[2 * v + 1] | tree[2 * v + 2];
    }

    void upd(int idx, node val) {
        upd(0, 0, n, idx, val);
    }

    node get(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) {
            return node();
        }
        if (ql <= l && r <= qr) {
            return tree[v];
        }

        int m = l + (r - l) / 2;

        return get(2 * v + 1, l, m, ql, qr) | get(2 * v + 2, m, r, ql, qr);
    }

    node get(int ql, int qr) {
        return get(0, 0, n, ql, qr);
    }
};

segment_tree<segment_tree_node_hash<kMaxN, kInf>> st;
segment_tree<segment_tree_node_hash<kMaxN, kInf+2>> st2;

void recolor(int v, int u) {
    assert(color[v] != color[u]);

    v = color[v];
    u = color[u];

    if (by_color[v].size() < by_color[u].size()) {
        swap(v, u);
    }

    while (!by_color[u].empty()) {
        int idx = by_color[u].back();
        by_color[u].pop_back();

        color[idx] = v;
        by_color[v].push_back(idx);

        st.upd(idx, segment_tree_node_hash<kMaxN, kInf>(v));
        st2.upd(idx, segment_tree_node_hash<kMaxN, kInf+2>(v));
    }

    // assert(color[v] == color[u]);
}

void solve() {
    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int v, u, l, c;

        cin >> v >> u >> l >> c;

        eds[i] = {v - 1, u - 1, l, c};
    }
    sort(eds, eds + m, [](auto e1, auto e2) -> bool {
        return e1.c < e2.c;
    });

    st.resize(n);
    st.build([](int idx) -> segment_tree_node_hash<kMaxN, kInf> {
        return segment_tree_node_hash<kMaxN, kInf>(idx + 1);
    });
    st2.resize(n);
    st2.build([](int idx) -> segment_tree_node_hash<kMaxN, kInf+2> {
        return segment_tree_node_hash<kMaxN, kInf+2>(idx + 1);
    });

    for (int i = 0; i < n; ++i) {
        color[i] = i + 1;
        by_color[color[i]] = {i};

        // st.upd(i, i + 1);

        // cout << "color[" << i << "] = " << st.get(i, i + 1).h << '\n';
    }

    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        auto [v, u, l, c] = eds[i];

        while (l > 0) {
            auto nv = make_pair(st.get(v, v + l).h, st2.get(v, v + l).h);
            auto nu = make_pair(st.get(u, u + l).h, st2.get(u, u + l).h);

            if (nv == nu) {
                break;
            }

            int lb = 0;
            int rb = l;

            while (rb - lb > 1) {
                int mid = lb + (rb - lb) / 2;

                auto nv_mid = make_pair(st.get(v, v + mid).h, st2.get(v, v + mid).h);
                auto nu_mid = make_pair(st.get(u, u + mid).h, st2.get(u, u + mid).h);

                if (nv_mid == nu_mid) {
                    lb = mid;
                } else {
                    rb = mid;
                }
            }
            // cout << "same? " << st.get(v, v + 1).h << ' ' << st.get(u, u + 1).h << '\n';
            // cout << "recolor: " << v << ' ' << u << ' ' << lb << '\n';

            assert(color[v + lb] != color[u + lb]);
            recolor(v + lb, u + lb);
            ans += c;

            v += lb + 1;
            u += lb + 1;
            l -= lb + 1;
        }
    }

    cout << ans << '\n';
}

void precalc() {
    segment_tree_node_hash<kMaxN, kInf>::init();
    segment_tree_node_hash<kMaxN, kInf+2>::init();
}

int32_t main() {
#ifndef KITANI
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#else
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    precalc();

    int t = 1;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }

    return 0;
}
